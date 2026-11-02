// ambang_trackbar.cpp - mengatur batas ambang secara langsung
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }
    cv::Mat abu, hasil;
    cv::cvtColor(gambar, abu, cv::COLOR_BGR2GRAY);

    const std::string JENDELA = "Ambang";
    cv::namedWindow(JENDELA);
    cv::createTrackbar("Batas", JENDELA, nullptr, 255);
    cv::setTrackbarPos("Batas", JENDELA, 128);

    int batasLama = -1;
    while (true) {
        int batas = cv::getTrackbarPos("Batas", JENDELA);
        if (batas != batasLama) {      // hitung ulang jika berubah
            cv::threshold(abu, hasil, batas, 255, cv::THRESH_BINARY);
            std::cout << "Batas " << batas << ": "
                      << cv::countNonZero(hasil) << " piksel putih\n";
            batasLama = batas;
        }
        cv::imshow(JENDELA, hasil);
        if (cv::waitKey(30) == 27) {
            break;
        }
    }
    return 0;
}
