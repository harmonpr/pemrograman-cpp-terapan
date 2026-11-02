// ulangi_hitung.cpp - mengulang program dengan do-while
#include <iostream>

int main() {
    char jawab = 't';

    do {
        int nilai = 0;
        std::cout << "\nMasukkan nilai kanal: ";
        std::cin >> nilai;
        std::cout << "Kebalikannya: " << 255 - nilai << "\n";

        std::cout << "Hitung lagi? (y/t): ";
        std::cin >> jawab;
    } while (jawab == 'y' || jawab == 'Y');

    std::cout << "Terima kasih!\n";
    return 0;
}
