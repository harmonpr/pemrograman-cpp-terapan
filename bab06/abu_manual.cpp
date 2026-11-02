// abu_manual.cpp - membuat gambar abu-abu dengan rumus sendiri
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    // gambar 1 kanal dengan ukuran yang sama
    cv::Mat rataRata(gambar.rows, gambar.cols, CV_8UC1);
    cv::Mat luminansi(gambar.rows, gambar.cols, CV_8UC1);

    for (int y = 0; y < gambar.rows; y++) {
        for (int x = 0; x < gambar.cols; x++) {
            cv::Vec3b p = gambar.at<cv::Vec3b>(y, x);
            int b = p[0], g = p[1], r = p[2];
            rataRata.at<uchar>(y, x) = (r + g + b) / 3;
            luminansi.at<uchar>(y, x) =
                0.299 * r + 0.587 * g + 0.114 * b;
        }
    }

    int nilaiRata = rataRata.at<uchar>(130, 530);
    int nilaiLum = luminansi.at<uchar>(130, 530);
    std::cout << "Piksel bola biru (530, 130):\n";
    std::cout << "  rata-rata = " << nilaiRata << "\n";
    std::cout << "  luminansi = " << nilaiLum << "\n";

    cv::imshow("Rata-rata", rataRata);
    cv::imshow("Luminansi", luminansi);
    cv::waitKey(0);
    return 0;
}
