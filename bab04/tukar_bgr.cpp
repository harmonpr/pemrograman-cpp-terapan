// tukar_bgr.cpp - menukar dua variabel dengan pass by reference
#include <iostream>

void tukar(int& a, int& b) {
    int sementara = a;
    a = b;
    b = sementara;
}

int main() {
    int k1 = 200, k2 = 100, k3 = 50;   // urutan R, G, B
    std::cout << "RGB: " << k1 << " " << k2 << " " << k3 << "\n";

    tukar(k1, k3);                     // sekarang urutan B, G, R
    std::cout << "BGR: " << k1 << " " << k2 << " " << k3 << "\n";
    return 0;
}
