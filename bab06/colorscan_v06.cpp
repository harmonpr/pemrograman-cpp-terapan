// ==========================================
//  ColorScan v0.6
//  Menganalisis warna pada gambar asli
//  dengan OpenCV
// ==========================================
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

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

// ---------- Function warna (dari Bab 4) ----------
std::string kelompokWarna(int r, int g, int b) {
    if (r < 50 && g < 50 && b < 50) {
        return "hitam";
    } else if (r > 200 && g > 200 && b > 200) {
        return "putih";
    } else if (r == g && g == b) {
        return "abu-abu";
    } else if (r >= g && r >= b) {
        return "kemerahan";
    } else if (g >= r && g >= b) {
        return "kehijauan";
    }
    return "kebiruan";
}

// ---------- Function gambar ----------
void tampilkan(const std::string& judul, const cv::Mat& gambar) {
    cv::imshow(judul, gambar);
    std::cout << "(Tekan sembarang tombol pada jendela gambar)\n";
    cv::waitKey(0);
    cv::destroyWindow(judul);
}

void tampilkanInfo(const cv::Mat& gambar) {
    std::cout << "Ukuran : " << gambar.cols << " x " << gambar.rows
              << " piksel\n";
    std::cout << "Kanal  : " << gambar.channels() << "\n";
    std::cout << "Piksel : " << gambar.total() << "\n";
}

void tampilkanPiksel(const cv::Mat& gambar, int x, int y) {
    cv::Vec3b p = gambar.at<cv::Vec3b>(y, x);
    int b = p[0], g = p[1], r = p[2];
    std::cout << "Piksel (" << x << ", " << y << "): R=" << r
              << " G=" << g << " B=" << b << " -> "
              << kelompokWarna(r, g, b) << "\n";
}

void tampilkanRataRata(const cv::Mat& gambar) {
    long long totalB = 0, totalG = 0, totalR = 0;
    for (int y = 0; y < gambar.rows; y++) {
        for (int x = 0; x < gambar.cols; x++) {
            cv::Vec3b p = gambar.at<cv::Vec3b>(y, x);
            totalB += p[0];
            totalG += p[1];
            totalR += p[2];
        }
    }
    long long n = gambar.total();
    int r = totalR / n, g = totalG / n, b = totalB / n;
    std::cout << "Rata-rata warna: R=" << r << " G=" << g
              << " B=" << b << " -> " << kelompokWarna(r, g, b)
              << "\n";
}

cv::Mat buatNegatif(const cv::Mat& gambar) {
    cv::Mat hasil = gambar.clone();
    for (int y = 0; y < hasil.rows; y++) {
        for (int x = 0; x < hasil.cols; x++) {
            cv::Vec3b& p = hasil.at<cv::Vec3b>(y, x);
            p[0] = 255 - p[0];
            p[1] = 255 - p[1];
            p[2] = 255 - p[2];
        }
    }
    return hasil;
}

void tampilkanBantuan() {
    std::cout << "Perintah yang tersedia:\n"
              << "  buka FILE     membuka gambar\n"
              << "  info          ukuran dan jumlah kanal\n"
              << "  tampil        menampilkan gambar\n"
              << "  piksel X Y    warna piksel di posisi X, Y\n"
              << "  rata          rata-rata warna seluruh gambar\n"
              << "  abu           menampilkan versi abu-abu\n"
              << "  negatif       menampilkan versi negatif\n"
              << "  keluar        mengakhiri program\n";
}

// ---------- Program utama ----------
int main() {
    cv::Mat gambar;           // masih kosong
    std::string baris;

    std::cout << "===== ColorScan v0.6 =====\n";
    std::cout << "Ketik 'bantuan' untuk melihat daftar perintah.\n";

    while (true) {
        std::cout << "\n> ";
        if (!std::getline(std::cin, baris)) {
            break;
        }
        std::vector<std::string> kata = pecahKata(baris);
        if (kata.empty()) {
            continue;   // baris kosong, minta perintah lagi
        }
        std::string perintah = kata[0];

        if (perintah == "keluar") {
            std::cout << "Terima kasih.\n";
            break;
        } else if (perintah == "bantuan") {
            tampilkanBantuan();
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
                std::cout << "Berhasil membuka " << kata[1] << "\n";
                tampilkanInfo(gambar);
            }
        } else if (gambar.empty()) {
            std::cout << "Belum ada gambar. Contoh: "
                      << "buka gambar/buah.png\n";
        } else if (perintah == "info") {
            tampilkanInfo(gambar);
        } else if (perintah == "tampil") {
            tampilkan("ColorScan", gambar);
        } else if (perintah == "piksel") {
            if (kata.size() < 3 || !adalahAngka(kata[1])
                || !adalahAngka(kata[2])) {
                std::cout << "Contoh: piksel 120 150\n";
                continue;
            }
            int x = std::stoi(kata[1]);
            int y = std::stoi(kata[2]);
            if (x >= gambar.cols || y >= gambar.rows) {
                std::cout << "Posisi di luar gambar.\n";
            } else {
                tampilkanPiksel(gambar, x, y);
            }
        } else if (perintah == "rata") {
            tampilkanRataRata(gambar);
        } else if (perintah == "abu") {
            cv::Mat abu;
            cv::cvtColor(gambar, abu, cv::COLOR_BGR2GRAY);
            tampilkan("Abu-abu", abu);
        } else if (perintah == "negatif") {
            tampilkan("Negatif", buatNegatif(gambar));
        } else {
            std::cout << "Perintah tidak dikenal: " << perintah
                      << ". Ketik 'bantuan'.\n";
        }
    }
    return 0;
}
