// ==========================================
//  ColorScan v0.9
//  Detektor dalam bentuk class:
//  warna, terang, dan gelap
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

// ---------- Class detektor ----------
class Detektor {
public:
    Detektor(const std::string& nama, const cv::Scalar& garis)
        : nama_(nama), garis_(garis) {}
    virtual ~Detektor() {}

    std::string nama() const { return nama_; }
    cv::Scalar warnaGaris() const { return garis_; }
    virtual bool cocok(const cv::Vec3b& p) const = 0;

private:
    std::string nama_;
    cv::Scalar garis_;
};

class DetektorWarna : public Detektor {
public:
    DetektorWarna(const std::string& nama, int r, int g, int b)
        : Detektor(nama, cv::Scalar(b, g, r)),
          r_(r), g_(g), b_(b), tol_(60) {}

    void setToleransi(int t) { tol_ = t; }

    bool cocok(const cv::Vec3b& p) const override {
        return std::abs(p[2] - r_) <= tol_
               && std::abs(p[1] - g_) <= tol_
               && std::abs(p[0] - b_) <= tol_;
    }

private:
    int r_, g_, b_, tol_;
};

class DetektorTerang : public Detektor {
public:
    DetektorTerang(int batas)
        : Detektor("terang", cv::Scalar(255, 255, 255)),
          batas_(batas) {}

    bool cocok(const cv::Vec3b& p) const override {
        return (p[0] + p[1] + p[2]) / 3 >= batas_;
    }

private:
    int batas_;
};

class DetektorGelap : public Detektor {
public:
    DetektorGelap(int batas)
        : Detektor("gelap", cv::Scalar(0, 0, 0)), batas_(batas) {}

    bool cocok(const cv::Vec3b& p) const override {
        return (p[0] + p[1] + p[2]) / 3 <= batas_;
    }

private:
    int batas_;
};

// ---------- Hasil deteksi ----------
struct HasilDeteksi {
    std::string nama;
    int jumlahPiksel;
    cv::Rect kotak;
};

