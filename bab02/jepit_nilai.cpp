// jepit_nilai.cpp - menjaga nilai tetap di rentang 0-255
#include <iostream>

int main() {
    int r = 0;
    std::cout << "Nilai merah awal: ";
    std::cin >> r;

    r = r + 80;   // mencerahkan
    std::cout << "Setelah ditambah 80: " << r << "\n";

    if (r > 255) {
        r = 255;
    }
    if (r < 0) {
        r = 0;
    }
    std::cout << "Setelah dijepit    : " << r << "\n";
    return 0;
}
