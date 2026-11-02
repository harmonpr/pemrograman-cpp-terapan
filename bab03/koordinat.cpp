// koordinat.cpp - perulangan bersarang untuk posisi piksel
#include <iostream>

int main() {
    int jumlahBaris = 3;
    int jumlahKolom = 4;

    for (int baris = 0; baris < jumlahBaris; baris++) {
        for (int kolom = 0; kolom < jumlahKolom; kolom++) {
            std::cout << "(" << baris << "," << kolom << ") ";
        }
        std::cout << "\n";   // pindah ke baris berikutnya
    }
    return 0;
}
