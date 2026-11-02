// salinan_mat.cpp - berbagi data atau menyalin data?
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat asli = cv::imread("gambar/buah.png");
    if (asli.empty()) {
        std::cout << "Gambar tidak ditemukan!\n";
        return 1;
    }

    cv::Mat berbagi = asli;           // hanya header yang disalin
    cv::Mat salinan = asli.clone();   // seluruh data piksel disalin

    // menggambar kotak hitam pada 'berbagi'
    cv::rectangle(berbagi, cv::Rect(20, 20, 150, 60),
                  cv::Scalar(0, 0, 0), -1);

    // mengisi sebagian gambar melalui ROI
    cv::Mat roi = asli(cv::Rect(470, 300, 150, 100));
    roi = cv::Scalar(255, 255, 255);

    std::cout << "asli dan berbagi memakai data yang sama? ";
    if (asli.data == berbagi.data) {
        std::cout << "ya\n";
    }
    std::cout << "asli dan salinan memakai data yang sama? ";
    if (asli.data != salinan.data) {
        std::cout << "tidak\n";
    }

    cv::imshow("Asli", asli);
    cv::imshow("Salinan", salinan);
    cv::waitKey(0);
    return 0;
}
