// palet_warna.cpp - menggambar palet dari vector struct
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

struct Warna {
    std::string nama;
    int r;
    int g;
    int b;
};

int main() {
    std::vector<Warna> palet = {
        {"merah", 220, 30, 40},   {"oranye", 255, 140, 0},
        {"kuning", 240, 205, 40}, {"hijau", 60, 160, 55},
        {"biru", 40, 80, 200},    {"ungu", 130, 60, 170}
    };

    int lebarKotak = 100;
    cv::Mat kanvas(160, lebarKotak * palet.size(), CV_8UC3,
                   cv::Scalar(255, 255, 255));

    for (std::size_t i = 0; i < palet.size(); i++) {
        const Warna& w = palet[i];
        cv::Rect kotak(i * lebarKotak + 10, 10, lebarKotak - 20, 100);
        cv::rectangle(kanvas, kotak, cv::Scalar(w.b, w.g, w.r), -1);
        cv::putText(kanvas, w.nama, cv::Point(kotak.x, 140),
                    cv::FONT_HERSHEY_SIMPLEX, 0.6,
                    cv::Scalar(0, 0, 0), 1);
    }

    cv::imshow("Palet", kanvas);
    cv::waitKey(0);
    return 0;
}
