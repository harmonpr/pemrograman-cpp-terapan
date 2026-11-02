// ==========================================
//  ColorScan v0.5
//  Mengolah "gambar" abu-abu berupa matriks
//  dengan perintah teks
// ==========================================
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using Gambar = std::vector<std::vector<int>>;

// ---------- Membuat gambar contoh ----------
Gambar buatGambarContoh() {
    const int TINGGI = 9, LEBAR = 16;
    Gambar gambar(TINGGI, std::vector<int>(LEBAR, 0));

    for (int y = 0; y < TINGGI; y++) {
        for (int x = 0; x < LEBAR; x++) {
            gambar[y][x] = 90 + x * 8;        // latar gradasi
            int dx = x - 8, dy = (y - 4) * 2;
            if (dx * dx + dy * dy < 30) {     // objek bulat gelap
                gambar[y][x] = 20;
            }
        }
    }
    return gambar;
}

// ---------- Function bantu ----------
int jepit(int nilai) {
    if (nilai > 255) {
        return 255;
    }
    if (nilai < 0) {
        return 0;
    }
    return nilai;
}

char keKarakter(int nilai) {
    if (nilai < 64) {
        return '@';
    }
    if (nilai < 128) {
        return '#';
    }
    if (nilai < 192) {
        return '+';
    }
    return '.';
}

bool adalahAngka(const std::string& teks) {
    if (teks.empty() || teks.length() > 4) {
        return false;
    }
    for (std::size_t i = 0; i < teks.length(); i++) {
        bool tandaMinus = (i == 0 && teks[i] == '-'
                           && teks.length() > 1);
        if (!tandaMinus && (teks[i] < '0' || teks[i] > '9')) {
            return false;
        }
    }
    return true;
}

// ---------- Tampilan ----------
void tampilkan(const Gambar& gambar) {
    for (const std::vector<int>& baris : gambar) {
        for (int nilai : baris) {
            std::cout << keKarakter(nilai);
        }
        std::cout << "\n";
    }
}

void tampilkanAngka(const Gambar& gambar) {
    for (const std::vector<int>& baris : gambar) {
        for (int nilai : baris) {
            std::cout << std::setw(4) << nilai;
        }
        std::cout << "\n";
    }
}

void tampilkanHistogram(const Gambar& gambar) {
    std::string label[4] = {"  0- 63", " 64-127", "128-191",
                            "192-255"};
    int hitung[4] = {0, 0, 0, 0};
    for (const std::vector<int>& baris : gambar) {
        for (int nilai : baris) {
            hitung[nilai / 64]++;
        }
    }
    for (int i = 0; i < 4; i++) {
        std::cout << label[i] << " | ";
        for (int j = 0; j < hitung[i] / 4; j++) {   // 1 * = 4
            std::cout << "*";
        }
        std::cout << " (" << hitung[i] << ")\n";
    }
}

void tampilkanBantuan() {
    std::cout << "Perintah yang tersedia:\n"
              << "  tampil        gambar sebagai karakter\n"
              << "  angka         gambar sebagai angka\n"
              << "  balik         membalik terang-gelap\n"
              << "  cerah N       menambah kecerahan N\n"
              << "  ambang N      hitam-putih dengan batas N\n"
              << "  cermin        membalik kiri-kanan\n"
              << "  histogram     sebaran kecerahan\n"
              << "  reset         kembali ke gambar awal\n"
              << "  keluar        mengakhiri program\n";
}

// ---------- Pengolahan ----------
void balikWarna(Gambar& gambar) {
    for (std::vector<int>& baris : gambar) {
        for (int& nilai : baris) {
            nilai = 255 - nilai;
        }
    }
}

void cerahkan(Gambar& gambar, int jumlah) {
    for (std::vector<int>& baris : gambar) {
        for (int& nilai : baris) {
            nilai = jepit(nilai + jumlah);
        }
    }
}

void ambang(Gambar& gambar, int batas) {
    for (std::vector<int>& baris : gambar) {
        for (int& nilai : baris) {
            if (nilai >= batas) {
                nilai = 255;
            } else {
                nilai = 0;
            }
        }
    }
}

void cerminkan(Gambar& gambar) {
    for (std::vector<int>& baris : gambar) {
        int kiri = 0;
        int kanan = baris.size() - 1;
        while (kiri < kanan) {
            int sementara = baris[kiri];
            baris[kiri] = baris[kanan];
            baris[kanan] = sementara;
            kiri++;
            kanan--;
        }
    }
}

// ---------- Program utama ----------
int main() {
    Gambar gambar = buatGambarContoh();
    std::string baris;

    std::cout << "===== ColorScan v0.5 =====\n";
    std::cout << "Ketik 'bantuan' untuk melihat daftar perintah.\n";

    while (true) {
        std::cout << "\n> ";
        if (!std::getline(std::cin, baris)) {   // input habis
            break;
        }

        // pecah menjadi perintah dan argumen
        std::string perintah = baris;
        std::string argumen = "";
        std::size_t spasi = baris.find(' ');
        if (spasi != std::string::npos) {
            perintah = baris.substr(0, spasi);
            argumen = baris.substr(spasi + 1);
        }

        if (perintah == "keluar") {
            std::cout << "Terima kasih.\n";
            break;
        } else if (perintah == "bantuan") {
            tampilkanBantuan();
        } else if (perintah == "tampil") {
            tampilkan(gambar);
        } else if (perintah == "angka") {
            tampilkanAngka(gambar);
        } else if (perintah == "histogram") {
            tampilkanHistogram(gambar);
        } else if (perintah == "balik") {
            balikWarna(gambar);
            tampilkan(gambar);
        } else if (perintah == "cermin") {
            cerminkan(gambar);
            tampilkan(gambar);
        } else if (perintah == "reset") {
            gambar = buatGambarContoh();
            tampilkan(gambar);
        } else if (perintah == "cerah" || perintah == "ambang") {
            if (!adalahAngka(argumen)) {
                std::cout << "Perintah " << perintah
                          << " memerlukan angka, contoh: "
                          << perintah << " 40\n";
            } else if (perintah == "cerah") {
                cerahkan(gambar, std::stoi(argumen));
                tampilkan(gambar);
            } else {
                ambang(gambar, std::stoi(argumen));
                tampilkan(gambar);
            }
        } else if (perintah != "") {
            std::cout << "Perintah tidak dikenal: " << perintah
                      << ". Ketik 'bantuan'.\n";
        }
    }
    return 0;
}