HasilDeteksi deteksi(const Detektor& d, const cv::Mat& gambar) {
    int xMin = gambar.cols, yMin = gambar.rows;
    int xMax = -1, yMax = -1;
    int jumlah = 0;
    for (int y = 0; y < gambar.rows; y++) {
        for (int x = 0; x < gambar.cols; x++) {
            if (d.cocok(gambar.at<cv::Vec3b>(y, x))) {
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
    HasilDeteksi hasil = {d.nama(), jumlah, cv::Rect()};
    if (jumlah > 0) {
        hasil.kotak = cv::Rect(xMin, yMin, xMax - xMin + 1,
                               yMax - yMin + 1);
    }
    return hasil;
}

void tandai(cv::Mat& gambar, const HasilDeteksi& h,
            const Detektor& d) {
    cv::rectangle(gambar, h.kotak, cv::Scalar(0, 0, 0), 4);
    cv::rectangle(gambar, h.kotak, d.warnaGaris(), 2);
    cv::Point posisi(h.kotak.x, h.kotak.y - 8);
    if (posisi.y < 15) {
        posisi.y = h.kotak.y + 20;
    }
    cv::putText(gambar, h.nama, posisi, cv::FONT_HERSHEY_SIMPLEX,
                0.6, cv::Scalar(0, 0, 0), 2);
}

// Menjalankan satu detektor apa pun, mencetak, dan menandai
HasilDeteksi jalankan(const Detektor& d, const cv::Mat& gambar,
                      cv::Mat& gambarHasil) {
    HasilDeteksi h = deteksi(d, gambar);
    std::cout << h.nama << ": " << h.jumlahPiksel << " piksel\n";
    if (h.jumlahPiksel > 0) {
        tandai(gambarHasil, h, d);
    }
    return h;
}

// ---------- File ----------
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

std::vector<DetektorWarna> bacaDaftarWarna(const std::string& nama) {
    std::vector<DetektorWarna> daftar;
    std::ifstream file(nama);
    if (!file) {
        std::cout << "Peringatan: " << nama << " tidak ditemukan.\n";
        daftar.push_back(DetektorWarna("merah", 205, 30, 35));
        return daftar;
    }
    std::string baris;
    std::getline(file, baris);
    while (std::getline(file, baris)) {
        std::vector<std::string> k = pecah(baris, ',');
        try {
            DetektorWarna d(k.at(0), std::stoi(k.at(1)),
                            std::stoi(k.at(2)), std::stoi(k.at(3)));
            daftar.push_back(d);
        } catch (const std::exception& e) {
            std::cout << "Baris dilewati: " << baris << "\n";
        }
    }
    return daftar;
}

void prosesFolder(const fs::path& folder,
                  const std::vector<DetektorWarna>& daftar) {
    if (!fs::is_directory(folder)) {
        std::cout << "Folder tidak ditemukan.\n";
        return;
    }
    fs::create_directories("hasil");
    std::ofstream laporan("hasil/laporan.csv");
    laporan << "file,warna,jumlah_piksel,persen\n";
    laporan << std::fixed << std::setprecision(2);
    for (const fs::directory_entry& entri :
         fs::directory_iterator(folder)) {
        cv::Mat gambar = cv::imread(entri.path().string());
        if (gambar.empty()) {
            continue;
        }
        std::string namaFile = entri.path().filename().string();
        std::cout << "[" << namaFile << "]\n";
        cv::Mat gambarHasil = gambar.clone();
        for (const DetektorWarna& d : daftar) {
            HasilDeteksi h = jalankan(d, gambar, gambarHasil);
            laporan << namaFile << "," << h.nama << ","
                    << h.jumlahPiksel << ","
                    << h.jumlahPiksel * 100.0 / gambar.total()
                    << "\n";
        }
        cv::imwrite("hasil/" + entri.path().stem().string() +
                        "_hasil.png", gambarHasil);
    }
    std::cout << "Selesai. Laporan: hasil/laporan.csv\n";
}

// ---------- Program utama ----------
void tampilkanBantuan() {
    std::cout << "Perintah yang tersedia:\n"
              << "  buka FILE      membuka gambar\n"
              << "  cari           mencari semua warna dari CSV\n"
              << "  terang N       area dengan kecerahan >= N\n"
              << "  gelap N        area dengan kecerahan <= N\n"
              << "  toleransi N    toleransi detektor warna\n"
              << "  simpan FILE    menyimpan hasil terakhir\n"
              << "  proses FOLDER  memproses satu folder\n"
              << "  keluar         mengakhiri program\n";
}

int main() {
    std::vector<DetektorWarna> daftar = bacaDaftarWarna("warna.csv");
    std::cout << "===== ColorScan v0.9 =====\n";
    std::cout << daftar.size() << " detektor warna dimuat.\n";

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
            } else if (perintah == "buka") {
                cv::Mat baru = cv::imread(kata.at(1));
                if (baru.empty()) {
                    std::cout << "Gagal membuka " << kata[1] << "\n";
                } else {
                    gambar = baru;
                    std::cout << "Berhasil membuka " << kata[1]
                              << "\n";
                }
            } else if (perintah == "toleransi") {
                int t = std::stoi(kata.at(1));
                for (DetektorWarna& d : daftar) {
                    d.setToleransi(t);
                }
                std::cout << "Toleransi sekarang " << t << "\n";
            } else if (perintah == "proses") {
                prosesFolder(kata.at(1), daftar);
            } else if (perintah == "simpan") {
                if (gambarHasil.empty()) {
                    std::cout << "Belum ada hasil.\n";
                } else if (cv::imwrite(kata.at(1), gambarHasil)) {
                    std::cout << "Tersimpan di " << kata[1] << "\n";
                }
            } else if (gambar.empty()) {
                std::cout << "Belum ada gambar. Gunakan 'buka'.\n";
            } else if (perintah == "cari") {
                gambarHasil = gambar.clone();
                for (const DetektorWarna& d : daftar) {
                    jalankan(d, gambar, gambarHasil);
                }
                cv::imshow("Hasil", gambarHasil);
                cv::waitKey(0);
            } else if (perintah == "terang") {
                DetektorTerang d(std::stoi(kata.at(1)));
                gambarHasil = gambar.clone();
                jalankan(d, gambar, gambarHasil);
                cv::imshow("Hasil", gambarHasil);
                cv::waitKey(0);
            } else if (perintah == "gelap") {
                DetektorGelap d(std::stoi(kata.at(1)));
                gambarHasil = gambar.clone();
                jalankan(d, gambar, gambarHasil);
                cv::imshow("Hasil", gambarHasil);
                cv::waitKey(0);
            } else {
                std::cout << "Perintah tidak dikenal. "
                          << "Ketik 'bantuan'.\n";
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Perintah " << perintah
                      << " memerlukan argumen.\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "Argumen harus berupa angka.\n";
        } catch (const cv::Exception& e) {
            std::cout << "Error OpenCV: " << e.func << "\n";
        }
    }
    return 0;
}
