// deteksi.hpp - mencari dan menandai benda pada gambar
#pragma once

#include <string>
#include <vector>
#include <opencv2/core.hpp>

#include "detektor.hpp"

struct HasilDeteksi {
    std::string detektor;   // nama detektor, misalnya "merah"
    std::string nama;       // label benda, misalnya "merah 2"
    int jumlahPiksel;
    cv::Rect kotak;
};

// Masker: 255 untuk piksel yang cocok, 0 untuk lainnya
cv::Mat buatMasker(const Detektor& d, const cv::Mat& gambar);

// Memisahkan piksel yang cocok menjadi benda-benda terpisah
std::vector<HasilDeteksi> cariObjek(const Detektor& d,
                                    const cv::Mat& gambar,
                                    int luasMin);

// Menggambar kotak dan label satu benda
void tandai(cv::Mat& gambar, const HasilDeteksi& h,
            const Detektor& d);

// Menjalankan semua detektor; gambar bertanda dikirim lewat
// gambarHasil, sedangkan semua benda dikembalikan
std::vector<HasilDeteksi> jalankanSemua(const DaftarDetektor& daftar,
                                        const cv::Mat& gambar,
                                        int luasMin,
                                        cv::Mat& gambarHasil);
