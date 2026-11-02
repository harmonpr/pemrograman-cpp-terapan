// baca_piksel.cpp - membaca warna satu piksel
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    int x = 120, y = 150;   // posisi di tengah apel merah
    cv::Vec3b piksel = gambar.at<cv::Vec3b>(y, x);

    int b = piksel[0];
    int g = piksel[1];
    int r = piksel[2];
    std::cout << "Piksel (" << x << ", " << y << ")\n";
    std::cout << "R = " << r << ", G = " << g
              << ", B = " << b << "\n";

    cv::Mat abu;
    cv::cvtColor(gambar, abu, cv::COLOR_BGR2GRAY);
    int nilaiAbu = abu.at<uchar>(y, x);
    std::cout << "Nilai abu-abu = " << nilaiAbu << "\n";
    return 0;
}
