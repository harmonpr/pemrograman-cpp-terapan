// prototipe.cpp - memperkenalkan function lebih dulu
#include <iostream>

void tampilkanGaris();   // prototipe

int main() {
    tampilkanGaris();
    std::cout << "Prototipe membuat urutan tidak masalah.\n";
    tampilkanGaris();
    return 0;
}

void tampilkanGaris() {
    std::cout << "==============================\n";
}
