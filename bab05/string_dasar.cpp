// string_dasar.cpp - mengolah nama file
#include <iostream>
#include <string>

int main() {
    std::string namaFile = "kucing_oranye.jpg";

    std::cout << "Nama file     : " << namaFile << "\n";
    std::cout << "Panjang       : " << namaFile.length()
              << " huruf\n";
    std::cout << "Huruf pertama : " << namaFile[0] << "\n";

    std::size_t posisiTitik = namaFile.find('.');
    std::string nama = namaFile.substr(0, posisiTitik);
    std::string ekstensi = namaFile.substr(posisiTitik + 1);

    std::cout << "Nama          : " << nama << "\n";
    std::cout << "Ekstensi      : " << ekstensi << "\n";

    std::string namaBaru = nama + "_abu.png";
    std::cout << "Nama baru     : " << namaBaru << "\n";

    if (ekstensi == "jpg" || ekstensi == "png") {
        std::cout << "Format gambar dikenali.\n";
    }
    return 0;
}
