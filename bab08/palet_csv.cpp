// palet_csv.cpp - membuat gambar palet dari file CSV
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

struct Warna {
    std::string nama;
    int r;
    int g;
    int b;
};

std::vector<std::string> pecah(const std::string& baris,
                               char pemisah) {
    std::vector<std::string> bagian;
    std::string sekarang = "";
    for (char c : baris) {
        if (c == pemisah) {
            bagian.push_back(sekarang);
            sekarang = "";
        } else {
            sekarang = sekarang + c;
        }
    }
    bagian.push_back(sekarang);
    return bagian;
}

int main() {
    std::ifstream file("warna.csv");
    if (!file) {
        std::cout << "warna.csv tidak ditemukan!\n";
        return 1;
    }

    std::vector<Warna> palet;
    std::string baris;
    std::getline(file, baris);                 // baris judul
    int nomorBaris = 1;
    while (std::getline(file, baris)) {
        nomorBaris++;
        std::vector<std::string> kolom = pecah(baris, ',');
        try {
            Warna w = {kolom.at(0), std::stoi(kolom.at(1)),
                       std::stoi(kolom.at(2)),
                       std::stoi(kolom.at(3))};
            palet.push_back(w);
        } catch (const std::exception& e) {
            std::cout << "Baris " << nomorBaris
                      << " dilewati karena formatnya salah.\n";
        }
    }

    if (palet.empty()) {
        std::cout << "Tidak ada warna yang bisa dibaca.\n";
        return 1;
    }

    cv::Mat kanvas(140, 100 * palet.size(), CV_8UC3,
                   cv::Scalar(255, 255, 255));
    for (std::size_t i = 0; i < palet.size(); i++) {
        cv::Rect kotak(i * 100 + 10, 10, 80, 80);
        cv::rectangle(kanvas, kotak,
                      cv::Scalar(palet[i].b, palet[i].g, palet[i].r),
                      -1);
        cv::putText(kanvas, palet[i].nama, cv::Point(kotak.x, 120),
                    cv::FONT_HERSHEY_SIMPLEX, 0.6,
                    cv::Scalar(0, 0, 0), 1);
    }

    if (cv::imwrite("palet.png", kanvas)) {
        std::cout << palet.size() << " warna disimpan ke palet.png\n";
    }
    return 0;
}
