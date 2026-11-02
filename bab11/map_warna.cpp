// map_warna.cpp - menghitung piksel per nama warna dengan std::map
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <opencv2/opencv.hpp>

struct TargetWarna {
    std::string nama;
    int r, g, b;
};

// mengembalikan nama target yang cocok, atau "lainnya"
std::string namaWarna(const cv::Vec3b& p) {
    TargetWarna daftar[4] = {
        {"merah", 205, 30, 35}, {"kuning", 240, 205, 40},
        {"hijau", 60, 160, 55}, {"biru", 40, 80, 200}
    };
    for (const TargetWarna& t : daftar) {
        if (std::abs(p[2] - t.r) <= 60 && std::abs(p[1] - t.g) <= 60
            && std::abs(p[0] - t.b) <= 60) {
            return t.nama;
        }
    }
    return "lainnya";
}

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    std::map<std::string, int> hitung;
    for (int y = 0; y < gambar.rows; y++) {
        for (int x = 0; x < gambar.cols; x++) {
            hitung[namaWarna(gambar.at<cv::Vec3b>(y, x))]++;
        }
    }

    for (const auto& pasangan : hitung) {
        std::cout << pasangan.first << " : " << pasangan.second
                  << " piksel\n";
    }

    if (hitung.count("ungu") == 0) {
        std::cout << "Tidak ada piksel ungu.\n";
    }
    std::cout << "Piksel hijau: " << hitung["hijau"] << "\n";
    return 0;
}
