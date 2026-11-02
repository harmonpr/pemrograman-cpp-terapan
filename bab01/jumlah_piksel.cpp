// jumlah_piksel.cpp - menghitung jumlah piksel dan ukuran gambar
#include <iostream>

int main() {
    int lebar = 0, tinggi = 0;

    std::cout << "Lebar gambar : ";
    std::cin >> lebar;
    std::cout << "Tinggi gambar: ";
    std::cin >> tinggi;

    int jumlahPiksel = lebar * tinggi;
    int ukuranByte = jumlahPiksel * 3;   // 3 byte per piksel
    double ukuranKB = ukuranByte / 1024.0;
    double ukuranMB = ukuranKB / 1024.0;

    std::cout << "Jumlah piksel: " << jumlahPiksel << "\n";
    std::cout << "Ukuran       : " << ukuranByte << " byte\n";
    std::cout << "             = " << ukuranKB << " KB\n";
    std::cout << "             = " << ukuranMB << " MB\n";
    return 0;
}
