// stack_urungkan.cpp - fitur urungkan (undo) dengan std::stack
#include <iostream>
#include <stack>
#include <string>
#include <opencv2/opencv.hpp>

void tampilkanKecerahan(const std::string& ket, const cv::Mat& g) {
    cv::Scalar rata = cv::mean(g);       // rata-rata setiap kanal
    int abu = (rata[0] + rata[1] + rata[2]) / 3;
    std::cout << ket << " -> kecerahan rata-rata " << abu << "\n";
}

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }
    std::stack<cv::Mat> riwayat;
    tampilkanKecerahan("awal    ", gambar);

    riwayat.push(gambar.clone());           // simpan sebelum diubah
    gambar = gambar + cv::Scalar(60, 60, 60);
    tampilkanKecerahan("cerah 60", gambar);

    riwayat.push(gambar.clone());
    cv::bitwise_not(gambar, gambar);        // negatif
    tampilkanKecerahan("negatif ", gambar);

    while (!riwayat.empty()) {
        gambar = riwayat.top();             // ambil yang terakhir
        riwayat.pop();
        tampilkanKecerahan("urungkan", gambar);
    }
    return 0;
}
