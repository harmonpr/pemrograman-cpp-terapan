// kelas_warna.cpp - data dan function digabung dalam class
#include <iostream>
#include <string>

class Warna {
public:
    int r;
    int g;
    int b;

    int kecerahan() const {
        return (r + g + b) / 3;
    }

    Warna kebalikan() const {
        Warna hasil;
        hasil.r = 255 - r;
        hasil.g = 255 - g;
        hasil.b = 255 - b;
        return hasil;
    }

    void tampilkan() const {
        std::cout << "(" << r << ", " << g << ", " << b
                  << "), kecerahan " << kecerahan() << "\n";
    }
};

int main() {
    Warna oranye;
    oranye.r = 255;
    oranye.g = 140;
    oranye.b = 0;

    oranye.tampilkan();
    oranye.kebalikan().tampilkan();
    return 0;
}
