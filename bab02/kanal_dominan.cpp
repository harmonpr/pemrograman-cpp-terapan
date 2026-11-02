// kanal_dominan.cpp - mencari kanal dengan nilai terbesar
#include <iostream>

int main() {
    int r = 0, g = 0, b = 0;
    std::cout << "Masukkan R G B: ";
    std::cin >> r >> g >> b;

    if (r >= g && r >= b) {
        std::cout << "Kanal dominan: MERAH (" << r << ")\n";
    } else if (g >= r && g >= b) {
        std::cout << "Kanal dominan: HIJAU (" << g << ")\n";
    } else {
        std::cout << "Kanal dominan: BIRU (" << b << ")\n";
    }
    return 0;
}
