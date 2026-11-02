// baca_csv.cpp - membaca file CSV baris demi baris
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

    std::string baris;
    std::getline(file, baris);              // lewati baris judul
    while (std::getline(file, baris)) {
        std::vector<std::string> kolom = pecah(baris, ',');
        if (kolom.size() != 4) {
            continue;
        }
        std::cout << kolom[0] << " -> R=" << kolom[1]
                  << " G=" << kolom[2] << " B=" << kolom[3] << "\n";
    }
    return 0;
}
