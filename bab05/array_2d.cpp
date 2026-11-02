// array_2d.cpp - gambar kecil sebagai array dua dimensi
#include <iomanip>
#include <iostream>

int main() {
    const int TINGGI = 4;
    const int LEBAR = 6;
    int gambar[TINGGI][LEBAR] = {
        { 10,  10,  10,  10,  10,  10},
        { 10, 200, 200, 200, 200,  10},
        { 10, 200, 255, 255, 200,  10},
        { 10,  10,  10,  10,  10,  10}
    };

    for (int y = 0; y < TINGGI; y++) {
        for (int x = 0; x < LEBAR; x++) {
            std::cout << std::setw(4) << gambar[y][x];
        }
        std::cout << "\n";
    }

    std::cout << "Piksel (2,3) bernilai " << gambar[2][3] << "\n";
    return 0;
}
