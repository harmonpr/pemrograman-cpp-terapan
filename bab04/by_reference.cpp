// by_reference.cpp - parameter mengubah variabel aslinya
#include <iostream>

void cerahkan(int& nilai) {
    nilai = nilai + 50;
    std::cout << "Di dalam function: " << nilai << "\n";
}

int main() {
    int merah = 100;
    cerahkan(merah);
    std::cout << "Di dalam main    : " << merah << "\n";
    return 0;
}
