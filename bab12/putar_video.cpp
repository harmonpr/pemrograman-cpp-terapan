// putar_video.cpp - membaca video atau kamera frame demi frame
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

int main() {
    std::string sumber;
    std::cout << "Nama file video (atau 0 untuk kamera): ";
    std::getline(std::cin, sumber);

    cv::VideoCapture video;
    if (sumber == "0") {
        video.open(0);                  // kamera pertama
    } else {
        video.open(sumber);
    }
    if (!video.isOpened()) {
        std::cout << "Sumber video tidak bisa dibuka.\n";
        return 1;
    }

    std::cout << "Ukuran frame: "
              << video.get(cv::CAP_PROP_FRAME_WIDTH) << " x "
              << video.get(cv::CAP_PROP_FRAME_HEIGHT) << "\n";

    cv::Mat frame;
    int nomor = 0;
    while (true) {
        video >> frame;                 // baca satu frame
        if (frame.empty()) {
            std::cout << "Video selesai.\n";
            break;
        }
        nomor++;
        cv::putText(frame, "Frame " + std::to_string(nomor),
                    cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8,
                    cv::Scalar(0, 0, 0), 2);
        cv::imshow("Video", frame);
        if (cv::waitKey(30) == 27) {
            std::cout << "Dihentikan pengguna.\n";
            break;
        }
    }
    std::cout << nomor << " frame ditampilkan.\n";
    return 0;
}
