// detektor_unik.cpp - banyak jenis detektor dalam satu vector
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
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
    DetektorWarna(const std::string& nama, int r, int g, int b)
        : Detektor(nama), r_(r), g_(g), b_(b) {}
    bool cocok(const cv::Vec3b& p) const override {
        return std::abs(p[2] - r_) <= 60 && std::abs(p[1] - g_) <= 60
               && std::abs(p[0] - b_) <= 60;
    }

private:
    int r_, g_, b_;
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

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    std::vector<std::unique_ptr<Detektor>> daftar;
    daftar.push_back(
        std::make_unique<DetektorWarna>("merah", 205, 30, 35));
    daftar.push_back(
        std::make_unique<DetektorWarna>("biru", 40, 80, 200));
    daftar.push_back(std::make_unique<DetektorTerang>(200));

    for (const std::unique_ptr<Detektor>& d : daftar) {
        int jumlah = 0;
        for (int y = 0; y < gambar.rows; y++) {
            const cv::Vec3b* baris = gambar.ptr<cv::Vec3b>(y);
            for (int x = 0; x < gambar.cols; x++) {
                if (d->cocok(baris[x])) {
                    jumlah++;
                }
            }
        }
        std::cout << d->nama() << ": " << jumlah << " piksel\n";
    }
    return 0;
}
