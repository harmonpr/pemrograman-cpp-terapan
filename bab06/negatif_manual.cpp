// negatif_manual.cpp - mengolah setiap piksel dengan perulangan
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    cv::Mat hasil = gambar.clone();   // salinan untuk diolah

    for (int y = 0; y < hasil.rows; y++) {
        for (int x = 0; x < hasil.cols; x++) {
            cv::Vec3b& p = hasil.at<cv::Vec3b>(y, x);
            p[0] = 255 - p[0];   // biru
            p[1] = 255 - p[1];   // hijau
            p[2] = 255 - p[2];   // merah
        }
    }

    cv::imshow("Asli", gambar);
    cv::imshow("Negatif", hasil);
    cv::waitKey(0);
    return 0;
}
