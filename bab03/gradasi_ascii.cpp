// gradasi_ascii.cpp - menggambar gradasi dengan karakter
#include <iostream>

int main() {
    int tinggi = 5;
    int lebar = 32;

    for (int baris = 0; baris < tinggi; baris++) {
        for (int kolom = 0; kolom < lebar; kolom++) {
            int nilai = kolom * 8;   // 0, 8, 16, ..., 248

            if (nilai < 64) {
                std::cout << '@';    // paling gelap
            } else if (nilai < 128) {
                std::cout << '#';
            } else if (nilai < 192) {
                std::cout << '+';
            } else {
                std::cout << '.';    // paling terang
            }
        }
        std::cout << "\n";
    }
    return 0;
}
