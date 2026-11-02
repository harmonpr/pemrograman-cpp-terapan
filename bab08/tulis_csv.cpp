// tulis_csv.cpp - menyimpan data warna ke file CSV
#include <fstream>
#include <iostream>

int main() {
    std::ofstream file("warna.csv");
    if (!file) {
        std::cout << "File tidak bisa dibuat!\n";
        return 1;
    }

    file << "nama,r,g,b\n";
    file << "merah,205,30,35\n";
    file << "kuning,240,205,40\n";
    file << "hijau,60,160,55\n";
    file << "biru,40,80,200\n";
    file.close();

    std::cout << "warna.csv berhasil ditulis.\n";
    return 0;
}
