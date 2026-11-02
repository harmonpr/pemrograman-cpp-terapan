// by_value.cpp - parameter menerima salinan nilai
#include <iostream>

void cerahkan(int nilai) {
    nilai = nilai + 50;
    std::cout << "Di dalam function: " << nilai << "\n";
}

int main() {
    int merah = 100;
    cerahkan(merah);
    std::cout << "Di dalam main    : " << merah << "\n";
    return 0;
}
