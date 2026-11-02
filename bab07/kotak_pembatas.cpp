// kotak_pembatas.cpp - menandai area berwarna merah
#include <cstdlib>
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    int targetR = 205, targetG = 30, targetB = 35;   // merah apel
    int toleransi = 60;

    int xMin = gambar.cols, yMin = gambar.rows, xMax = -1, yMax = -1;
    int jumlah = 0;
    for (int y = 0; y < gambar.rows; y++) {
        for (int x = 0; x < gambar.cols; x++) {
            cv::Vec3b p = gambar.at<cv::Vec3b>(y, x);
            if (std::abs(p[2] - targetR) <= toleransi
                && std::abs(p[1] - targetG) <= toleransi
                && std::abs(p[0] - targetB) <= toleransi) {
                jumlah++;
                if (x < xMin) {
                    xMin = x;
                }
                if (x > xMax) {
                    xMax = x;
                }
                if (y < yMin) {
                    yMin = y;
                }
                if (y > yMax) {
                    yMax = y;
                }
            }
        }
    }

    std::cout << "Piksel merah: " << jumlah << "\n";
    if (jumlah > 0) {
        cv::Rect kotak(xMin, yMin, xMax - xMin + 1, yMax - yMin + 1);
        std::cout << "Kotak pembatas: " << kotak << "\n";
        cv::rectangle(gambar, kotak, cv::Scalar(0, 0, 0), 2);
        cv::putText(gambar, "merah", cv::Point(kotak.x, kotak.y - 8),
                    cv::FONT_HERSHEY_SIMPLEX, 0.7,
                    cv::Scalar(0, 0, 0), 2);
    }
    cv::imshow("Hasil", gambar);
    cv::waitKey(0);
    return 0;
}
