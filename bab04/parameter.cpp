// parameter.cpp - function dengan parameter
#include <iostream>

void tampilkanWarna(int r, int g, int b) {
    std::cout << "(" << r << ", " << g << ", " << b << ")\n";
}

void tampilkanGaris(int panjang, char karakter) {
    for (int i = 0; i < panjang; i++) {
        std::cout << karakter;
    }
    std::cout << "\n";
}

int main() {
    tampilkanGaris(20, '=');
    tampilkanWarna(255, 0, 0);
    tampilkanWarna(0, 128, 255);
    tampilkanGaris(20, '-');
    return 0;
}
