// ==========================================
//  ColorScan v0.7
//  Mencari area berwarna dan menandainya
//  dengan kotak serta label
// ==========================================
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

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
std::vector<std::string> pecahKata(const std::string& baris) {
    std::vector<std::string> kata;
    std::string sekarang = "";
    for (char c : baris) {
        if (c == ' ') {
            if (sekarang != "") {
                kata.push_back(sekarang);
                sekarang = "";
            }
        } else {
            sekarang = sekarang + c;
        }
    }
    if (sekarang != "") {
        kata.push_back(sekarang);
    }
    return kata;
}

bool adalahAngka(const std::string& teks) {
    if (teks.empty() || teks.length() > 5) {
        return false;
    }
    for (char c : teks) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
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
    cv::Scalar warnaGaris(t.b, t.g, t.r);
    cv::rectangle(gambar, h.kotak, cv::Scalar(0, 0, 0), 4);
    cv::rectangle(gambar, h.kotak, warnaGaris, 2);
    std::string label = h.nama + " (" +
                        std::to_string(h.jumlahPiksel) + ")";
    cv::Point posisi(h.kotak.x, h.kotak.y - 8);
    if (posisi.y < 15) {
        posisi.y = h.kotak.y + 20;   // label tidak keluar gambar
    }
    cv::putText(gambar, label, posisi, cv::FONT_HERSHEY_SIMPLEX,
                0.6, cv::Scalar(0, 0, 0), 2);
}

// ---------- Tampilan ----------
void tampilkan(const std::string& judul, const cv::Mat& gambar) {
    cv::imshow(judul, gambar);
    std::cout << "(Tekan sembarang tombol pada jendela gambar)\n";
    cv::waitKey(0);
    cv::destroyWindow(judul);
}

void tampilkanBantuan() {
    std::cout << "Perintah yang tersedia:\n"
              << "  buka FILE     membuka gambar\n"
              << "  tampil        menampilkan gambar\n"
              << "  cari NAMA     mencari satu warna (merah, dll.)\n"
              << "  cari semua    mencari semua warna\n"
              << "  toleransi N   mengatur toleransi (awal 60)\n"
              << "  keluar        mengakhiri program\n";
}

// ---------- Program utama ----------
int main() {
    std::vector<TargetWarna> daftarTarget = {
        {"merah", 205, 30, 35},
        {"kuning", 240, 205, 40},
        {"hijau", 60, 160, 55},
        {"biru", 40, 80, 200}
    };
    int toleransi = 60;
    cv::Mat gambar;
    std::string baris;

    std::cout << "===== ColorScan v0.7 =====\n";
    std::cout << "Ketik 'bantuan' untuk melihat daftar perintah.\n";

    while (true) {
        std::cout << "\n> ";
        if (!std::getline(std::cin, baris)) {
            break;
        }
        std::vector<std::string> kata = pecahKata(baris);
        if (kata.empty()) {
            continue;
        }
        std::string perintah = kata[0];

        if (perintah == "keluar") {
            std::cout << "Terima kasih.\n";
            break;
        } else if (perintah == "bantuan") {
            tampilkanBantuan();
        } else if (perintah == "toleransi") {
            if (kata.size() < 2 || !adalahAngka(kata[1])) {
                std::cout << "Contoh: toleransi 60\n";
            } else {
                toleransi = std::stoi(kata[1]);
                std::cout << "Toleransi sekarang " << toleransi
                          << "\n";
            }
        } else if (perintah == "buka") {
            if (kata.size() < 2) {
                std::cout << "Contoh: buka gambar/buah.png\n";
                continue;
            }
            cv::Mat baru = cv::imread(kata[1]);
            if (baru.empty()) {
                std::cout << "Gagal membuka " << kata[1] << "\n";
            } else {
                gambar = baru;
                std::cout << "Berhasil membuka " << kata[1] << " ("
                          << gambar.cols << " x " << gambar.rows
                          << ")\n";
            }
        } else if (gambar.empty()) {
            std::cout << "Belum ada gambar. Contoh: "
                      << "buka gambar/buah.png\n";
        } else if (perintah == "tampil") {
            tampilkan("ColorScan", gambar);
        } else if (perintah == "cari" && kata.size() >= 2) {
            cv::Mat hasilGambar = gambar.clone();
            int ditemukan = 0;   // jumlah warna yang ditemukan
            for (const TargetWarna& t : daftarTarget) {
                if (kata[1] != "semua" && kata[1] != t.nama) {
                    continue;
                }
                HasilDeteksi h = deteksi(gambar, t, toleransi);
                std::cout << t.nama << ": " << h.jumlahPiksel
                          << " piksel";
                if (h.jumlahPiksel > 0) {
                    std::cout << ", kotak " << h.kotak;
                    tandai(hasilGambar, h, t);
                    ditemukan++;
                }
                std::cout << "\n";
            }
            if (ditemukan > 0) {
                tampilkan("Hasil pencarian", hasilGambar);
            } else if (kata[1] != "semua") {
                std::cout << "Warna " << kata[1] << " tidak ada "
                          << "atau tidak ditemukan.\n";
            }
        } else {
            std::cout << "Perintah tidak dikenal. Ketik 'bantuan'.\n";
        }
    }
    return 0;
}
