// warna_enkapsulasi.cpp - constructor, private, getter, setter
#include <iostream>

class Warna {
private:
    int r_;
    int g_;
    int b_;

    int jepit(int nilai) const {
        if (nilai < 0) {
            return 0;
        }
        if (nilai > 255) {
            return 255;
        }
        return nilai;
    }

public:
    Warna(int r, int g, int b) {
        r_ = jepit(r);
        g_ = jepit(g);
        b_ = jepit(b);
    }

    int getR() const { return r_; }
    int getG() const { return g_; }
    int getB() const { return b_; }

    void setR(int r) { r_ = jepit(r); }

    void cerahkan(int jumlah) {
        r_ = jepit(r_ + jumlah);
        g_ = jepit(g_ + jumlah);
        b_ = jepit(b_ + jumlah);
    }

    void tampilkan() const {
        std::cout << "(" << r_ << ", " << g_ << ", " << b_ << ")\n";
    }
};

int main() {
    Warna w(300, 120, -40);        // nilai salah langsung dijepit
    w.tampilkan();

    w.cerahkan(100);
    w.tampilkan();

    w.setR(-10);
    std::cout << "Merah sekarang: " << w.getR() << "\n";
    // w.r_ = 999;   // error: 'int Warna::r_' is private
    return 0;
}
