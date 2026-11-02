// pemilih_warna.cpp - contoh warna dari piksel yang diklik
#include <cstdio>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

struct DataPemilih {
    cv::Mat gambar;
    cv::Mat contoh;     // jendela kecil berisi warna terpilih
};

std::string keHeksa(int r, int g, int b) {
    char teks[8];
    std::snprintf(teks, sizeof(teks), "#%02X%02X%02X", r, g, b);
    return teks;
}

void saatMouse(int peristiwa, int x, int y, int, void* data) {
    if (peristiwa != cv::EVENT_LBUTTONDOWN) {
        return;
    }
    DataPemilih* d = static_cast<DataPemilih*>(data);
    cv::Vec3b p = d->gambar.at<cv::Vec3b>(y, x);
    int b = p[0], g = p[1], r = p[2];

    d->contoh = cv::Scalar(b, g, r);
    cv::Scalar warnaTeks(255, 255, 255);
    if ((r + g + b) / 3 > 127) {
        warnaTeks = cv::Scalar(0, 0, 0);   // teks gelap
    }
    std::string rgb = std::to_string(r) + ", " + std::to_string(g) +
                      ", " + std::to_string(b);
    cv::putText(d->contoh, rgb, cv::Point(15, 50),
                cv::FONT_HERSHEY_SIMPLEX, 0.8, warnaTeks, 2);
    cv::putText(d->contoh, keHeksa(r, g, b), cv::Point(15, 95),
                cv::FONT_HERSHEY_SIMPLEX, 0.8, warnaTeks, 2);
    std::cout << "Dipilih " << keHeksa(r, g, b) << "\n";
}

int main() {
    DataPemilih data;
    data.gambar = cv::imread("gambar/taman.jpg");
    if (data.gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }
    data.contoh = cv::Mat(130, 260, CV_8UC3,
                          cv::Scalar(255, 255, 255));

    cv::namedWindow("Gambar");
    cv::setMouseCallback("Gambar", saatMouse, &data);
    while (true) {
        cv::imshow("Gambar", data.gambar);
        cv::imshow("Warna", data.contoh);
        if (cv::waitKey(30) == 27) {
            break;
        }
    }
    return 0;
}
