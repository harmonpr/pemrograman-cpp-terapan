// cek_terang.cpp - if sederhana
#include <iostream>

int main() {
    int abu = 0;
    std::cout << "Masukkan nilai abu-abu (0-255): ";
    std::cin >> abu;

    if (abu > 127) {
        std::cout << "Warna ini terang.\n";
    }

    std::cout << "Selesai.\n";
    return 0;
}
