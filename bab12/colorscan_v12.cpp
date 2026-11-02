// ==========================================
//  ColorScan v0.12
//  Mode interaktif: klik mouse, trackbar,
//  video, dan kamera
// ==========================================
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
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
    std::string detektor;   // nama detektor, misalnya "merah"
    std::string nama;       // label benda, misalnya "merah 2"
    int jumlahPiksel;
    cv::Rect kotak;
};

// Membuat masker: 255 untuk piksel yang cocok, 0 untuk lainnya
cv::Mat buatMasker(const Detektor& d, const cv::Mat& gambar) {
    cv::Mat masker(gambar.rows, gambar.cols, CV_8UC1, cv::Scalar(0));
    for (int y = 0; y < gambar.rows; y++) {
        const cv::Vec3b* baris = gambar.ptr<cv::Vec3b>(y);
        uchar* barisMasker = masker.ptr<uchar>(y);
        for (int x = 0; x < gambar.cols; x++) {
            if (d.cocok(baris[x])) {
                barisMasker[x] = 255;
            }
        }
    }
    return masker;
}

// Memisahkan piksel yang cocok menjadi benda-benda terpisah
std::vector<HasilDeteksi> cariObjek(const Detektor& d,
                                    const cv::Mat& gambar,
                                    int luasMin) {
    cv::Mat masker = buatMasker(d, gambar);
    std::vector<HasilDeteksi> daftarBenda;
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    for (int y = 0; y < masker.rows; y++) {
        for (int x = 0; x < masker.cols; x++) {
            if (masker.at<uchar>(y, x) != 255) {
                continue;
            }
            std::queue<cv::Point> antrian;
            antrian.push(cv::Point(x, y));
            masker.at<uchar>(y, x) = 0;
            cv::Rect kotak(x, y, 1, 1);
            int luas = 0;
            while (!antrian.empty()) {
                cv::Point p = antrian.front();
                antrian.pop();
                luas++;
                kotak = kotak | cv::Rect(p.x, p.y, 1, 1);
                for (int k = 0; k < 4; k++) {
                    int nx = p.x + dx[k], ny = p.y + dy[k];
                    if (nx >= 0 && ny >= 0 && nx < masker.cols
                        && ny < masker.rows
                        && masker.at<uchar>(ny, nx) == 255) {
                        masker.at<uchar>(ny, nx) = 0;
                        antrian.push(cv::Point(nx, ny));
                    }
                }
            }
            if (luas >= luasMin) {          // abaikan bintik kecil
                std::string label = d.nama() + " " +
                    std::to_string(daftarBenda.size() + 1);
                daftarBenda.push_back({d.nama(), label, luas, kotak});
            }
        }
    }
    return daftarBenda;
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

std::vector<HasilDeteksi> jalankanSemua(const DaftarDetektor& daftar,
                                        const cv::Mat& gambar,
                                        int luasMin,
                                        cv::Mat& gambarHasil) {
    gambarHasil = gambar.clone();
    std::vector<HasilDeteksi> semua;
    for (const std::unique_ptr<Detektor>& d : daftar) {
        std::vector<HasilDeteksi> benda =
            cariObjek(*d, gambar, luasMin);
        std::cout << d->nama() << ": " << benda.size() << " benda\n";
        for (const HasilDeteksi& h : benda) {
            tandai(gambarHasil, h, *d);
            semua.push_back(h);
        }
    }
    return semua;
}

void tampilkanStatistik(std::vector<HasilDeteksi> semua) {
    if (semua.empty()) {
        std::cout << "Belum ada hasil. Jalankan 'jalankan'.\n";
        return;
    }
    // jumlah benda dan total luas untuk setiap detektor
    std::map<std::string, int> jumlahBenda;
    std::map<std::string, int> totalLuas;
    for (const HasilDeteksi& h : semua) {
        jumlahBenda[h.detektor]++;
        totalLuas[h.detektor] += h.jumlahPiksel;
    }
    std::cout << "Per detektor:\n";
    for (const auto& p : jumlahBenda) {
        std::cout << "  " << p.first << ": " << p.second
                  << " benda, " << totalLuas[p.first] << " piksel\n";
    }

    // urutkan semua benda dari yang terbesar
    std::sort(semua.begin(), semua.end(),
              [](const HasilDeteksi& a, const HasilDeteksi& b) {
                  return a.jumlahPiksel > b.jumlahPiksel;
              });
    std::cout << "Benda dari yang terbesar:\n";
    for (const HasilDeteksi& h : semua) {
        std::cout << "  " << h.nama << " (" << h.jumlahPiksel
                  << " piksel)\n";
    }

    int rataRata = 0;
    for (const HasilDeteksi& h : semua) {
        rataRata += h.jumlahPiksel;
    }
    rataRata /= semua.size();
    int diAtasRata = std::count_if(
        semua.begin(), semua.end(),
        [rataRata](const HasilDeteksi& h) {
            return h.jumlahPiksel > rataRata;
        });
    std::cout << "Rata-rata luas " << rataRata << " piksel, "
              << diAtasRata << " benda di atasnya.\n";
}

// ---------- Mode interaktif ----------
struct DataInteraktif {
    cv::Mat frame;              // frame yang sedang diolah
    bool adaTarget = false;
    cv::Vec3b target;           // warna yang diklik (B, G, R)
};

void saatKlik(int peristiwa, int x, int y, int, void* data) {
    DataInteraktif* d = static_cast<DataInteraktif*>(data);
    if (peristiwa == cv::EVENT_LBUTTONDOWN && !d->frame.empty()) {
        d->target = d->frame.at<cv::Vec3b>(y, x);
        d->adaTarget = true;
        std::cout << "Target dipilih di (" << x << ", " << y << ")\n";
    }
}

// Membuka gambar diam, file video, atau kamera
bool bukaSumber(const std::string& sumber, cv::VideoCapture& video,
                cv::Mat& gambarDiam) {
    if (sumber == "kamera") {
        video.open(0);
        return video.isOpened();
    }
    std::string ekstensi =
        std::filesystem::path(sumber).extension().string();
    if (ekstensi == ".png" || ekstensi == ".jpg"
        || ekstensi == ".bmp") {
        gambarDiam = cv::imread(sumber);
        return !gambarDiam.empty();
    }
    video.open(sumber);
    return video.isOpened();
}

void modeInteraktif(const std::string& sumber,
                    DaftarDetektor& daftar) {
    cv::VideoCapture video;
    cv::Mat gambarDiam;
    if (!bukaSumber(sumber, video, gambarDiam)) {
        std::cout << "Sumber tidak bisa dibuka: " << sumber << "\n";
        return;
    }

    const std::string JENDELA = "ColorScan Interaktif";
    cv::namedWindow(JENDELA);
    cv::createTrackbar("Toleransi", JENDELA, nullptr, 150);
    cv::createTrackbar("LuasMin", JENDELA, nullptr, 2000);
    cv::setTrackbarPos("Toleransi", JENDELA, 60);
    cv::setTrackbarPos("LuasMin", JENDELA, 100);

    DataInteraktif data;
    cv::setMouseCallback(JENDELA, saatKlik, &data);
    bool pakaiDaftar = false;
    int nomorSimpan = 0;
    std::cout << "Klik benda untuk memilih target warna.\n"
              << "Tombol: d daftar detektor, t tambah target ke "
              << "daftar,\n        s simpan, r hapus target, "
              << "Esc kembali\n";

    while (true) {
        if (!gambarDiam.empty()) {
            data.frame = gambarDiam;
        } else if (!video.read(data.frame)) {
            std::cout << "Video selesai.\n";
            break;
        }
        int tol = cv::getTrackbarPos("Toleransi", JENDELA);
        int luasMin = cv::getTrackbarPos("LuasMin", JENDELA);
        cv::Mat tampil = data.frame.clone();
        int jumlahBenda = 0;

        if (pakaiDaftar) {
            for (const std::unique_ptr<Detektor>& d : daftar) {
                for (const HasilDeteksi& h :
                     cariObjek(*d, data.frame, luasMin)) {
                    tandai(tampil, h, *d);
                    jumlahBenda++;
                }
            }
        }
        if (data.adaTarget) {
            DetektorWarna target("target", data.target[2],
                                 data.target[1], data.target[0], tol);
            for (const HasilDeteksi& h :
                 cariObjek(target, data.frame, luasMin)) {
                tandai(tampil, h, target);
                jumlahBenda++;
            }
        }
        cv::putText(tampil, std::to_string(jumlahBenda) + " benda",
                    cv::Point(10, tampil.rows - 15),
                    cv::FONT_HERSHEY_SIMPLEX, 0.8,
                    cv::Scalar(0, 0, 0), 2);
        cv::imshow(JENDELA, tampil);

        int tombol = cv::waitKey(30);
        if (tombol == 27) {
            break;
        } else if (tombol == 'd') {
            pakaiDaftar = !pakaiDaftar;
        } else if (tombol == 'r') {
            data.adaTarget = false;
        } else if (tombol == 's') {
            nomorSimpan++;
            std::string nama = "tangkapan_" +
                               std::to_string(nomorSimpan) + ".png";
            cv::imwrite(nama, tampil);
            std::cout << "Tersimpan di " << nama << "\n";
        } else if (tombol == 't' && data.adaTarget) {
            std::string nama = "target" +
                               std::to_string(daftar.size() + 1);
            daftar.push_back(std::make_unique<DetektorWarna>(
                nama, data.target[2], data.target[1],
                data.target[0], tol));
            std::cout << "Ditambahkan ke daftar: " << nama << "\n";
        }
    }
    cv::destroyWindow(JENDELA);
}

void tampilkanBantuan() {
    std::cout << "Perintah yang tersedia:\n"
              << "  buka FILE                 membuka gambar\n"
              << "  daftar                    daftar detektor\n"
              << "  tambah warna NAMA R G B [TOL]\n"
              << "  tambah terang N           kecerahan >= N\n"
              << "  tambah gelap N            kecerahan <= N\n"
              << "  hapus NOMOR               menghapus detektor\n"
              << "  jalankan                  mencari semua benda\n"
              << "  statistik                 ringkasan hasil\n"
              << "  luas N                    luas benda minimum\n"
              << "  interaktif SUMBER         file gambar, video,\n"
              << "                            atau kamera\n"
              << "  simpan FILE               menyimpan hasil\n"
              << "  keluar                    mengakhiri program\n";
}

// ---------- Program utama ----------
int main() {
    DaftarDetektor daftar;
    muatDariCsv("warna.csv", daftar);
    std::cout << "===== ColorScan v0.12 =====\n";
    std::cout << daftar.size() << " detektor dimuat.\n";

    cv::Mat gambar, gambarHasil;
    std::vector<HasilDeteksi> hasilTerakhir;
    int luasMin = 100;
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
            } else if (perintah == "interaktif") {
                modeInteraktif(kata.at(1), daftar);
            } else if (perintah == "statistik") {
                tampilkanStatistik(hasilTerakhir);
            } else if (perintah == "luas") {
                luasMin = std::stoi(kata.at(1));
                std::cout << "Luas minimum sekarang " << luasMin
                          << " piksel\n";
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
                hasilTerakhir = jalankanSemua(daftar, gambar, luasMin,
                                              gambarHasil);
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
