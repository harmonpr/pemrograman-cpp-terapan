// input_warna.cpp - membaca warna dari keyboard
#include <iostream>

int main() {
    int r = 0, g = 0, b = 0;

    std::cout << "Masukkan nilai merah (R): ";
    std::cin >> r;
    std::cout << "Masukkan nilai hijau (G): ";
    std::cin >> g;
    std::cout << "Masukkan nilai biru  (B): ";
    std::cin >> b;

    std::cout << "Warna Anda: ("
              << r << ", " << g << ", " << b << ")\n";
    return 0;
}
