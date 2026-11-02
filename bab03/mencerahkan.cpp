// mencerahkan.cpp - mengulang selama syarat terpenuhi dengan while
#include <iostream>

int main() {
    int r = 0;
    int langkah = 0;

    std::cout << "Nilai merah awal: ";
    std::cin >> r;

    while (r < 255) {
        r = r + 40;
        if (r > 255) {
            r = 255;
        }
        langkah++;
        std::cout << "Langkah " << langkah << ": merah = "
                  << r << "\n";
    }

    std::cout << "Mencapai 255 setelah " << langkah << " langkah.\n";
    return 0;
}
