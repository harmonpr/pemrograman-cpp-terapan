// terang_gelap.cpp - if dan else
#include <iostream>

int main() {
    int abu = 0;
    std::cout << "Masukkan nilai abu-abu (0-255): ";
    std::cin >> abu;

    if (abu > 127) {
        std::cout << "Warna ini terang.\n";
    } else {
        std::cout << "Warna ini gelap.\n";
    }
    return 0;
}
