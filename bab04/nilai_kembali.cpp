// nilai_kembali.cpp - function yang mengembalikan nilai
#include <iostream>
#include <string>

int hitungAbu(int r, int g, int b) {
    return (r + g + b) / 3;
}

int jepit(int nilai) {
    if (nilai > 255) {
        return 255;
    }
    if (nilai < 0) {
        return 0;
    }
    return nilai;
}

std::string kategoriKecerahan(int abu) {
    if (abu < 85) {
        return "gelap";
    } else if (abu < 170) {
        return "sedang";
    }
    return "terang";
}

int main() {
    int abu = hitungAbu(200, 100, 50);
    std::cout << "Nilai abu-abu: " << abu << "\n";
    std::cout << "Kategori     : " << kategoriKecerahan(abu) << "\n";

    std::cout << "jepit(300)   : " << jepit(300) << "\n";
    std::cout << "jepit(-20)   : " << jepit(-20) << "\n";
    std::cout << "jepit(128)   : " << jepit(128) << "\n";
    return 0;
}
