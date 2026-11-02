// hitung_benda.cpp - alat kecil yang memakai pustaka colorscan_inti
#include <filesystem>
#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>

#include "deteksi.hpp"
#include "detektor.hpp"
#include "laporan.hpp"

namespace fs = std::filesystem;

int main() {
    DaftarDetektor daftar;
    muatDariCsv("warna.csv", daftar);

    std::string folder;
    std::cout << "Folder gambar: ";
    std::getline(std::cin, folder);
    if (!fs::is_directory(folder)) {
        std::cout << "Folder tidak ditemukan.\n";
        return 1;
    }

    for (const fs::directory_entry& entri :
         fs::directory_iterator(folder)) {
        std::string ekstensi = entri.path().extension().string();
        if (ekstensi != ".png" && ekstensi != ".jpg") {
            continue;                   // hanya file gambar
        }
        cv::Mat gambar = cv::imread(entri.path().string());
        int total = 0;
        for (const std::unique_ptr<Detektor>& d : daftar) {
            total += cariObjek(*d, gambar, 100).size();
        }
        std::cout << entri.path().filename().string() << ": "
                  << total << " benda\n";
    }
    return 0;
}
