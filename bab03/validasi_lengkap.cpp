// validasi_lengkap.cpp - menolak huruf dan nilai di luar rentang
#include <iostream>

int main() {
    int nilai = 0;
    bool valid = false;

    do {
        std::cout << "Masukkan nilai kanal (0-255): ";
        std::cin >> nilai;

        if (std::cin.fail()) {               // input bukan angka
            std::cin.clear();                // pulihkan cin
            std::cin.ignore(1000, '\n');     // buang sisa input
            std::cout << "Input harus berupa angka. Coba lagi.\n";
        } else if (nilai < 0 || nilai > 255) {
            std::cout << "Nilai harus 0 sampai 255. Coba lagi.\n";
        } else {
            valid = true;
        }
    } while (!valid);

    std::cout << "Nilai diterima: " << nilai << "\n";
    return 0;
}
