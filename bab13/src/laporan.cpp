// laporan.cpp - file CSV, statistik, dan pemrosesan folder
#include "laporan.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <opencv2/imgcodecs.hpp>

#include "teks.hpp"

namespace fs = std::filesystem;

void muatDariCsv(const std::string& namaFile,
                 DaftarDetektor& daftar) {
    std::ifstream file(namaFile);
    if (!file) {
        std::cout << "Peringatan: " << namaFile
                  << " tidak ditemukan.\n";
        return;
    }
    std::string baris;
    std::getline(file, baris);                  // baris judul
    while (std::getline(file, baris)) {
        std::vector<std::string> k = pecah(baris, ',');
        try {
            daftar.push_back(std::make_unique<DetektorWarna>(
                k.at(0), std::stoi(k.at(1)), std::stoi(k.at(2)),
                std::stoi(k.at(3)), 60));
        } catch (const std::exception& e) {
            std::cout << "Baris dilewati: " << baris << "\n";
        }
    }
}

void tampilkanStatistik(std::vector<HasilDeteksi> semua) {
    if (semua.empty()) {
        std::cout << "Belum ada hasil. Jalankan 'jalankan'.\n";
        return;
    }
    std::map<std::string, int> jumlahBenda;
    std::map<std::string, int> totalLuas;
    for (const HasilDeteksi& h : semua) {
        jumlahBenda[h.detektor]++;
        totalLuas[h.detektor] += h.jumlahPiksel;
    }
    std::cout << "Per detektor:\n";
    for (const auto& p : jumlahBenda) {
        std::cout << "  " << p.first << ": " << p.second
                  << " benda, " << totalLuas[p.first] << " piksel\n";
    }

    std::sort(semua.begin(), semua.end(),
              [](const HasilDeteksi& a, const HasilDeteksi& b) {
                  return a.jumlahPiksel > b.jumlahPiksel;
              });
    std::cout << "Benda dari yang terbesar:\n";
    for (const HasilDeteksi& h : semua) {
        std::cout << "  " << h.nama << " (" << h.jumlahPiksel
                  << " piksel)\n";
    }
}

void prosesFolder(const std::string& folder,
                  const DaftarDetektor& daftar, int luasMin) {
    if (!fs::is_directory(folder)) {
        std::cout << "Folder tidak ditemukan: " << folder << "\n";
        return;
    }
    fs::create_directories("hasil");
    std::ofstream laporan("hasil/laporan.csv");
    laporan << "file,benda,detektor,luas,persen,x,y,lebar,tinggi\n";
    laporan << std::fixed << std::setprecision(2);

    int jumlahFile = 0;
    for (const fs::directory_entry& entri :
         fs::directory_iterator(folder)) {
        fs::path p = entri.path();
        std::string ekstensi = p.extension().string();
        if (ekstensi != ".png" && ekstensi != ".jpg") {
            continue;                     // lewati video dan lainnya
        }
        cv::Mat gambar = cv::imread(p.string());
        if (gambar.empty()) {
            continue;
        }
        std::cout << "[" << p.filename().string() << "]\n";
        cv::Mat gambarHasil;
        std::vector<HasilDeteksi> semua =
            jalankanSemua(daftar, gambar, luasMin, gambarHasil);
        for (const HasilDeteksi& h : semua) {
            laporan << p.filename().string() << "," << h.nama << ","
                    << h.detektor << "," << h.jumlahPiksel << ","
                    << h.jumlahPiksel * 100.0 / gambar.total() << ","
                    << h.kotak.x << "," << h.kotak.y << ","
                    << h.kotak.width << "," << h.kotak.height << "\n";
        }
        cv::imwrite("hasil/" + p.stem().string() + "_hasil.png",
                    gambarHasil);
        jumlahFile++;
    }
    std::cout << jumlahFile << " gambar diproses. "
              << "Laporan: hasil/laporan.csv\n";
}
