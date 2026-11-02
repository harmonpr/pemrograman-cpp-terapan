// statistik_abu.cpp - statistik kecerahan dengan <algorithm>
#include <algorithm>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/taman.jpg");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }
    cv::Mat abu;
    cv::cvtColor(gambar, abu, cv::COLOR_BGR2GRAY);

    std::vector<int> nilai;
    for (int y = 0; y < abu.rows; y++) {
        for (int x = 0; x < abu.cols; x++) {
            nilai.push_back(abu.at<uchar>(y, x));
        }
    }

    auto terkecil = std::min_element(nilai.begin(), nilai.end());
    auto terbesar = std::max_element(nilai.begin(), nilai.end());
    std::cout << "Terkecil : " << *terkecil << "\n";
    std::cout << "Terbesar : " << *terbesar << "\n";

    std::sort(nilai.begin(), nilai.end());
    std::cout << "Median   : " << nilai[nilai.size() / 2] << "\n";

    int gelap = std::count_if(nilai.begin(), nilai.end(),
                              [](int n) { return n < 85; });
    int terang = std::count_if(nilai.begin(), nilai.end(),
                               [](int n) { return n >= 170; });
    std::cout << "Gelap    : " << gelap * 100 / nilai.size()
              << " %\n";
    std::cout << "Terang   : " << terang * 100 / nilai.size()
              << " %\n";
    return 0;
}
