// ==========================================
//  ColorScan v0.8
//  Daftar warna dari CSV, menyimpan hasil,
//  dan memproses satu folder sekaligus
// ==========================================
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

namespace fs = std::filesystem;

// ---------- Struct ----------
struct TargetWarna {
    std::string nama;
    int r;
    int g;
    int b;
};

struct HasilDeteksi {
    std::string nama;
    int jumlahPiksel;
    cv::Rect kotak;
};

// ---------- Function teks ----------
std::vector<std::string> pecah(const std::string& baris,
                               char pemisah) {
    std::vector<std::string> bagian;
    std::string sekarang = "";
    for (char c : baris) {
        if (c == pemisah) {
            if (sekarang != "") {
                bagian.push_back(sekarang);
            }
            sekarang = "";
        } else {
            sekarang = sekarang + c;
        }
    }
    if (sekarang != "") {
        bagian.push_back(sekarang);
    }
    return bagian;
}

// ---------- File ----------
std::vector<TargetWarna> bacaDaftarWarna(const std::string& nama) {
    std::vector<TargetWarna> daftar;
    std::ifstream file(nama);
    if (!file) {
        std::cout << "Peringatan: " << nama << " tidak ditemukan, "
                  << "memakai daftar bawaan.\n";
        daftar.push_back({"merah", 205, 30, 35});
        daftar.push_back({"biru", 40, 80, 200});
        return daftar;
    }
    std::string baris;
    std::getline(file, baris);                    // baris judul
    while (std::getline(file, baris)) {
        std::vector<std::string> kolom = pecah(baris, ',');
        try {
            TargetWarna t = {kolom.at(0), std::stoi(kolom.at(1)),
                             std::stoi(kolom.at(2)),
                             std::stoi(kolom.at(3))};
            daftar.push_back(t);
        } catch (const std::exception& e) {
            std::cout << "Baris dilewati: " << baris << "\n";
        }
    }
    return daftar;
}

bool simpanGambar(const std::string& nama, const cv::Mat& gambar) {
    try {
        return cv::imwrite(nama, gambar);
    } catch (const cv::Exception& e) {
        std::cout << "Format file tidak dikenal: " << nama << "\n";
        return false;
    }
}

// ---------- Deteksi warna ----------
bool cocok(const cv::Vec3b& p, const TargetWarna& t, int toleransi) {
    return std::abs(p[2] - t.r) <= toleransi
           && std::abs(p[1] - t.g) <= toleransi
           && std::abs(p[0] - t.b) <= toleransi;
}

HasilDeteksi deteksi(const cv::Mat& gambar, const TargetWarna& t,
                     int toleransi) {
    int xMin = gambar.cols, yMin = gambar.rows;
    int xMax = -1, yMax = -1;
    int jumlah = 0;
    for (int y = 0; y < gambar.rows; y++) {
        for (int x = 0; x < gambar.cols; x++) {
            if (cocok(gambar.at<cv::Vec3b>(y, x), t, toleransi)) {
                jumlah++;
                if (x < xMin) {
                    xMin = x;
                }
                if (x > xMax) {
                    xMax = x;
                }
                if (y < yMin) {
                    yMin = y;
                }
                if (y > yMax) {
                    yMax = y;
                }
            }
        }
    }
    HasilDeteksi hasil = {t.nama, jumlah, cv::Rect()};
    if (jumlah > 0) {
        hasil.kotak = cv::Rect(xMin, yMin, xMax - xMin + 1,
                               yMax - yMin + 1);
    }
    return hasil;
}

void tandai(cv::Mat& gambar, const HasilDeteksi& h,
            const TargetWarna& t) {
    cv::rectangle(gambar, h.kotak, cv::Scalar(0, 0, 0), 4);
    cv::rectangle(gambar, h.kotak, cv::Scalar(t.b, t.g, t.r), 2);
    cv::Point posisi(h.kotak.x, h.kotak.y - 8);
    if (posisi.y < 15) {
        posisi.y = h.kotak.y + 20;
    }
    cv::putText(gambar, h.nama, posisi, cv::FONT_HERSHEY_SIMPLEX,
                0.6, cv::Scalar(0, 0, 0), 2);
}

// Mendeteksi semua warna, menandai, dan mengembalikan hasilnya
std::vector<HasilDeteksi> analisis(const cv::Mat& gambar,
                                   cv::Mat& gambarHasil,
                                   const std::vector<TargetWarna>& d,
                                   int toleransi) {
    std::vector<HasilDeteksi> semua;
    gambarHasil = gambar.clone();
    for (const TargetWarna& t : d) {
        HasilDeteksi h = deteksi(gambar, t, toleransi);
        if (h.jumlahPiksel > 0) {
            tandai(gambarHasil, h, t);
        }
        semua.push_back(h);
    }
    return semua;
}

