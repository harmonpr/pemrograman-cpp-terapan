// gambar_kotak.cpp - function yang memakai perulangan bersarang
#include <iostream>

void gambarKotak(int tinggi, int lebar, char isi) {
    for (int baris = 0; baris < tinggi; baris++) {
        for (int kolom = 0; kolom < lebar; kolom++) {
            std::cout << isi;
        }
        std::cout << "\n";
    }
}

void gambarPapanCatur(int ukuran) {
    for (int baris = 0; baris < ukuran; baris++) {
        for (int kolom = 0; kolom < ukuran; kolom++) {
            if ((baris + kolom) % 2 == 0) {
                std::cout << "##";
            } else {
                std::cout << "..";
            }
        }
        std::cout << "\n";
    }
}

int main() {
    gambarKotak(2, 12, '@');
    std::cout << "\n";
    gambarKotak(3, 6, '+');
    std::cout << "\n";
    gambarPapanCatur(3);
    return 0;
}
