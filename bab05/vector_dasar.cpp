// vector_dasar.cpp - wadah yang ukurannya bisa bertambah
#include <iostream>
#include <vector>

int main() {
    std::vector<int> piksel;
    int nilai = 0;

    std::cout << "Masukkan nilai piksel, akhiri dengan -1:\n";
    std::cin >> nilai;
    while (nilai != -1) {
        piksel.push_back(nilai);   // tambahkan di akhir
        std::cin >> nilai;
    }

    std::cout << "Jumlah piksel: " << piksel.size() << "\n";
    std::cout << "Isi vector   : ";
    for (int p : piksel) {
        std::cout << p << " ";
    }
    std::cout << "\n";
    return 0;
}
