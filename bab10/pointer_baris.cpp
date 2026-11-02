// pointer_baris.cpp - menelusuri gambar dengan pointer baris
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    cv::Mat hasil = gambar.clone();
    for (int y = 0; y < hasil.rows; y++) {
        cv::Vec3b* baris = hasil.ptr<cv::Vec3b>(y);  // awal baris y
        for (int x = 0; x < hasil.cols; x++) {
            baris[x][0] = 255 - baris[x][0];
            baris[x][1] = 255 - baris[x][1];
            baris[x][2] = 255 - baris[x][2];
        }
    }

    cv::Vec3b* awal = hasil.ptr<cv::Vec3b>(0);
    std::cout << "Piksel pertama setelah dibalik: " << awal[0]
              << "\n";
    cv::imshow("Negatif", hasil);
    cv::waitKey(0);
    return 0;
}
