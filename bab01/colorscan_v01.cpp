// ==========================================
//  ColorScan v0.1
//  Penganalisis warna sederhana di konsol
// ==========================================
#include <iostream>

int main() {
    // 1. Membaca input
    int r = 0, g = 0, b = 0;

    std::cout << "===== ColorScan v0.1 =====\n";
    std::cout << "Masukkan nilai R G B (0-255): ";
    std::cin >> r >> g >> b;

    // 2. Menghitung
    int kebalikanR = 255 - r;
    int kebalikanG = 255 - g;
    int kebalikanB = 255 - b;

    int abu = (r + g + b) / 3;
    double persen = abu * 100.0 / 255;

    bool terang = abu > 127;

    // 3. Menampilkan hasil
    std::cout << std::boolalpha;
    std::cout << "\n--- Hasil Analisis ---\n";
    std::cout << "Warna asli     : ("
              << r << ", " << g << ", " << b << ")\n";
    std::cout << "Warna kebalikan: (" << kebalikanR << ", "
              << kebalikanG << ", " << kebalikanB << ")\n";
    std::cout << "Nilai abu-abu  : " << abu << "\n";
    std::cout << "Kecerahan      : " << persen << " %\n";
    std::cout << "Warna terang?  : " << terang << "\n";
    return 0;
}
