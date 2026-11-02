// deteksi.cpp - mencari dan menandai benda pada gambar
#include "deteksi.hpp"

#include <iostream>
#include <queue>
#include <opencv2/imgproc.hpp>

cv::Mat buatMasker(const Detektor& d, const cv::Mat& gambar) {
    cv::Mat masker(gambar.rows, gambar.cols, CV_8UC1, cv::Scalar(0));
    for (int y = 0; y < gambar.rows; y++) {
        const cv::Vec3b* baris = gambar.ptr<cv::Vec3b>(y);
        uchar* barisMasker = masker.ptr<uchar>(y);
        for (int x = 0; x < gambar.cols; x++) {
            if (d.cocok(baris[x])) {
                barisMasker[x] = 255;
            }
        }
    }
    return masker;
}

std::vector<HasilDeteksi> cariObjek(const Detektor& d,
                                    const cv::Mat& gambar,
                                    int luasMin) {
    cv::Mat masker = buatMasker(d, gambar);
    std::vector<HasilDeteksi> daftarBenda;
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    for (int y = 0; y < masker.rows; y++) {
        for (int x = 0; x < masker.cols; x++) {
            if (masker.at<uchar>(y, x) != 255) {
                continue;
            }
            std::queue<cv::Point> antrian;
            antrian.push(cv::Point(x, y));
            masker.at<uchar>(y, x) = 0;
            cv::Rect kotak(x, y, 1, 1);
            int luas = 0;
            while (!antrian.empty()) {
                cv::Point p = antrian.front();
                antrian.pop();
                luas++;
                kotak = kotak | cv::Rect(p.x, p.y, 1, 1);
                for (int k = 0; k < 4; k++) {
                    int nx = p.x + dx[k], ny = p.y + dy[k];
                    if (nx >= 0 && ny >= 0 && nx < masker.cols
                        && ny < masker.rows
                        && masker.at<uchar>(ny, nx) == 255) {
                        masker.at<uchar>(ny, nx) = 0;
                        antrian.push(cv::Point(nx, ny));
                    }
                }
            }
            if (luas >= luasMin) {
                std::string label = d.nama() + " " +
                    std::to_string(daftarBenda.size() + 1);
                daftarBenda.push_back({d.nama(), label, luas, kotak});
            }
        }
    }
    return daftarBenda;
}

void tandai(cv::Mat& gambar, const HasilDeteksi& h,
            const Detektor& d) {
    cv::rectangle(gambar, h.kotak, cv::Scalar(0, 0, 0), 4);
    cv::rectangle(gambar, h.kotak, d.warnaGaris(), 2);
    cv::Point posisi(h.kotak.x, h.kotak.y - 8);
    if (posisi.y < 15) {
        posisi.y = h.kotak.y + 20;
    }
    cv::putText(gambar, h.nama, posisi, cv::FONT_HERSHEY_SIMPLEX,
                0.6, cv::Scalar(0, 0, 0), 2);
}

std::vector<HasilDeteksi> jalankanSemua(const DaftarDetektor& daftar,
                                        const cv::Mat& gambar,
                                        int luasMin,
                                        cv::Mat& gambarHasil) {
    gambarHasil = gambar.clone();
    std::vector<HasilDeteksi> semua;
    for (const std::unique_ptr<Detektor>& d : daftar) {
        std::vector<HasilDeteksi> benda =
            cariObjek(*d, gambar, luasMin);
        std::cout << d->nama() << ": " << benda.size() << " benda\n";
        for (const HasilDeteksi& h : benda) {
            tandai(gambarHasil, h, *d);
            semua.push_back(h);
        }
    }
    return semua;
}
