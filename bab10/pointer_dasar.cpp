// pointer_dasar.cpp - variabel yang menyimpan alamat
#include <iostream>

void tukarPointer(int* a, int* b) {
    int sementara = *a;
    *a = *b;
    *b = sementara;
}

int main() {
    int merah = 200;
    int* p = &merah;          // p menyimpan alamat merah

    std::cout << "merah        = " << merah << "\n";
    std::cout << "alamat merah = " << &merah << "\n";
    std::cout << "isi p        = " << p << "\n";
    std::cout << "*p           = " << *p << "\n";

    *p = 255;                 // mengubah merah melalui p
    std::cout << "Setelah *p = 255, merah = " << merah << "\n";

    int* kosong = nullptr;    // pointer yang belum menunjuk apa pun
    if (kosong == nullptr) {
        std::cout << "Pointer kosong tidak boleh dipakai.\n";
    }

    int r = 200, b = 50;
    tukarPointer(&r, &b);
    std::cout << "Setelah ditukar: r = " << r << ", b = " << b
              << "\n";
    return 0;
}
