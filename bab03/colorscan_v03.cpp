// ==========================================
//  ColorScan v0.3
//  Tambahan: menu berulang, validasi input,
//            gradasi warna
// ==========================================
#include <iostream>

int main() {
    int r = 0, g = 0, b = 0;
    int pilihan = 0;
    bool perluWarnaBaru = true;

    std::cout << "===== ColorScan v0.3 =====\n";

    do {
        // 1. Membaca warna (jika diperlukan) dengan validasi
        if (perluWarnaBaru) {
            bool valid = false;
            do {
                std::cout << "\nMasukkan nilai R G B (0-255): ";
                std::cin >> r >> g >> b;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Input harus berupa angka. "
                              << "Coba lagi.\n";
                } else if (r < 0 || r > 255 || g < 0 || g > 255
                           || b < 0 || b > 255) {
                    std::cout << "Nilai harus 0 sampai 255. "
                              << "Coba lagi.\n";
                } else {
                    valid = true;
                }
            } while (!valid);
            perluWarnaBaru = false;
        }

        // 2. Menampilkan menu
        std::cout << "\nWarna aktif: ("
                  << r << ", " << g << ", " << b << ")\n";
        std::cout << "1. Warna kebalikan\n";
        std::cout << "2. Kecerahan\n";
        std::cout << "3. Kelompok warna\n";
        std::cout << "4. Gradasi ke hitam\n";
        std::cout << "5. Ganti warna\n";
        std::cout << "0. Keluar\n";
        std::cout << "Pilihan Anda: ";
        std::cin >> pilihan;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            pilihan = -1;   // dianggap pilihan tidak tersedia
        }

        // 3. Menjalankan pilihan
        int abu = (r + g + b) / 3;
        std::cout << "\n--- Hasil ---\n";

        switch (pilihan) {
            case 1:
                std::cout << "Warna kebalikan: (" << 255 - r << ", "
                          << 255 - g << ", " << 255 - b << ")\n";
                break;

            case 2:
                std::cout << "Nilai abu-abu: " << abu << "\n";
                std::cout << "Kecerahan    : "
                          << abu * 100.0 / 255 << " %\n";
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

            case 4:
                for (int persen = 100; persen >= 0;
                     persen = persen - 25) {
                    std::cout << persen << "% : ("
                              << r * persen / 100 << ", "
                              << g * persen / 100 << ", "
                              << b * persen / 100 << ")\n";
                }
                break;

            case 5:
                perluWarnaBaru = true;
                std::cout << "Silakan masukkan warna baru.\n";
                break;

            case 0:
                std::cout << "Terima kasih.\n";
                break;

            default:
                std::cout << "Pilihan tidak tersedia.\n";
                break;
        }
    } while (pilihan != 0);

    return 0;
}
