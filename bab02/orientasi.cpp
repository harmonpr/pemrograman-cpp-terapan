// orientasi.cpp - menentukan orientasi gambar
#include <iostream>

int main() {
    int lebar = 0, tinggi = 0;
    std::cout << "Lebar gambar : ";
    std::cin >> lebar;
    std::cout << "Tinggi gambar: ";
    std::cin >> tinggi;

    if (lebar <= 0 || tinggi <= 0) {
        std::cout << "Ukuran tidak valid.\n";
    } else if (lebar > tinggi) {
        std::cout << "Orientasi: landscape (mendatar)\n";
    } else if (lebar < tinggi) {
        std::cout << "Orientasi: portrait (tegak)\n";
    } else {
        std::cout << "Orientasi: persegi\n";
    }
    return 0;
}
