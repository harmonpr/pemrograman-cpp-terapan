// rata_piksel.cpp - mengolah deretan nilai piksel
#include <iostream>

int main() {
    const int JUMLAH = 8;
    int baris[JUMLAH] = {12, 40, 85, 130, 170, 210, 240, 255};

    int total = 0;
    for (int i = 0; i < JUMLAH; i++) {
        total = total + baris[i];
    }
    std::cout << "Rata-rata : " << total / JUMLAH << "\n";

    std::cout << "Dibalik   : ";
    for (int i = 0; i < JUMLAH; i++) {
        std::cout << 255 - baris[i] << " ";
    }
    std::cout << "\n";
    return 0;
}