// ---------- Proses satu folder ----------
void prosesFolder(const fs::path& folder,
                  const std::vector<TargetWarna>& daftar,
                  int toleransi) {
    if (!fs::exists(folder) || !fs::is_directory(folder)) {
        std::cout << "Folder tidak ditemukan: " << folder.string()
                  << "\n";
        return;
    }
    fs::create_directories("hasil");
    std::ofstream laporan("hasil/laporan.csv");
    laporan << "file,warna,jumlah_piksel,persen,x,y,lebar,tinggi\n";
    laporan << std::fixed << std::setprecision(2);

    int jumlahFile = 0;
    for (const fs::directory_entry& entri :
         fs::directory_iterator(folder)) {
        fs::path p = entri.path();
        cv::Mat gambar = cv::imread(p.string());
        if (gambar.empty()) {
            continue;
        }
        cv::Mat gambarHasil;
        std::vector<HasilDeteksi> semua =
            analisis(gambar, gambarHasil, daftar, toleransi);

        for (const HasilDeteksi& h : semua) {
            double persen = h.jumlahPiksel * 100.0 / gambar.total();
            laporan << p.filename().string() << "," << h.nama << ","
                    << h.jumlahPiksel << "," << persen << ","
                    << h.kotak.x << "," << h.kotak.y << ","
                    << h.kotak.width << "," << h.kotak.height << "\n";
        }
        std::string tujuan = "hasil/" + p.stem().string() +
                             "_hasil.png";
        simpanGambar(tujuan, gambarHasil);
        std::cout << p.filename().string() << " -> " << tujuan
                  << "\n";
        jumlahFile++;
    }
    std::cout << jumlahFile << " gambar diproses. "
              << "Laporan: hasil/laporan.csv\n";
}

// ---------- Program utama ----------
void tampilkanBantuan() {
    std::cout << "Perintah yang tersedia:\n"
              << "  buka FILE      membuka gambar\n"
              << "  cari           mencari semua warna dan menandai\n"
              << "  simpan FILE    menyimpan hasil pencarian\n"
              << "  proses FOLDER  memproses semua gambar di folder\n"
              << "  toleransi N    mengatur toleransi (awal 60)\n"
              << "  keluar         mengakhiri program\n";
}

int main() {
    std::vector<TargetWarna> daftar = bacaDaftarWarna("warna.csv");
    std::cout << "===== ColorScan v0.8 =====\n";
    std::cout << daftar.size() << " warna dimuat dari warna.csv\n";

    int toleransi = 60;
    cv::Mat gambar, gambarHasil;
    std::string baris;

    while (true) {
        std::cout << "\n> ";
        if (!std::getline(std::cin, baris)) {
            break;
        }
        std::vector<std::string> kata = pecah(baris, ' ');
        if (kata.empty()) {
            continue;
        }
        std::string perintah = kata[0];

        try {
            if (perintah == "keluar") {
                std::cout << "Terima kasih.\n";
                break;
            } else if (perintah == "bantuan") {
                tampilkanBantuan();
            } else if (perintah == "toleransi") {
                toleransi = std::stoi(kata.at(1));
                std::cout << "Toleransi sekarang " << toleransi
                          << "\n";
            } else if (perintah == "proses") {
                prosesFolder(kata.at(1), daftar, toleransi);
            } else if (perintah == "buka") {
                cv::Mat baru = cv::imread(kata.at(1));
                if (baru.empty()) {
                    std::cout << "Gagal membuka " << kata[1] << "\n";
                } else {
                    gambar = baru;
                    gambarHasil = cv::Mat();
                    std::cout << "Berhasil membuka " << kata[1]
                              << "\n";
                }
            } else if (perintah == "cari" && gambar.empty()) {
                std::cout << "Belum ada gambar. Gunakan 'buka'.\n";
            } else if (perintah == "cari") {
                std::vector<HasilDeteksi> semua =
                    analisis(gambar, gambarHasil, daftar, toleransi);
                for (const HasilDeteksi& h : semua) {
                    std::cout << h.nama << ": " << h.jumlahPiksel
                              << " piksel\n";
                }
                cv::imshow("Hasil", gambarHasil);
                cv::waitKey(0);
                cv::destroyWindow("Hasil");
            } else if (perintah == "simpan") {
                if (gambarHasil.empty()) {
                    std::cout << "Belum ada hasil. "
                              << "Jalankan 'cari'.\n";
                } else if (simpanGambar(kata.at(1), gambarHasil)) {
                    std::cout << "Tersimpan di " << kata[1] << "\n";
                }
            } else {
                std::cout << "Perintah tidak dikenal. "
                          << "Ketik 'bantuan'.\n";
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Perintah " << perintah
                      << " memerlukan argumen. Ketik 'bantuan'.\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "Argumen harus berupa angka.\n";
        } catch (const cv::Exception& e) {
            std::cout << "Error OpenCV: " << e.func << "\n";
        }
    }
    return 0;
}
