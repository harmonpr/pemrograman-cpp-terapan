// ==========================================
//  ColorScan v0.4
//  Program dipecah menjadi function
// ==========================================
#include <iostream>
#include <string>

// ---------- Function bantu ----------
int hitungAbu(int r, int g, int b) {
    return (r + g + b) / 3;
}

std::string kategoriKecerahan(int abu) {
    if (abu < 85) {
        return "gelap";
    } else if (abu < 170) {
        return "sedang";
    }
    return "terang";
}

std::string kelompokWarna(int r, int g, int b) {
    if (r < 50 && g < 50 && b < 50) {
        return "hitam";
    } else if (r > 200 && g > 200 && b > 200) {
        return "putih";
    } else if (r == g && g == b) {
        return "abu-abu";
    } else if (r >= g && r >= b) {
        return "kemerahan";
    } else if (g >= r && g >= b) {
        return "kehijauan";
    }
    return "kebiruan";
}

bool diLuarRentang(int nilai) {
    return nilai < 0 || nilai > 255;
}

// ---------- Function input ----------
void bacaWarna(int& r, int& g, int& b) {
    bool valid = false;
    do {
        std::cout << "\nMasukkan nilai R G B (0-255): ";
        std::cin >> r >> g >> b;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Input harus berupa angka. Coba lagi.\n";
        } else if (diLuarRentang(r) || diLuarRentang(g)
                   || diLuarRentang(b)) {
            std::cout << "Nilai harus 0 sampai 255. Coba lagi.\n";
        } else {
            valid = true;
        }
    } while (!valid);
}

int bacaPilihan() {
    int pilihan = 0;
    std::cout << "Pilihan Anda: ";
    std::cin >> pilihan;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return -1;
    }
    return pilihan;
}

// ---------- Function tampilan ----------
void tampilkanMenu(int r, int g, int b) {
    std::cout << "\nWarna aktif: (" << r << ", " << g << ", "
              << b << ")\n";
    std::cout << "1. Warna kebalikan\n";
    std::cout << "2. Kecerahan\n";
    std::cout << "3. Kelompok warna\n";
    std::cout << "4. Gradasi ke hitam\n";
    std::cout << "5. Ganti warna\n";
    std::cout << "0. Keluar\n";
}

void tampilkanKebalikan(int r, int g, int b) {
    std::cout << "Warna kebalikan: (" << 255 - r << ", "
              << 255 - g << ", " << 255 - b << ")\n";
}

void tampilkanKecerahan(int r, int g, int b) {
    int abu = hitungAbu(r, g, b);
    std::cout << "Nilai abu-abu: " << abu << "\n";
    std::cout << "Kecerahan    : " << abu * 100.0 / 255 << " %\n";
    std::cout << "Kategori     : " << kategoriKecerahan(abu) << "\n";
}

void tampilkanGradasi(int r, int g, int b) {
    for (int persen = 100; persen >= 0; persen = persen - 25) {
        std::cout << persen << "% : (" << r * persen / 100 << ", "
                  << g * persen / 100 << ", "
                  << b * persen / 100 << ")\n";
    }
}

// ---------- Program utama ----------
int main() {
    int r = 0, g = 0, b = 0;
    int pilihan = 0;

    std::cout << "===== ColorScan v0.4 =====\n";
    bacaWarna(r, g, b);

    do {
        tampilkanMenu(r, g, b);
        pilihan = bacaPilihan();
        std::cout << "\n--- Hasil ---\n";

        switch (pilihan) {
            case 1: tampilkanKebalikan(r, g, b); break;
            case 2: tampilkanKecerahan(r, g, b); break;
            case 3:
                std::cout << "Kelompok warna: "
                          << kelompokWarna(r, g, b) << "\n";
                break;
            case 4: tampilkanGradasi(r, g, b); break;
            case 5: bacaWarna(r, g, b); break;
            case 0: std::cout << "Terima kasih.\n"; break;
            default: std::cout << "Pilihan tidak tersedia.\n";
        }
    } while (pilihan != 0);

    return 0;
}
