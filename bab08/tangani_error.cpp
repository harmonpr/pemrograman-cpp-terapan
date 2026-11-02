// tangani_error.cpp - mencegah dan menangani error
#include <filesystem>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

int main() {
    // 1. Memeriksa sebelum bertindak
    std::string namaFile = "gambar/tidak_ada.png";
    if (!std::filesystem::exists(namaFile)) {
        std::cout << "1. File " << namaFile << " tidak ada.\n";
    }

    // 2. Menangkap exception dari std::stoi
    try {
        int nilai = std::stoi("abc");
        std::cout << "Nilai: " << nilai << "\n";
    } catch (const std::exception& e) {
        std::cout << "2. Error std: " << e.what() << "\n";
    }

    // 3. Menangkap exception dari OpenCV
    try {
        cv::Mat kosong;
        cv::Mat abu;
        cv::cvtColor(kosong, abu, cv::COLOR_BGR2GRAY);
    } catch (const cv::Exception& e) {
        std::cout << "3. Error OpenCV pada function: " << e.func
                  << "\n";
    }

    // 4. Format file yang tidak dikenal
    try {
        cv::Mat gambar(10, 10, CV_8UC3, cv::Scalar(0, 0, 0));
        cv::imwrite("hasil.xyz", gambar);
    } catch (const cv::Exception& e) {
        std::cout << "4. Gagal menyimpan: format tidak dikenal\n";
    }

    std::cout << "Program tetap berjalan sampai akhir.\n";
    return 0;
}
