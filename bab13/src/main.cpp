// main.cpp - ColorScan v1.0: program utama dan mode perintah
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include "deteksi.hpp"
#include "detektor.hpp"
#include "interaktif.hpp"
#include "laporan.hpp"
#include "teks.hpp"

namespace {

// Semua data yang dipakai selama program berjalan
struct Sesi {
    DaftarDetektor daftar;
    cv::Mat gambar;
    cv::Mat gambarHasil;
    std::vector<HasilDeteksi> hasilTerakhir;
    int luasMin = 100;
};

void tampilkanBantuan() {
    std::cout
        << "Perintah yang tersedia:\n"
        << "  buka FILE                 membuka gambar\n"
        << "  daftar                    daftar detektor\n"
        << "  tambah warna NAMA R G B [TOL]\n"
        << "  tambah terang N           kecerahan >= N\n"
        << "  tambah gelap N            kecerahan <= N\n"
        << "  hapus NOMOR               menghapus detektor\n"
        << "  luas N                    luas benda minimum\n"
        << "  jalankan                  mencari semua benda\n"
        << "  statistik                 ringkasan hasil\n"
        << "  simpan FILE               menyimpan hasil\n"
        << "  proses FOLDER             memproses satu folder\n"
        << "  interaktif SUMBER         gambar, video, atau kamera\n"
        << "  keluar                    mengakhiri program\n";
}

void tampilkanDaftar(const DaftarDetektor& daftar) {
    if (daftar.empty()) {
        std::cout << "Daftar detektor kosong.\n";
    }
    for (std::size_t i = 0; i < daftar.size(); i++) {
        std::cout << i + 1 << ". " << daftar[i]->nama() << " : "
                  << daftar[i]->keterangan() << "\n";
    }
}

void tambahDetektor(const std::vector<std::string>& kata,
                    DaftarDetektor& daftar) {
    const std::string& jenis = kata.at(1);
    if (jenis == "warna") {
        int tol = 60;
        if (kata.size() >= 7) {
            tol = std::stoi(kata[6]);
        }
        daftar.push_back(std::make_unique<DetektorWarna>(
            kata.at(2), std::stoi(kata.at(3)), std::stoi(kata.at(4)),
            std::stoi(kata.at(5)), tol));
    } else if (jenis == "terang") {
        daftar.push_back(
            std::make_unique<DetektorTerang>(std::stoi(kata.at(2))));
    } else if (jenis == "gelap") {
        daftar.push_back(
            std::make_unique<DetektorGelap>(std::stoi(kata.at(2))));
    } else {
        std::cout << "Jenis tidak dikenal: " << jenis << "\n";
        return;
    }
    std::cout << "Ditambahkan: " << daftar.back()->nama() << "\n";
}

void hapusDetektor(const std::string& nomorTeks,
                   DaftarDetektor& daftar) {
    int nomor = std::stoi(nomorTeks);
    int jumlah = daftar.size();
    if (nomor < 1 || nomor > jumlah) {
        std::cout << "Nomor tidak ada dalam daftar.\n";
        return;
    }
    std::cout << "Dihapus: " << daftar[nomor - 1]->nama() << "\n";
    daftar.erase(daftar.begin() + (nomor - 1));
}

void bukaGambar(const std::string& nama, Sesi& sesi) {
    cv::Mat baru = cv::imread(nama);
    if (baru.empty()) {
        std::cout << "Gagal membuka " << nama << "\n";
        return;
    }
    sesi.gambar = baru;
    sesi.gambarHasil = cv::Mat();
    sesi.hasilTerakhir.clear();
    std::cout << "Berhasil membuka " << nama << " (" << baru.cols
              << " x " << baru.rows << ")\n";
}

void jalankanDeteksi(Sesi& sesi) {
    if (sesi.gambar.empty()) {
        std::cout << "Belum ada gambar. Gunakan 'buka'.\n";
        return;
    }
    sesi.hasilTerakhir = jalankanSemua(
        sesi.daftar, sesi.gambar, sesi.luasMin, sesi.gambarHasil);
    cv::imshow("Hasil", sesi.gambarHasil);
    cv::waitKey(0);
    cv::destroyWindow("Hasil");
}

void simpanHasil(const std::string& nama, const Sesi& sesi) {
    if (sesi.gambarHasil.empty()) {
        std::cout << "Belum ada hasil. Jalankan 'jalankan'.\n";
    } else if (cv::imwrite(nama, sesi.gambarHasil)) {
        std::cout << "Tersimpan di " << nama << "\n";
    }
}

// Menjalankan satu perintah; mengembalikan false jika harus keluar
bool jalankanPerintah(const std::vector<std::string>& kata,
                      Sesi& sesi) {
    const std::string& perintah = kata[0];
    if (perintah == "keluar") {
        return false;
    } else if (perintah == "bantuan") {
        tampilkanBantuan();
    } else if (perintah == "buka") {
        bukaGambar(kata.at(1), sesi);
    } else if (perintah == "daftar") {
        tampilkanDaftar(sesi.daftar);
    } else if (perintah == "tambah") {
        tambahDetektor(kata, sesi.daftar);
    } else if (perintah == "hapus") {
        hapusDetektor(kata.at(1), sesi.daftar);
    } else if (perintah == "luas") {
        sesi.luasMin = std::stoi(kata.at(1));
        std::cout << "Luas minimum sekarang " << sesi.luasMin << "\n";
    } else if (perintah == "jalankan") {
        jalankanDeteksi(sesi);
    } else if (perintah == "statistik") {
        tampilkanStatistik(sesi.hasilTerakhir);
    } else if (perintah == "simpan") {
        simpanHasil(kata.at(1), sesi);
    } else if (perintah == "proses") {
        prosesFolder(kata.at(1), sesi.daftar, sesi.luasMin);
    } else if (perintah == "interaktif") {
        modeInteraktif(kata.at(1), sesi.daftar);
    } else {
        std::cout << "Perintah tidak dikenal. Ketik 'bantuan'.\n";
    }
    return true;
}

}  // namespace

int main() {
    Sesi sesi;
    muatDariCsv("warna.csv", sesi.daftar);
    std::cout << "===== ColorScan v1.0 =====\n"
              << sesi.daftar.size() << " detektor dimuat. "
              << "Ketik 'bantuan' untuk daftar perintah.\n";

    std::string baris;
    while (true) {
        std::cout << "\n> ";
        if (!std::getline(std::cin, baris)) {
            break;
        }
        std::vector<std::string> kata = pecah(baris, ' ');
        if (kata.empty()) {
            continue;
        }
        try {
            if (!jalankanPerintah(kata, sesi)) {
                break;
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Argumen kurang. Ketik 'bantuan'.\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "Argumen harus berupa angka.\n";
        } catch (const cv::Exception& e) {
            std::cout << "Error OpenCV: " << e.func << "\n";
        }
    }
    std::cout << "Terima kasih telah memakai ColorScan.\n";
    return 0;
}
