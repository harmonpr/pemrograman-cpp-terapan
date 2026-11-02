// array_warna.cpp - menyimpan tiga kanal dalam satu array
#include <iostream>
#include <string>

int main() {
    int kanal[3] = {200, 100, 50};
    std::string nama[3] = {"Merah", "Hijau", "Biru"};

    for (int i = 0; i < 3; i++) {
        std::cout << nama[i] << " = " << kanal[i] << "\n";
    }

    kanal[2] = 255;   // mengubah elemen ketiga (biru)
    std::cout << "Biru sekarang = " << kanal[2] << "\n";
    return 0;
}
