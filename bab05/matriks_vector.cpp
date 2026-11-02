// matriks_vector.cpp - gambar dengan ukuran bebas
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    int tinggi = 0, lebar = 0;
    std::cout << "Tinggi dan lebar gambar: ";
    std::cin >> tinggi >> lebar;

    // tinggi baris, setiap baris berisi lebar nilai 0
    std::vector<std::vector<int>> gambar(
        tinggi, std::vector<int>(lebar, 0));

    // isi dengan gradasi dari kiri ke kanan
    for (int y = 0; y < tinggi; y++) {
        for (int x = 0; x < lebar; x++) {
            gambar[y][x] = x * 255 / (lebar - 1);
        }
    }

    std::cout << "Ukuran: " << gambar.size() << " x "
              << gambar[0].size() << "\n";
    for (const std::vector<int>& baris : gambar) {
        for (int nilai : baris) {
            std::cout << std::setw(4) << nilai;
        }
        std::cout << "\n";
    }
    return 0;
}
