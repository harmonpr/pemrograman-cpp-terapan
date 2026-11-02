// campur_trackbar.cpp - mencampur warna dengan tiga trackbar
#include <string>
#include <opencv2/opencv.hpp>

int main() {
    const std::string JENDELA = "Pencampur Warna";
    cv::namedWindow(JENDELA);
    cv::createTrackbar("R", JENDELA, nullptr, 255);
    cv::createTrackbar("G", JENDELA, nullptr, 255);
    cv::createTrackbar("B", JENDELA, nullptr, 255);
    cv::setTrackbarPos("R", JENDELA, 255);
    cv::setTrackbarPos("G", JENDELA, 140);

    cv::Mat kanvas(200, 400, CV_8UC3);
    while (true) {
        int r = cv::getTrackbarPos("R", JENDELA);
        int g = cv::getTrackbarPos("G", JENDELA);
        int b = cv::getTrackbarPos("B", JENDELA);

        kanvas = cv::Scalar(b, g, r);
        std::string teks = "RGB(" + std::to_string(r) + ", " +
                           std::to_string(g) + ", " +
                           std::to_string(b) + ")";
        cv::putText(kanvas, teks, cv::Point(20, 110),
                    cv::FONT_HERSHEY_SIMPLEX, 1.0,
                    cv::Scalar(255, 255, 255), 2);
        cv::imshow(JENDELA, kanvas);

        int tombol = cv::waitKey(30);
        if (tombol == 27) {          // tombol Esc
            break;
        }
    }
    return 0;
}
