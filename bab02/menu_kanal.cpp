// menu_kanal.cpp - memilih kanal dengan switch
#include <iostream>

int main() {
    int r = 200, g = 100, b = 50;
    int pilihan = 0;

    std::cout << "Warna: (" << r << ", " << g << ", " << b << ")\n";
    std::cout << "1. Lihat nilai merah\n";
    std::cout << "2. Lihat nilai hijau\n";
    std::cout << "3. Lihat nilai biru\n";
    std::cout << "Pilihan Anda: ";
    std::cin >> pilihan;

    switch (pilihan) {
        case 1:
            std::cout << "Merah = " << r << "\n";
            break;
        case 2:
            std::cout << "Hijau = " << g << "\n";
            break;
        case 3:
            std::cout << "Biru = " << b << "\n";
            break;
        default:
            std::cout << "Pilihan tidak tersedia.\n";
            break;
    }
    return 0;
}
