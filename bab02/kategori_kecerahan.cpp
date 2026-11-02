// kategori_kecerahan.cpp - if, else if, else
#include <iostream>

int main() {
    int abu = 0;
    std::cout << "Masukkan nilai abu-abu (0-255): ";
    std::cin >> abu;

    if (abu < 85) {
        std::cout << "Kategori: gelap\n";
    } else if (abu < 170) {
        std::cout << "Kategori: sedang\n";
    } else {
        std::cout << "Kategori: terang\n";
    }
    return 0;
}
