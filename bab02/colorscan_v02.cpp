// ==========================================
//  ColorScan v0.2
//  Tambahan: validasi, nama warna, menu
// ==========================================
#include <iostream>

int main() {
    // 1. Membaca input
    int r = 0, g = 0, b = 0;

    std::cout << "===== ColorScan v0.2 =====\n";
    std::cout << "Masukkan nilai R G B (0-255): ";
    std::cin >> r >> g >> b;

    // 2. Memeriksa input
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        std::cout << "Error: setiap nilai harus 0 sampai 255.\n";
        return 1;   // program berhenti
    }

    // 3. Menghitung
    int abu = (r + g + b) / 3;
    double persen = abu * 100.0 / 255;

    // 4. Menampilkan menu
    int pilihan = 0;
    std::cout << "\nPilih analisis:\n";
    std::cout << "1. Warna kebalikan\n";
    std::cout << "2. Kecerahan\n";
    std::cout << "3. Kelompok warna\n";
    std::cout << "Pilihan Anda: ";
    std::cin >> pilihan;

    std::cout << "\n--- Hasil ---\n";
    switch (pilihan) {
        case 1:
            std::cout << "Warna kebalikan: (" << 255 - r << ", "
                      << 255 - g << ", " << 255 - b << ")\n";
            break;

        case 2:
            std::cout << "Nilai abu-abu: " << abu << "\n";
            std::cout << "Kecerahan    : " << persen << " %\n";
            if (abu < 85) {
                std::cout << "Kategori     : gelap\n";
            } else if (abu < 170) {
                std::cout << "Kategori     : sedang\n";
            } else {
                std::cout << "Kategori     : terang\n";
            }
            break;

        case 3:
            std::cout << "Kelompok warna: ";
            if (r < 50 && g < 50 && b < 50) {
                std::cout << "hitam\n";
            } else if (r > 200 && g > 200 && b > 200) {
                std::cout << "putih\n";
            } else if (r == g && g == b) {
                std::cout << "abu-abu\n";
            } else if (r >= g && r >= b) {
                std::cout << "kemerahan\n";
            } else if (g >= r && g >= b) {
                std::cout << "kehijauan\n";
            } else {
                std::cout << "kebiruan\n";
            }
            break;

        default:
            std::cout << "Pilihan tidak tersedia.\n";
            break;
    }
    return 0;
}
