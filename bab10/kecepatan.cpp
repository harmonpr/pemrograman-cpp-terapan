// kecepatan.cpp - membandingkan at<>() dan ptr<>()
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }
    const int ULANG = 50;     // ulangi agar waktunya terukur
    long long total = 0;
    cv::TickMeter timer;

    timer.start();
    for (int u = 0; u < ULANG; u++) {
        for (int y = 0; y < gambar.rows; y++) {
            for (int x = 0; x < gambar.cols; x++) {
                total += gambar.at<cv::Vec3b>(y, x)[2];
            }
        }
    }
    timer.stop();
    std::cout << "at<>() : " << timer.getTimeMilli() << " ms\n";

    timer.reset();
    timer.start();
    for (int u = 0; u < ULANG; u++) {
        for (int y = 0; y < gambar.rows; y++) {
            const cv::Vec3b* baris = gambar.ptr<cv::Vec3b>(y);
            for (int x = 0; x < gambar.cols; x++) {
                total += baris[x][2];
            }
        }
    }
    timer.stop();
    std::cout << "ptr<>(): " << timer.getTimeMilli() << " ms\n";
    std::cout << "(total = " << total << ")\n";
    return 0;
}
