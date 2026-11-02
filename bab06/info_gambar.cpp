// info_gambar.cpp - laporan singkat tentang sebuah gambar
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

int main() {
    std::string namaFile;
    std::cout << "Nama file gambar: ";
    std::getline(std::cin, namaFile);

    cv::Mat gambar = cv::imread(namaFile);
    if (gambar.empty()) {
        std::cout << "Gagal membuka " << namaFile << "\n";
        return 1;
    }

    long long totalB = 0, totalG = 0, totalR = 0;
    for (int y = 0; y < gambar.rows; y++) {
        for (int x = 0; x < gambar.cols; x++) {
            cv::Vec3b p = gambar.at<cv::Vec3b>(y, x);
            totalB += p[0];
            totalG += p[1];
            totalR += p[2];
        }
    }
    long long jumlah = gambar.total();   // jumlah piksel

    std::cout << "Lebar x tinggi : " << gambar.cols << " x "
              << gambar.rows << "\n";
    std::cout << "Jumlah piksel  : " << jumlah << "\n";
    std::cout << "Jumlah kanal   : " << gambar.channels() << "\n";
    std::cout << "Rata-rata warna: R=" << totalR / jumlah
              << " G=" << totalG / jumlah
              << " B=" << totalB / jumlah << "\n";
    return 0;
}
