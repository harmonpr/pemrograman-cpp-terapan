// laporan.hpp - file CSV, statistik, dan pemrosesan folder
#pragma once

#include <string>
#include <vector>

#include "deteksi.hpp"
#include "detektor.hpp"

// Menambahkan detektor warna dari file CSV (nama,r,g,b)
void muatDariCsv(const std::string& namaFile,
                 DaftarDetektor& daftar);

// Ringkasan hasil deteksi terakhir
void tampilkanStatistik(std::vector<HasilDeteksi> semua);

// Memproses semua gambar di folder; hasil di folder "hasil"
void prosesFolder(const std::string& folder,
                  const DaftarDetektor& daftar, int luasMin);
