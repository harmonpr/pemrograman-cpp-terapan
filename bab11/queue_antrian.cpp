// queue_antrian.cpp - antrian gambar yang akan diproses
#include <iostream>
#include <queue>
#include <string>

int main() {
    std::queue<std::string> antrian;
    antrian.push("buah.png");
    antrian.push("mainan.png");
    antrian.push("taman.jpg");

    std::cout << "Jumlah dalam antrian: " << antrian.size() << "\n";
    while (!antrian.empty()) {
        std::string berikutnya = antrian.front();   // paling depan
        antrian.pop();
        std::cout << "Memproses " << berikutnya << ", sisa "
                  << antrian.size() << "\n";
    }
    return 0;
}
