// konversi.cpp - kumpulan function konversi warna
#include <iostream>

int persenKeNilai(double persen) {
    return persen * 255 / 100;
}

double nilaiKePersen(int nilai) {
    return nilai * 100.0 / 255;
}

bool adalahAbuAbu(int r, int g, int b) {
    return r == g && g == b;
}

int main() {
    std::cout << "50% menjadi nilai : " << persenKeNilai(50) << "\n";
    std::cout << "51 menjadi persen : " << nilaiKePersen(51)
              << " %\n";

    std::cout << std::boolalpha;
    std::cout << "(90, 90, 90) abu-abu? " << adalahAbuAbu(90, 90, 90)
              << "\n";
    std::cout << "(90, 10, 90) abu-abu? " << adalahAbuAbu(90, 10, 90)
              << "\n";
    return 0;
}
