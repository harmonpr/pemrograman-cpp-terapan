// statistik_piksel.cpp - rata-rata, terkecil, dan terbesar
#include <iostream>

int main() {
    int jumlahPiksel = 0;
    std::cout << "Berapa piksel yang akan dimasukkan? ";
    std::cin >> jumlahPiksel;

    int total = 0;
    int terkecil = 255;
    int terbesar = 0;

    for (int i = 1; i <= jumlahPiksel; i++) {
        int nilai = 0;
        std::cout << "Nilai piksel ke-" << i << ": ";
        std::cin >> nilai;

        total = total + nilai;
        if (nilai < terkecil) {
            terkecil = nilai;
        }
        if (nilai > terbesar) {
            terbesar = nilai;
        }
    }

    if (jumlahPiksel > 0) {
        std::cout << "\nRata-rata: " << total / jumlahPiksel << "\n";
        std::cout << "Terkecil : " << terkecil << "\n";
        std::cout << "Terbesar : " << terbesar << "\n";
    }
    return 0;
}
