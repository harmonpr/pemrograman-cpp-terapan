// detektor_polimorfik.cpp - pewarisan dan polimorfisme
#include <cstdlib>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

class Detektor {
public:
    Detektor(const std::string& nama) : nama_(nama) {}
    virtual ~Detektor() {}

    std::string nama() const { return nama_; }
    virtual bool cocok(const cv::Vec3b& p) const = 0;

private:
    std::string nama_;
};

class DetektorWarna : public Detektor {
public:
    DetektorWarna(const std::string& nama, int r, int g, int b,
                  int toleransi)
        : Detektor(nama), r_(r), g_(g), b_(b), tol_(toleransi) {}

    bool cocok(const cv::Vec3b& p) const override {
        return std::abs(p[2] - r_) <= tol_
               && std::abs(p[1] - g_) <= tol_
               && std::abs(p[0] - b_) <= tol_;
    }

private:
    int r_, g_, b_, tol_;
};

class DetektorTerang : public Detektor {
public:
    DetektorTerang(int batas) : Detektor("terang"), batas_(batas) {}

    bool cocok(const cv::Vec3b& p) const override {
        return (p[0] + p[1] + p[2]) / 3 >= batas_;
    }

private:
    int batas_;
};

// Bekerja untuk SEMUA jenis detektor
int hitungPiksel(const Detektor& d, const cv::Mat& gambar) {
    int jumlah = 0;
    for (int y = 0; y < gambar.rows; y++) {
        for (int x = 0; x < gambar.cols; x++) {
            if (d.cocok(gambar.at<cv::Vec3b>(y, x))) {
                jumlah++;
            }
        }
    }
    return jumlah;
}

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    DetektorWarna merah("merah", 205, 30, 35, 60);
    DetektorWarna biru("biru", 40, 80, 200, 60);
    DetektorTerang terang(200);

    std::cout << merah.nama() << " : " << hitungPiksel(merah, gambar)
              << " piksel\n";
    std::cout << biru.nama() << "  : " << hitungPiksel(biru, gambar)
              << " piksel\n";
    std::cout << terang.nama() << ": " << hitungPiksel(terang, gambar)
              << " piksel\n";
    return 0;
}
