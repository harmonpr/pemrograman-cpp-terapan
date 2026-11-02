// perbandingan.cpp - memeriksa sifat warna
#include <iostream>

int main() {
    int r = 0, g = 0, b = 0;
    std::cout << "Masukkan R G B: ";
    std::cin >> r >> g >> b;

    int rata = (r + g + b) / 3;
    bool terang = rata > 127;
    bool abuAbu = (r == g) && (g == b);

    std::cout << std::boolalpha;   // tampilkan true/false
    std::cout << "Rata-rata : " << rata << "\n";
    std::cout << "Terang?   : " << terang << "\n";
    std::cout << "Abu-abu?  : " << abuAbu << "\n";
    return 0;
}
