// cek_video.cpp - mencari tahu mengapa video tidak bisa dibuka
#include <filesystem>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/registry.hpp>

int main() {
    std::string nama = "gambar/bola.mp4";

    std::cout << "1. Folder kerja : "
              << std::filesystem::current_path().string() << "\n";
    std::cout << "2. File ada?    : "
              << (std::filesystem::exists(nama) ? "ya" : "TIDAK")
              << "\n";
    std::cout << "3. FFMPEG siap? : "
              << (cv::videoio_registry::hasBackend(cv::CAP_FFMPEG)
                      ? "ya" : "TIDAK")
              << "\n";

    cv::VideoCapture video(nama);
    std::cout << "4. Video terbuka: "
              << (video.isOpened() ? "ya" : "TIDAK") << "\n";
    return 0;
}
