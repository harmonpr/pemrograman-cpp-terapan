// papan_catur.cpp - pola papan catur dengan perulangan bersarang
#include <iostream>

int main() {
    int ukuran = 0;
    std::cout << "Ukuran papan: ";
    std::cin >> ukuran;

    for (int baris = 0; baris < ukuran; baris++) {
        for (int kolom = 0; kolom < ukuran; kolom++) {
            if ((baris + kolom) % 2 == 0) {
                std::cout << "##";   // kotak hitam
            } else {
                std::cout << "..";   // kotak putih
            }
        }
        std::cout << "\n";
    }
    return 0;
}
