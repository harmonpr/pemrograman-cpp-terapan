// perintah.cpp - memecah perintah teks menjadi kata dan angka
#include <iostream>
#include <string>

int main() {
    std::string baris;
    std::cout << "Ketik perintah (contoh: cerah 40): ";
    std::getline(std::cin, baris);

    std::string perintah = baris;
    std::string argumen = "";

    std::size_t spasi = baris.find(' ');
    if (spasi != std::string::npos) {
        perintah = baris.substr(0, spasi);
        argumen = baris.substr(spasi + 1);
    }

    std::cout << "Perintah: [" << perintah << "]\n";
    std::cout << "Argumen : [" << argumen << "]\n";

    if (perintah == "cerah" && argumen != "") {
        int jumlah = std::stoi(argumen);   // teks -> int
        std::cout << "Mencerahkan sebesar " << jumlah << "\n";
    }
    return 0;
}
