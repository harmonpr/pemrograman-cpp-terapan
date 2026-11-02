// hitung_objek.cpp - memisahkan benda dengan pencarian melebar
#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    // 1. Masker: 255 untuk piksel merah, 0 untuk lainnya
    cv::Mat masker(gambar.rows, gambar.cols, CV_8UC1, cv::Scalar(0));
    for (int y = 0; y < gambar.rows; y++) {
        for (int x = 0; x < gambar.cols; x++) {
            cv::Vec3b p = gambar.at<cv::Vec3b>(y, x);
            if (std::abs(p[2] - 205) <= 60
                && std::abs(p[1] - 30) <= 60
                && std::abs(p[0] - 35) <= 60) {
                masker.at<uchar>(y, x) = 255;
            }
        }
    }

    // 2. Telusuri setiap kelompok piksel yang bersambung
    std::vector<cv::Rect> daftarKotak;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    for (int y = 0; y < masker.rows; y++) {
        for (int x = 0; x < masker.cols; x++) {
            if (masker.at<uchar>(y, x) != 255) {
                continue;
            }
            std::queue<cv::Point> antrian;
            antrian.push(cv::Point(x, y));
            masker.at<uchar>(y, x) = 0;   // tandai sudah dikunjungi
            cv::Rect kotak(x, y, 1, 1);
            while (!antrian.empty()) {
                cv::Point p = antrian.front();
                antrian.pop();
                kotak = kotak | cv::Rect(p.x, p.y, 1, 1);
                for (int k = 0; k < 4; k++) {
                    int nx = p.x + dx[k], ny = p.y + dy[k];
                    if (nx >= 0 && ny >= 0 && nx < masker.cols
                        && ny < masker.rows
                        && masker.at<uchar>(ny, nx) == 255) {
                        masker.at<uchar>(ny, nx) = 0;
                        antrian.push(cv::Point(nx, ny));
                    }
                }
            }
            daftarKotak.push_back(kotak);
        }
    }

    // 3. Tampilkan hasil
    std::cout << "Jumlah benda merah: " << daftarKotak.size() << "\n";
    for (std::size_t i = 0; i < daftarKotak.size(); i++) {
        std::cout << "Benda " << i + 1 << ": " << daftarKotak[i]
                  << "\n";
        cv::rectangle(gambar, daftarKotak[i], cv::Scalar(0, 0, 0), 2);
        cv::putText(gambar, "merah " + std::to_string(i + 1),
                    cv::Point(daftarKotak[i].x, daftarKotak[i].y - 8),
                    cv::FONT_HERSHEY_SIMPLEX, 0.6,
                    cv::Scalar(0, 0, 0), 2);
    }
    cv::imshow("Benda merah", gambar);
    cv::waitKey(0);
    return 0;
}
