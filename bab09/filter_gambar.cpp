// filter_gambar.cpp - keluarga class filter
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

class Filter {
public:
    virtual ~Filter() {}
    virtual std::string nama() const = 0;
    virtual void terapkan(cv::Mat& gambar) const = 0;
};

class FilterNegatif : public Filter {
public:
    std::string nama() const override { return "Negatif"; }
    void terapkan(cv::Mat& gambar) const override {
        for (int y = 0; y < gambar.rows; y++) {
            for (int x = 0; x < gambar.cols; x++) {
                cv::Vec3b& p = gambar.at<cv::Vec3b>(y, x);
                p = cv::Vec3b(255 - p[0], 255 - p[1], 255 - p[2]);
            }
        }
    }
};

class FilterAbu : public Filter {
public:
    std::string nama() const override { return "Abu-abu"; }
    void terapkan(cv::Mat& gambar) const override {
        cv::Mat abu;
        cv::cvtColor(gambar, abu, cv::COLOR_BGR2GRAY);
        cv::cvtColor(abu, gambar, cv::COLOR_GRAY2BGR);
    }
};

class FilterCerah : public Filter {
public:
    FilterCerah(int jumlah) : jumlah_(jumlah) {}
    std::string nama() const override {
        return "Cerah " + std::to_string(jumlah_);
    }
    void terapkan(cv::Mat& gambar) const override {
        for (int y = 0; y < gambar.rows; y++) {
            for (int x = 0; x < gambar.cols; x++) {
                cv::Vec3b& p = gambar.at<cv::Vec3b>(y, x);
                for (int k = 0; k < 3; k++) {
                    p[k] = cv::saturate_cast<uchar>(p[k] + jumlah_);
                }
            }
        }
    }

private:
    int jumlah_;
};

void tampilkanDenganFilter(const cv::Mat& asli, const Filter& f) {
    cv::Mat hasil = asli.clone();
    f.terapkan(hasil);
    std::cout << "Menerapkan filter " << f.nama() << "\n";
    cv::imshow(f.nama(), hasil);
}

int main() {
    cv::Mat gambar = cv::imread("gambar/buah.png");
    if (gambar.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    FilterNegatif negatif;
    FilterAbu abu;
    FilterCerah cerah(80);

    tampilkanDenganFilter(gambar, negatif);
    tampilkanDenganFilter(gambar, abu);
    tampilkanDenganFilter(gambar, cerah);
    cv::waitKey(0);
    return 0;
}
