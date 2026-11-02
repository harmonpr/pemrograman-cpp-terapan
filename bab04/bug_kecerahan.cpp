// bug_kecerahan.cpp - program yang hasilnya salah
#include <iostream>

int hitungAbu(int r, int g, int b) {
    return (r + g + b) / 3;
}

int persenKecerahan(int abu) {
    int persen = abu / 255 * 100;
    return persen;
}

int main() {
    int r = 200, g = 100, b = 50;
    int abu = hitungAbu(r, g, b);
    int persen = persenKecerahan(abu);
    std::cout << "Kecerahan: " << persen << " %\n";
    return 0;
}
