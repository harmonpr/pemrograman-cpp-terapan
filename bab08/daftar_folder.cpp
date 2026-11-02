// daftar_folder.cpp - menampilkan isi folder gambar
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main() {
    fs::path folder = "gambar";

    if (!fs::exists(folder)) {
        std::cout << "Folder " << folder.string()
                  << " tidak ditemukan.\n";
        return 1;
    }

    int jumlah = 0;
    for (const fs::directory_entry& entri :
         fs::directory_iterator(folder)) {
        fs::path p = entri.path();
        std::string ekstensi = p.extension().string();
        if (ekstensi == ".png" || ekstensi == ".jpg") {
            std::cout << p.filename().string() << "  ("
                      << fs::file_size(p) / 1024 << " KB)\n";
            jumlah++;
        }
    }
    std::cout << "Jumlah gambar: " << jumlah << "\n";

    fs::create_directories("hasil");
    std::cout << "Folder hasil siap.\n";
    return 0;
}
