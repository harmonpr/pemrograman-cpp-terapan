// konversi_folder.cpp - mengubah semua gambar menjadi abu-abu
#include <filesystem>
#include <iostream>
#include <opencv2/opencv.hpp>

namespace fs = std::filesystem;

int main() {
    fs::path folderAsal = "gambar";
    fs::path folderHasil = "hasil";

    if (!fs::exists(folderAsal)) {
        std::cout << "Folder gambar tidak ditemukan.\n";
        return 1;
    }
    fs::create_directories(folderHasil);

    int berhasil = 0;
    for (const fs::directory_entry& entri :
         fs::directory_iterator(folderAsal)) {
        fs::path p = entri.path();
        cv::Mat gambar = cv::imread(p.string());
        if (gambar.empty()) {
            continue;                  // bukan file gambar
        }

        cv::Mat abu;
        cv::cvtColor(gambar, abu, cv::COLOR_BGR2GRAY);

        std::string namaBaru = "abu_" + p.stem().string() + ".png";
        fs::path tujuan = folderHasil / namaBaru;
        if (cv::imwrite(tujuan.string(), abu)) {
            std::cout << p.filename().string() << " -> "
                      << tujuan.string() << "\n";
            berhasil++;
        }
    }
    std::cout << berhasil << " gambar selesai diproses.\n";
    return 0;
}
