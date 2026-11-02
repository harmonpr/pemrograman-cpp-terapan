// abu_abu.cpp - mengubah gambar berwarna menjadi abu-abu
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    cv::Mat abu;
    cv::cvtColor(gambar, abu, cv::COLOR_BGR2GRAY);

    std::cout << "Kanal gambar asli: " << gambar.channels() << "\n";
    std::cout << "Kanal gambar abu : " << abu.channels() << "\n";

    cv::imshow("Asli", gambar);
    cv::imshow("Abu-abu", abu);
    cv::waitKey(0);
    return 0;
}
