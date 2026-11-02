// detektor.cpp - isi method keluarga class detektor
#include "detektor.hpp"

#include <cstdlib>

// ---------- Detektor ----------
Detektor::Detektor(const std::string& nama, const cv::Scalar& garis)
    : nama_(nama), garis_(garis) {}

std::string Detektor::nama() const {
    return nama_;
}

cv::Scalar Detektor::warnaGaris() const {
    return garis_;
}

// ---------- DetektorWarna ----------
DetektorWarna::DetektorWarna(const std::string& nama, int r, int g,
                             int b, int toleransi)
    : Detektor(nama, cv::Scalar(b, g, r)),
      r_(r), g_(g), b_(b), tol_(toleransi) {}

bool DetektorWarna::cocok(const cv::Vec3b& p) const {
    return std::abs(p[2] - r_) <= tol_
           && std::abs(p[1] - g_) <= tol_
           && std::abs(p[0] - b_) <= tol_;
}

std::string DetektorWarna::keterangan() const {
    return "warna (" + std::to_string(r_) + ", " +
           std::to_string(g_) + ", " + std::to_string(b_) +
           "), toleransi " + std::to_string(tol_);
}

// ---------- DetektorTerang ----------
DetektorTerang::DetektorTerang(int batas)
    : Detektor("terang", cv::Scalar(255, 255, 255)), batas_(batas) {}

bool DetektorTerang::cocok(const cv::Vec3b& p) const {
    return (p[0] + p[1] + p[2]) / 3 >= batas_;
}

std::string DetektorTerang::keterangan() const {
    return "kecerahan >= " + std::to_string(batas_);
}

// ---------- DetektorGelap ----------
DetektorGelap::DetektorGelap(int batas)
    : Detektor("gelap", cv::Scalar(0, 0, 0)), batas_(batas) {}

bool DetektorGelap::cocok(const cv::Vec3b& p) const {
    return (p[0] + p[1] + p[2]) / 3 <= batas_;
}

std::string DetektorGelap::keterangan() const {
    return "kecerahan <= " + std::to_string(batas_);
}
