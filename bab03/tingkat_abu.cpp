// tingkat_abu.cpp - menampilkan tingkat abu-abu dengan for
#include <iostream>

int main() {
    std::cout << "Tingkat abu-abu dari hitam ke putih:\n";

    for (int nilai = 0; nilai <= 255; nilai = nilai + 51) {
        std::cout << "(" << nilai << ", " << nilai << ", "
                  << nilai << ")\n";
    }

    std::cout << "Selesai.\n";
    return 0;
}
