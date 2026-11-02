// mat_dasar.cpp - membuat gambar sendiri dengan cv::Mat
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // 3 baris, 4 kolom, 1 kanal, semua bernilai 7
    cv::Mat kecil(3, 4, CV_8UC1, cv::Scalar(7));
    std::cout << "Isi Mat kecil:\n" << kecil << "\n\n";

    // 200 baris, 300 kolom, 3 kanal (B, G, R)
    cv::Mat biru(200, 300, CV_8UC3, cv::Scalar(255, 0, 0));
    cv::Mat oranye(200, 300, CV_8UC3, cv::Scalar(0, 165, 255));

    std::cout << "Baris  : " << biru.rows << "\n";
    std::cout << "Kolom  : " << biru.cols << "\n";
    std::cout << "Kanal  : " << biru.channels() << "\n";

    cv::imshow("Biru", biru);
    cv::imshow("Oranye", oranye);
    cv::waitKey(0);
    return 0;
}
