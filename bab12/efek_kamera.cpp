// efek_kamera.cpp - memilih efek dengan tombol keyboard
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture video(0);
    if (!video.isOpened()) {
        std::cout << "Kamera tidak bisa dibuka.\n";
        return 1;
    }
    std::cout << "Tombol: n normal, a abu-abu, g negatif, "
              << "c cermin, Esc keluar\n";

    char efek = 'n';
    bool cermin = false;
    cv::Mat frame, hasil;
    while (video.read(frame)) {
        if (cermin) {
            cv::flip(frame, frame, 1);   // 1 = balik kiri-kanan
        }
        if (efek == 'a') {
            cv::cvtColor(frame, hasil, cv::COLOR_BGR2GRAY);
        } else if (efek == 'g') {
            cv::bitwise_not(frame, hasil);
        } else {
            hasil = frame;
        }
        cv::imshow("Kamera", hasil);

        int tombol = cv::waitKey(1);
        if (tombol == 27) {
            break;
        } else if (tombol == 'n' || tombol == 'a' || tombol == 'g') {
            efek = tombol;
        } else if (tombol == 'c') {
            cermin = !cermin;
        }
    }
    return 0;
}
