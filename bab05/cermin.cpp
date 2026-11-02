// cermin.cpp - membalik gambar secara horizontal
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

void cerminkan(Gambar& gambar) {
    for (std::vector<int>& baris : gambar) {
        int kiri = 0;
        int kanan = baris.size() - 1;
        while (kiri < kanan) {
            int sementara = baris[kiri];
            baris[kiri] = baris[kanan];
            baris[kanan] = sementara;
            kiri++;
            kanan--;
        }
    }
}

int main() {
    Gambar gambar = {
        {10, 20, 30, 40},
        {50, 60, 70, 80}
    };
    tampilkan(gambar);
    cerminkan(gambar);
    std::cout << "Setelah dicerminkan:\n";
    tampilkan(gambar);
    return 0;
}
