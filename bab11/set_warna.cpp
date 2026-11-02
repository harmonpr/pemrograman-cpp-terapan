// set_warna.cpp - menghitung jumlah warna yang berbeda
#include <iostream>
#include <set>
#include <string>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    std::set<int> warnaPersis;   // setiap warna RGB yang berbeda
    std::set<int> warnaKasar;    // warna setelah disederhanakan
    for (int y = 0; y < gambar.rows; y++) {
        for (int x = 0; x < gambar.cols; x++) {
            cv::Vec3b p = gambar.at<cv::Vec3b>(y, x);
            int b = p[0], g = p[1], r = p[2];
            warnaPersis.insert(r * 65536 + g * 256 + b);
            warnaKasar.insert((r / 64) * 16 + (g / 64) * 4 + b / 64);
        }
    }
    std::cout << "Warna berbeda (persis)        : "
              << warnaPersis.size() << "\n";
    std::cout << "Warna berbeda (4 tingkat/kanal): "
              << warnaKasar.size() << "\n";

    std::set<std::string> nama = {"merah", "biru", "merah", "hijau"};
    std::cout << "Isi set nama:";
    for (const std::string& n : nama) {
        std::cout << " " << n;
    }
    std::cout << "\n";
    return 0;
}
