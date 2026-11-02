// tampil_gambar.cpp - membuka dan menampilkan gambar
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");

    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    std::cout << "Ukuran gambar: " << gambar.cols << " x "
              << gambar.rows << " piksel\n";

    cv::imshow("Buah", gambar);
    std::cout << "Tekan sembarang tombol pada jendela gambar...\n";
    cv::waitKey(0);
    return 0;
}
