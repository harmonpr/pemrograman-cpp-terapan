// alamat_memori.cpp - melihat ukuran dan alamat variabel
#include <iostream>

int main() {
    int merah = 200;
    double kecerahan = 0.78;
    char kanal = 'R';

    std::cout << "Ukuran int    : " << sizeof(merah) << " byte\n";
    std::cout << "Ukuran double : " << sizeof(kecerahan) << " byte\n";
    std::cout << "Ukuran char   : " << sizeof(kanal) << " byte\n";

    std::cout << "\nAlamat merah  : " << &merah << "\n";

    int piksel[4] = {10, 20, 30, 40};
    std::cout << "\nAlamat setiap elemen array:\n";
    for (int i = 0; i < 4; i++) {
        std::cout << "piksel[" << i << "] di " << &piksel[i]
                  << " berisi " << piksel[i] << "\n";
    }
    return 0;
}
