// algoritma.cpp - sort, max_element, count_if, dan lambda
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Benda {
    std::string nama;
    int luas;
};

int main() {
    std::vector<int> nilai = {130, 45, 210, 88, 255, 17, 190, 64};

    std::sort(nilai.begin(), nilai.end());
    std::cout << "Terurut  :";
    for (int n : nilai) {
        std::cout << " " << n;
    }
    std::cout << "\n";

    auto terbesar = std::max_element(nilai.begin(), nilai.end());
    std::cout << "Terbesar : " << *terbesar << "\n";

    int jumlahTerang = std::count_if(nilai.begin(), nilai.end(),
                                     [](int n) { return n > 127; });
    std::cout << "Terang   : " << jumlahTerang << " nilai\n";

    std::vector<Benda> benda = {
        {"merah 1", 13256}, {"kuning 1", 13588},
        {"merah 2", 9480}, {"biru 1", 11296}
    };
    std::sort(benda.begin(), benda.end(),
              [](const Benda& a, const Benda& b) {
                  return a.luas > b.luas;      // dari yang terbesar
              });
    std::cout << "\nBenda dari yang terbesar:\n";
    for (const Benda& b : benda) {
        std::cout << "  " << b.nama << " (" << b.luas << ")\n";
    }

    int batas = 10000;
    int besar = std::count_if(benda.begin(), benda.end(),
                              [batas](const Benda& b) {
                                  return b.luas > batas;
                              });
    std::cout << "Lebih dari " << batas << " piksel: " << besar
              << " benda\n";
    return 0;
}
