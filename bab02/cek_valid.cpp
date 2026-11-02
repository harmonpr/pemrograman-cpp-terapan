// cek_valid.cpp - memeriksa rentang nilai dengan || dan &&
#include <iostream>

int main() {
    int nilai = 0;
    std::cout << "Masukkan nilai kanal: ";
    std::cin >> nilai;

    if (nilai < 0 || nilai > 255) {
        std::cout << "Tidak valid! Nilai harus 0 sampai 255.\n";
    } else {
        std::cout << "Nilai " << nilai << " valid.\n";
    }
    return 0;
}
