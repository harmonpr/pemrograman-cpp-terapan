// klik_piksel.cpp - membaca warna piksel dengan klik mouse
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

struct DataKlik {
    cv::Mat gambar;      // gambar asli
    cv::Mat tampilan;    // gambar yang diberi tanda
};

void saatMouse(int peristiwa, int x, int y, int, void* data) {
    if (peristiwa != cv::EVENT_LBUTTONDOWN) {
        return;                         // hanya tanggapi klik kiri
    }
    DataKlik* d = static_cast<DataKlik*>(data);
    cv::Vec3b p = d->gambar.at<cv::Vec3b>(y, x);
    int b = p[0], g = p[1], r = p[2];
    std::cout << "Klik (" << x << ", " << y << "): R=" << r
              << " G=" << g << " B=" << b << "\n";

    cv::circle(d->tampilan, cv::Point(x, y), 6, cv::Scalar(0, 0, 0),
               2);
    cv::putText(d->tampilan, std::to_string(r) + "," +
                std::to_string(g) + "," + std::to_string(b),
                cv::Point(x + 10, y - 10), cv::FONT_HERSHEY_SIMPLEX,
                0.5, cv::Scalar(0, 0, 0), 2);
}

int main() {
    DataKlik data;
    data.gambar = cv::imread("gambar/buah.png");
    if (data.gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }
    data.tampilan = data.gambar.clone();

    const std::string JENDELA = "Klik untuk membaca warna";
    cv::namedWindow(JENDELA);
    cv::setMouseCallback(JENDELA, saatMouse, &data);

    while (true) {
        cv::imshow(JENDELA, data.tampilan);
        int tombol = cv::waitKey(30);
        if (tombol == 27) {
            break;
        } else if (tombol == 'r') {          // hapus semua tanda
            data.tampilan = data.gambar.clone();
        }
    }
    return 0;
}
