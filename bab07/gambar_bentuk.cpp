// gambar_bentuk.cpp - menggambar garis, kotak, lingkaran, teks
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat kanvas(300, 500, CV_8UC3, cv::Scalar(255, 255, 255));

    cv::Scalar merah(0, 0, 255), hijau(0, 160, 0),
               biru(255, 0, 0), hitam(0, 0, 0);

    cv::line(kanvas, cv::Point(20, 20), cv::Point(480, 20), hitam, 2);
    cv::rectangle(kanvas, cv::Rect(30, 50, 140, 100), merah, 3);
    cv::rectangle(kanvas, cv::Rect(200, 50, 120, 100), hijau, -1);
    cv::circle(kanvas, cv::Point(410, 100), 50, biru, 4);
    cv::putText(kanvas, "ColorScan", cv::Point(30, 230),
                cv::FONT_HERSHEY_SIMPLEX, 1.5, hitam, 3);
    cv::putText(kanvas, "kotak, lingkaran, dan teks",
                cv::Point(30, 270), cv::FONT_HERSHEY_SIMPLEX, 0.7,
                biru, 2);

    cv::imshow("Kanvas", kanvas);
    cv::waitKey(0);
    return 0;
}
