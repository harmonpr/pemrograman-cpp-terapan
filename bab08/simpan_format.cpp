// simpan_format.cpp - menyimpan gambar dalam beberapa format
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

namespace fs = std::filesystem;

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    cv::imwrite("buah_salin.png", gambar);
    cv::imwrite("buah_bagus.jpg", gambar,
                {cv::IMWRITE_JPEG_QUALITY, 95});
    cv::imwrite("buah_kecil.jpg", gambar,
                {cv::IMWRITE_JPEG_QUALITY, 30});

    std::vector<std::string> daftar = {
        "gambar/buah.png", "buah_salin.png", "buah_bagus.jpg",
        "buah_kecil.jpg"
    };
    for (const std::string& nama : daftar) {
        std::cout << nama << " : " << fs::file_size(nama) / 1024
                  << " KB\n";
    }
    return 0;
}
