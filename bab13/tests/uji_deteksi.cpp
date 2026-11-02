// uji_deteksi.cpp - pengujian otomatis bagian inti ColorScan
#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "deteksi.hpp"
#include "detektor.hpp"
#include "teks.hpp"

int jumlahGagal = 0;

void periksa(bool kondisi, const std::string& keterangan) {
    if (!kondisi) {
        std::cout << "  GAGAL: " << keterangan << "\n";
        jumlahGagal++;
    }
}

void ujiPecah() {
    std::cout << "ujiPecah\n";
    std::vector<std::string> k = pecah("tambah  warna merah", ' ');
    periksa(k.size() == 3, "tiga kata, spasi ganda diabaikan");
    periksa(k[0] == "tambah" && k[2] == "merah", "isi kata benar");
    periksa(pecah("merah,205,30,35", ',').size() == 4, "CSV 4 kolom");
    periksa(pecah("", ' ').empty(), "baris kosong");
}

void ujiDetektor() {
    std::cout << "ujiDetektor\n";
    DetektorWarna merah("merah", 200, 30, 30, 50);
    periksa(merah.cocok(cv::Vec3b(30, 30, 200)), "merah cocok");
    periksa(!merah.cocok(cv::Vec3b(200, 30, 30)), "biru tidak cocok");
    DetektorTerang terang(200);
    periksa(terang.cocok(cv::Vec3b(255, 255, 255)), "putih terang");
    periksa(!terang.cocok(cv::Vec3b(0, 0, 0)), "hitam tidak terang");
}

void ujiCariObjek() {
    std::cout << "ujiCariObjek\n";
    // gambar uji: dua kotak merah dan satu titik merah kecil
    cv::Mat g(100, 200, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::rectangle(g, cv::Rect(10, 10, 30, 20),
                  cv::Scalar(0, 0, 255), -1);
    cv::rectangle(g, cv::Rect(100, 50, 40, 40),
                  cv::Scalar(0, 0, 255), -1);
    g.at<cv::Vec3b>(5, 190) = cv::Vec3b(0, 0, 255);

    DetektorWarna merah("merah", 255, 0, 0, 30);
    std::vector<HasilDeteksi> h = cariObjek(merah, g, 10);
    periksa(h.size() == 2, "dua benda, titik kecil diabaikan");
    if (h.size() == 2) {
        periksa(h[0].jumlahPiksel == 30 * 20, "luas benda pertama");
        periksa(h[0].kotak == cv::Rect(10, 10, 30, 20), "kotak 1");
        periksa(h[1].kotak == cv::Rect(100, 50, 40, 40), "kotak 2");
        periksa(h[1].nama == "merah 2", "label benda kedua");
    }
    periksa(cariObjek(merah, g, 1).size() == 3,
            "tiga benda jika luas minimum 1");
}

int main() {
    ujiPecah();
    ujiDetektor();
    ujiCariObjek();
    if (jumlahGagal > 0) {
        std::cout << jumlahGagal << " pemeriksaan gagal.\n";
        return 1;                 // ctest menganggap pengujian gagal
    }
    std::cout << "Semua pengujian lulus.\n";
    return 0;
}
