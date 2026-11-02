// teks.cpp - pengolahan teks
#include "teks.hpp"

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
