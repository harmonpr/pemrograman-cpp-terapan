// campur_warna.cpp - mencampur dua warna sama rata
#include <iostream>

int main() {
    int r1 = 0, g1 = 0, b1 = 0;
    int r2 = 0, g2 = 0, b2 = 0;

    std::cout << "Warna pertama (R G B): ";
    std::cin >> r1 >> g1 >> b1;
    std::cout << "Warna kedua   (R G B): ";
    std::cin >> r2 >> g2 >> b2;

    int r = (r1 + r2) / 2;
    int g = (g1 + g2) / 2;
    int b = (b1 + b2) / 2;

    std::cout << "Hasil campuran: ("
              << r << ", " << g << ", " << b << ")\n";
    return 0;
}
