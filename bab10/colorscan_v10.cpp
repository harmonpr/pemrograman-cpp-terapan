// ==========================================
//  ColorScan v0.10
//  Daftar detektor yang bisa diatur saat
//  program berjalan (unique_ptr)
// ==========================================
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

// ---------- Class detektor ----------
class Detektor {
public:
    Detektor(const std::string& nama, const cv::Scalar& garis)
        : nama_(nama), garis_(garis) {}
    virtual ~Detektor() {}

    std::string nama() const { return nama_; }
    cv::Scalar warnaGaris() const { return garis_; }
    virtual bool cocok(const cv::Vec3b& p) const = 0;
    virtual std::string keterangan() const = 0;

private:
    std::string nama_;
    cv::Scalar garis_;
};

class DetektorWarna : public Detektor {
public:
    DetektorWarna(const std::string& nama, int r, int g, int b,
                  int tol)
        : Detektor(nama, cv::Scalar(b, g, r)),
          r_(r), g_(g), b_(b), tol_(tol) {}

    bool cocok(const cv::Vec3b& p) const override {
        return std::abs(p[2] - r_) <= tol_
               && std::abs(p[1] - g_) <= tol_
               && std::abs(p[0] - b_) <= tol_;
    }
    std::string keterangan() const override {
        return "warna (" + std::to_string(r_) + ", " +
               std::to_string(g_) + ", " + std::to_string(b_) +
               "), toleransi " + std::to_string(tol_);
    }

private:
    int r_, g_, b_, tol_;
};

class DetektorTerang : public Detektor {
public:
    DetektorTerang(int batas)
        : Detektor("terang", cv::Scalar(255, 255, 255)),
          batas_(batas) {}

    bool cocok(const cv::Vec3b& p) const override {
        return (p[0] + p[1] + p[2]) / 3 >= batas_;
    }
    std::string keterangan() const override {
        return "kecerahan >= " + std::to_string(batas_);
    }

private:
    int batas_;
};

class DetektorGelap : public Detektor {
public:
    DetektorGelap(int batas)
        : Detektor("gelap", cv::Scalar(0, 0, 0)), batas_(batas) {}

    bool cocok(const cv::Vec3b& p) const override {
        return (p[0] + p[1] + p[2]) / 3 <= batas_;
    }
    std::string keterangan() const override {
        return "kecerahan <= " + std::to_string(batas_);
    }

private:
    int batas_;
};

using DaftarDetektor = std::vector<std::unique_ptr<Detektor>>;

// ---------- Deteksi ----------
struct HasilDeteksi {
    std::string nama;
    int jumlahPiksel;
    cv::Rect kotak;
};

HasilDeteksi deteksi(const Detektor& d, const cv::Mat& gambar) {
    int xMin = gambar.cols, yMin = gambar.rows;
    int xMax = -1, yMax = -1;
    int jumlah = 0;
    for (int y = 0; y < gambar.rows; y++) {
        const cv::Vec3b* baris = gambar.ptr<cv::Vec3b>(y);
        for (int x = 0; x < gambar.cols; x++) {
            if (d.cocok(baris[x])) {
                jumlah++;
                if (x < xMin) {
                    xMin = x;
                }
                if (x > xMax) {
                    xMax = x;
                }
                if (y < yMin) {
                    yMin = y;
                }
                if (y > yMax) {
                    yMax = y;
                }
            }
        }
    }
    HasilDeteksi hasil = {d.nama(), jumlah, cv::Rect()};
    if (jumlah > 0) {
        hasil.kotak = cv::Rect(xMin, yMin, xMax - xMin + 1,
                               yMax - yMin + 1);
    }
    return hasil;
}

void tandai(cv::Mat& gambar, const HasilDeteksi& h,
            const Detektor& d) {
    cv::rectangle(gambar, h.kotak, cv::Scalar(0, 0, 0), 4);
    cv::rectangle(gambar, h.kotak, d.warnaGaris(), 2);
    cv::Point posisi(h.kotak.x, h.kotak.y - 8);
    if (posisi.y < 15) {
        posisi.y = h.kotak.y + 20;
    }
    cv::putText(gambar, h.nama, posisi, cv::FONT_HERSHEY_SIMPLEX,
                0.6, cv::Scalar(0, 0, 0), 2);
}

