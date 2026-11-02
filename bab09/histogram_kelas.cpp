// histogram_kelas.cpp - class untuk histogram kecerahan
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

class Histogram {
public:
    Histogram(int jumlahKelompok)
        : hitung_(jumlahKelompok, 0), lebar_(256 / jumlahKelompok) {}

    void tambah(int nilai) {
        hitung_[nilai / lebar_]++;
    }

    void tambahGambar(const cv::Mat& abu) {
        for (int y = 0; y < abu.rows; y++) {
            for (int x = 0; x < abu.cols; x++) {
                tambah(abu.at<uchar>(y, x));
            }
        }
    }

    int totalPiksel() const {
        int total = 0;
        for (int h : hitung_) {
            total += h;
        }
        return total;
    }

    void tampilkan() const {
        int total = totalPiksel();
        for (std::size_t i = 0; i < hitung_.size(); i++) {
            int awal = i * lebar_;
            int persen = hitung_[i] * 100 / total;
            std::cout << std::setw(3) << awal << "-"
                      << std::setw(3) << awal + lebar_ - 1 << " | "
                      << std::string(persen / 2, '*') << " " << persen
                      << "%\n";
        }
    }

private:
    std::vector<int> hitung_;
    int lebar_;
};

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }
    cv::Mat abu;
    cv::cvtColor(gambar, abu, cv::COLOR_BGR2GRAY);

    Histogram h(8);
    h.tambahGambar(abu);
    std::cout << "Total piksel: " << h.totalPiksel() << "\n";
    h.tampilkan();
    return 0;
}
