// lacak_warna.cpp - klik sebuah benda, lalu lacak warnanya
#include <cstdlib>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

struct DataLacak {
    cv::Mat frame;          // frame yang sedang tampil
    bool adaTarget = false;
    cv::Vec3b target;
};

void saatMouse(int peristiwa, int x, int y, int, void* data) {
    DataLacak* d = static_cast<DataLacak*>(data);
    if (peristiwa == cv::EVENT_LBUTTONDOWN && !d->frame.empty()) {
        d->target = d->frame.at<cv::Vec3b>(y, x);
        d->adaTarget = true;
        std::cout << "Target: " << d->target << " (urutan B, G, R)\n";
    }
}

int main() {
    std::string sumber;
    std::cout << "Nama file video (atau 0 untuk kamera): ";
    std::getline(std::cin, sumber);
    cv::VideoCapture video;
    if (sumber == "0") {
        video.open(0);
    } else {
        video.open(sumber);
    }
    if (!video.isOpened()) {
        std::cout << "Sumber video tidak bisa dibuka.\n";
        return 1;
    }

    const std::string JENDELA = "Lacak Warna";
    DataLacak data;
    cv::namedWindow(JENDELA);
    cv::createTrackbar("Toleransi", JENDELA, nullptr, 150);
    cv::setTrackbarPos("Toleransi", JENDELA, 60);
    cv::setMouseCallback(JENDELA, saatMouse, &data);

    while (video.read(data.frame)) {
        cv::Mat tampil = data.frame.clone();
        if (data.adaTarget) {
            int tol = cv::getTrackbarPos("Toleransi", JENDELA);
            cv::Scalar bawah(data.target[0] - tol,
                             data.target[1] - tol,
                             data.target[2] - tol);
            cv::Scalar atas(data.target[0] + tol,
                            data.target[1] + tol,
                            data.target[2] + tol);
            cv::Mat masker;
            cv::inRange(data.frame, bawah, atas, masker);
            if (cv::countNonZero(masker) > 100) {
                cv::Rect kotak = cv::boundingRect(masker);
                cv::rectangle(tampil, kotak, cv::Scalar(0, 0, 0), 3);
            }
        }
        cv::imshow(JENDELA, tampil);
        int tombol = cv::waitKey(30);
        if (tombol == 27) {
            break;
        } else if (tombol == 'r') {
            data.adaTarget = false;      // hapus target
        }
    }
    return 0;
}
