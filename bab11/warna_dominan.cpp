// warna_dominan.cpp - lima warna paling banyak dalam gambar
#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat gambar = cv::imread("gambar/taman.jpg");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    // 1. Sederhanakan warna (kelipatan 32), lalu hitung dengan map
    std::map<int, int> hitung;
    for (int y = 0; y < gambar.rows; y++) {
        const cv::Vec3b* baris = gambar.ptr<cv::Vec3b>(y);
        for (int x = 0; x < gambar.cols; x++) {
            int b = baris[x][0] / 32 * 32 + 16;
            int g = baris[x][1] / 32 * 32 + 16;
            int r = baris[x][2] / 32 * 32 + 16;
            hitung[r * 65536 + g * 256 + b]++;
        }
    }

    // 2. Pindahkan ke vector agar bisa diurutkan
    std::vector<std::pair<int, int>> daftar(hitung.begin(),
                                            hitung.end());
    std::sort(daftar.begin(), daftar.end(),
              [](const std::pair<int, int>& a,
                 const std::pair<int, int>& b) {
                  return a.second > b.second;
              });

    // 3. Tampilkan dan gambar lima warna teratas
    int jumlahTampil = 5;
    if (daftar.size() < 5) {
        jumlahTampil = daftar.size();
    }
    cv::Mat palet(80, 100 * jumlahTampil, CV_8UC3,
                  cv::Scalar(255, 255, 255));
    for (int i = 0; i < jumlahTampil; i++) {
        int kode = daftar[i].first;
        int r = kode / 65536, g = kode / 256 % 256, b = kode % 256;
        double persen = daftar[i].second * 100.0 / gambar.total();
        std::cout << i + 1 << ". RGB(" << r << ", " << g << ", " << b
                  << ") " << persen << " %\n";
        cv::rectangle(palet, cv::Rect(i * 100 + 5, 5, 90, 70),
                      cv::Scalar(b, g, r), -1);
    }
    std::cout << "Jumlah kelompok warna: " << hitung.size() << "\n";
    cv::imshow("Warna dominan", palet);
    cv::waitKey(0);
    return 0;
}
