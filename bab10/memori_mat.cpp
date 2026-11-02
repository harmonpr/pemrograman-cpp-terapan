// memori_mat.cpp - berapa besar sebuah gambar di memori?
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    std::cout << "Jumlah piksel     : " << gambar.total() << "\n";
    std::cout << "Byte per piksel   : " << gambar.elemSize() << "\n";
    std::cout << "Byte per baris    : " << gambar.step << "\n";
    std::cout << "Total memori data : "
              << gambar.total() * gambar.elemSize() / 1024
              << " KB\n";

    cv::Mat abu;
    cv::cvtColor(gambar, abu, cv::COLOR_BGR2GRAY);
    std::cout << "Versi abu-abu     : "
              << abu.total() * abu.elemSize() / 1024 << " KB\n";
    return 0;
}