// ---------- Teks dan file ----------
std::vector<std::string> pecah(const std::string& baris,
                               char pemisah) {
    std::vector<std::string> bagian;
    std::string sekarang = "";
    for (char c : baris) {
        if (c == pemisah) {
            if (sekarang != "") {
                bagian.push_back(sekarang);
            }
            sekarang = "";
        } else {
            sekarang = sekarang + c;
        }
    }
    if (sekarang != "") {
        bagian.push_back(sekarang);
    }
    return bagian;
}

void muatDariCsv(const std::string& nama, DaftarDetektor& daftar) {
    std::ifstream file(nama);
    if (!file) {
        std::cout << "Peringatan: " << nama << " tidak ditemukan.\n";
        return;
    }
    std::string baris;
    std::getline(file, baris);
    while (std::getline(file, baris)) {
        std::vector<std::string> k = pecah(baris, ',');
        try {
            daftar.push_back(std::make_unique<DetektorWarna>(
                k.at(0), std::stoi(k.at(1)), std::stoi(k.at(2)),
                std::stoi(k.at(3)), 60));
        } catch (const std::exception& e) {
            std::cout << "Baris dilewati: " << baris << "\n";
        }
    }
}

// ---------- Perintah ----------
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
    std::string jenis = kata.at(1);
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

cv::Mat jalankanSemua(const DaftarDetektor& daftar,
                      const cv::Mat& gambar) {
    cv::Mat hasil = gambar.clone();     // gambar asli tidak diubah
    for (const std::unique_ptr<Detektor>& d : daftar) {
        HasilDeteksi h = deteksi(*d, gambar);
        std::cout << h.nama << ": " << h.jumlahPiksel << " piksel\n";
        if (h.jumlahPiksel > 0) {
            tandai(hasil, h, *d);
        }
    }
    return hasil;
}

void tampilkanBantuan() {
    std::cout << "Perintah yang tersedia:\n"
              << "  buka FILE                 membuka gambar\n"
              << "  daftar                    daftar detektor\n"
              << "  tambah warna NAMA R G B [TOL]\n"
              << "  tambah terang N           kecerahan >= N\n"
              << "  tambah gelap N            kecerahan <= N\n"
              << "  hapus NOMOR               menghapus detektor\n"
              << "  jalankan                  menjalankan semua\n"
              << "  simpan FILE               menyimpan hasil\n"
              << "  keluar                    mengakhiri program\n";
}

// ---------- Program utama ----------
int main() {
    DaftarDetektor daftar;
    muatDariCsv("warna.csv", daftar);
    std::cout << "===== ColorScan v0.10 =====\n";
    std::cout << daftar.size() << " detektor dimuat.\n";

    cv::Mat gambar, gambarHasil;
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
        std::string perintah = kata[0];

        try {
            if (perintah == "keluar") {
                std::cout << "Terima kasih.\n";
                break;
            } else if (perintah == "bantuan") {
                tampilkanBantuan();
            } else if (perintah == "daftar") {
                tampilkanDaftar(daftar);
            } else if (perintah == "tambah") {
                tambahDetektor(kata, daftar);
            } else if (perintah == "hapus") {
                hapusDetektor(kata.at(1), daftar);
            } else if (perintah == "buka") {
                cv::Mat baru = cv::imread(kata.at(1));
                if (baru.empty()) {
                    std::cout << "Gagal membuka " << kata[1] << "\n";
                } else {
                    gambar = baru;
                    std::cout << "Berhasil membuka " << kata[1]
                              << "\n";
                }
            } else if (perintah == "simpan") {
                if (gambarHasil.empty()) {
                    std::cout << "Belum ada hasil.\n";
                } else if (cv::imwrite(kata.at(1), gambarHasil)) {
                    std::cout << "Tersimpan di " << kata[1] << "\n";
                }
            } else if (perintah == "jalankan") {
                if (gambar.empty()) {
                    std::cout << "Belum ada gambar.\n";
                    continue;
                }
                gambarHasil = jalankanSemua(daftar, gambar);
                cv::imshow("Hasil", gambarHasil);
                cv::waitKey(0);
            } else {
                std::cout << "Perintah tidak dikenal. "
                          << "Ketik 'bantuan'.\n";
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Argumen kurang. Ketik 'bantuan'.\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "Argumen harus berupa angka.\n";
        } catch (const cv::Exception& e) {
            std::cout << "Error OpenCV: " << e.func << "\n";
        }
    }
    return 0;
}
