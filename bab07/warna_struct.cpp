// warna_struct.cpp - mengelompokkan data warna dengan struct
#include <iostream>
#include <string>
#include <vector>

struct Warna {
    std::string nama;
    int r;
    int g;
    int b;
};

int kecerahan(const Warna& w) {
    return (w.r + w.g + w.b) / 3;
}

Warna kebalikan(const Warna& w) {
    Warna hasil = {"kebalikan " + w.nama, 255 - w.r, 255 - w.g,
                   255 - w.b};
    return hasil;
}

void tampilkan(const Warna& w) {
    std::cout << w.nama << " (" << w.r << ", " << w.g << ", " << w.b
              << "), kecerahan " << kecerahan(w) << "\n";
}

int main() {
    Warna oranye = {"oranye", 255, 165, 0};
    oranye.g = 140;                  // mengubah satu anggota
    tampilkan(oranye);
    tampilkan(kebalikan(oranye));

    std::vector<Warna> palet = {
        {"merah", 220, 30, 40},
        {"hijau", 60, 160, 55},
        {"biru", 40, 80, 200}
    };
    std::cout << "\nIsi palet:\n";
    for (const Warna& w : palet) {
        tampilkan(w);
    }
    return 0;
}
