// vector_function.cpp - mengirim gambar ke function
#include <iomanip>
#include <iostream>
#include <vector>

using Gambar = std::vector<std::vector<int>>;

void tampilkan(const Gambar& gambar) {
    for (const std::vector<int>& baris : gambar) {
        for (int nilai : baris) {
            std::cout << std::setw(4) << nilai;
        }
        std::cout << "\n";
    }
}

void balikWarna(Gambar& gambar) {
    for (std::vector<int>& baris : gambar) {
        for (int& nilai : baris) {
            nilai = 255 - nilai;
        }
    }
}

int main() {
    Gambar gambar = {
        {0, 50, 100},
        {150, 200, 255}
    };

    std::cout << "Asli:\n";
    tampilkan(gambar);
    balikWarna(gambar);
    std::cout << "Setelah dibalik:\n";
    tampilkan(gambar);
    return 0;
}
