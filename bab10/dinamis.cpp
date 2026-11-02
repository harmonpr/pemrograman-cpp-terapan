// dinamis.cpp - memori dinamis dengan new/delete dan unique_ptr
#include <iostream>
#include <memory>

struct Warna {
    int r;
    int g;
    int b;
};

int main() {
    // 1. Cara lama: new dan delete
    int jumlah = 0;
    std::cout << "Berapa warna? ";
    std::cin >> jumlah;

    Warna* palet = new Warna[jumlah];     // dipesan saat berjalan
    for (int i = 0; i < jumlah; i++) {
        palet[i] = {i * 50, 100, 255 - i * 50};
    }
    std::cout << "Warna terakhir: (" << palet[jumlah - 1].r << ", "
              << palet[jumlah - 1].g << ", " << palet[jumlah - 1].b
              << ")\n";
    delete[] palet;                       // wajib dikembalikan!

    // 2. Cara modern: smart pointer
    std::unique_ptr<Warna> w = std::make_unique<Warna>();
    w->r = 255;
    w->g = 165;
    w->b = 0;
    std::cout << "Warna dari unique_ptr: (" << w->r << ", " << w->g
              << ", " << w->b << ")\n";
    return 0;                             // w dihapus otomatis
}
