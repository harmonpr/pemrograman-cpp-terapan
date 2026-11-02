// interaktif.cpp - mode interaktif dengan mouse, trackbar, dan video
#include "interaktif.hpp"

#include <filesystem>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include "deteksi.hpp"

namespace {   // hanya dipakai di dalam file ini

struct DataInteraktif {
    cv::Mat frame;              // frame yang sedang diolah
    bool adaTarget = false;
    cv::Vec3b target;           // warna yang diklik (B, G, R)
};

void saatKlik(int peristiwa, int x, int y, int, void* data) {
    DataInteraktif* d = static_cast<DataInteraktif*>(data);
    if (peristiwa == cv::EVENT_LBUTTONDOWN && !d->frame.empty()) {
        d->target = d->frame.at<cv::Vec3b>(y, x);
        d->adaTarget = true;
        std::cout << "Target dipilih di (" << x << ", " << y << ")\n";
    }
}

// Membuka gambar diam, file video, atau kamera
bool bukaSumber(const std::string& sumber, cv::VideoCapture& video,
                cv::Mat& gambarDiam) {
    if (sumber == "kamera") {
        video.open(0);
        return video.isOpened();
    }
    std::string ekstensi =
        std::filesystem::path(sumber).extension().string();
    if (ekstensi == ".png" || ekstensi == ".jpg"
        || ekstensi == ".bmp") {
        gambarDiam = cv::imread(sumber);
        return !gambarDiam.empty();
    }
    video.open(sumber);
    return video.isOpened();
}

}  // namespace

void modeInteraktif(const std::string& sumber,
                    DaftarDetektor& daftar) {
    cv::VideoCapture video;
    cv::Mat gambarDiam;
    if (!bukaSumber(sumber, video, gambarDiam)) {
        std::cout << "Sumber tidak bisa dibuka: " << sumber << "\n";
        return;
    }

    const std::string JENDELA = "ColorScan Interaktif";
    cv::namedWindow(JENDELA);
    cv::createTrackbar("Toleransi", JENDELA, nullptr, 150);
    cv::createTrackbar("LuasMin", JENDELA, nullptr, 2000);
    cv::setTrackbarPos("Toleransi", JENDELA, 60);
    cv::setTrackbarPos("LuasMin", JENDELA, 100);

    DataInteraktif data;
    cv::setMouseCallback(JENDELA, saatKlik, &data);
    bool pakaiDaftar = false;
    int nomorSimpan = 0;
    std::cout << "Klik benda untuk memilih target warna.\n"
              << "Tombol: d daftar detektor, t tambah target ke "
              << "daftar,\n        s simpan, r hapus target, "
              << "Esc kembali\n";

    while (true) {
        if (!gambarDiam.empty()) {
            data.frame = gambarDiam;
        } else if (!video.read(data.frame)) {
            std::cout << "Video selesai.\n";
            break;
        }
        int tol = cv::getTrackbarPos("Toleransi", JENDELA);
        int luasMin = cv::getTrackbarPos("LuasMin", JENDELA);
        cv::Mat tampil = data.frame.clone();
        int jumlahBenda = 0;

        if (pakaiDaftar) {
            for (const std::unique_ptr<Detektor>& d : daftar) {
                for (const HasilDeteksi& h :
                     cariObjek(*d, data.frame, luasMin)) {
                    tandai(tampil, h, *d);
                    jumlahBenda++;
                }
            }
        }
        if (data.adaTarget) {
            DetektorWarna target("target", data.target[2],
                                 data.target[1], data.target[0], tol);
            for (const HasilDeteksi& h :
                 cariObjek(target, data.frame, luasMin)) {
                tandai(tampil, h, target);
                jumlahBenda++;
            }
        }
        cv::putText(tampil, std::to_string(jumlahBenda) + " benda",
                    cv::Point(10, tampil.rows - 15),
                    cv::FONT_HERSHEY_SIMPLEX, 0.8,
                    cv::Scalar(0, 0, 0), 2);
        cv::imshow(JENDELA, tampil);

        int tombol = cv::waitKey(30);
        if (tombol == 27) {
            break;
        } else if (tombol == 'd') {
            pakaiDaftar = !pakaiDaftar;
        } else if (tombol == 'r') {
            data.adaTarget = false;
        } else if (tombol == 's') {
            nomorSimpan++;
            std::string nama = "tangkapan_" +
                               std::to_string(nomorSimpan) + ".png";
            cv::imwrite(nama, tampil);
            std::cout << "Tersimpan di " << nama << "\n";
        } else if (tombol == 't' && data.adaTarget) {
            std::string nama = "target" +
                               std::to_string(daftar.size() + 1);
            daftar.push_back(std::make_unique<DetektorWarna>(
                nama, data.target[2], data.target[1],
                data.target[0], tol));
            std::cout << "Ditambahkan ke daftar: " << nama << "\n";
        }
    }
    cv::destroyWindow(JENDELA);
}
