// struct_opencv.cpp - Point, Size, Rect, dan Scalar
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    cv::Size ukuran = gambar.size();
    std::cout << "Ukuran: " << ukuran.width << " x "
              << ukuran.height << "\n";

    cv::Point titik(120, 150);
    std::cout << "Titik : x=" << titik.x << " y=" << titik.y << "\n";

    cv::Rect kotak(60, 90, 130, 130);   // x, y, lebar, tinggi
    std::cout << "Kotak : " << kotak << "\n";
    std::cout << "Luas  : " << kotak.area() << " piksel\n";
    if (kotak.contains(titik)) {
        std::cout << "Titik berada di dalam kotak\n";
    }

    cv::Scalar merah(0, 0, 255);        // urutan B, G, R
    std::cout << "Merah : " << merah << "\n";

    cv::Mat potongan = gambar(kotak);    // memotong dengan Rect
    std::cout << "Potongan: " << potongan.cols << " x "
              << potongan.rows << "\n";
    cv::imshow("Potongan", potongan);
    cv::waitKey(0);
    return 0;
}
