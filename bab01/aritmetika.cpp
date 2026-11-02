// aritmetika.cpp - operator aritmetika pada warna
#include <iostream>

int main() {
    int r = 200, g = 100, b = 50;

    int jumlah = r + g + b;
    int kebalikanR = 255 - r;
    int dobelB = b * 2;
    int rataBulat = jumlah / 3;       // int / int
    double rataPecahan = jumlah / 3.0; // int / double
    int sisa = r % 16;

    std::cout << "Jumlah r + g + b  : " << jumlah << "\n";
    std::cout << "Kebalikan merah   : " << kebalikanR << "\n";
    std::cout << "Biru dikali 2     : " << dobelB << "\n";
    std::cout << "Rata-rata (/ 3)   : " << rataBulat << "\n";
    std::cout << "Rata-rata (/ 3.0) : " << rataPecahan << "\n";
    std::cout << "Sisa 200 bagi 16  : " << sisa << "\n";
    return 0;
}
