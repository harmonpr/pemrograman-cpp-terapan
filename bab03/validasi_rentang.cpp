// validasi_rentang.cpp - meminta ulang sampai nilai 0-255
#include <iostream>

int main() {
    int nilai = 0;

    do {
        std::cout << "Masukkan nilai kanal (0-255): ";
        std::cin >> nilai;

        if (nilai < 0 || nilai > 255) {
            std::cout << "Nilai harus 0 sampai 255. Coba lagi.\n";
        }
    } while (nilai < 0 || nilai > 255);

    std::cout << "Nilai diterima: " << nilai << "\n";
    return 0;
}
