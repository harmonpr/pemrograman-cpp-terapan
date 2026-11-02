// histogram.cpp - menghitung sebaran kecerahan piksel
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<int> piksel = {
        12, 30, 45, 60, 70, 90, 100, 110, 120, 125,
        130, 140, 150, 160, 200, 210, 220, 240, 250, 255
    };

    std::string label[4] = {"  0- 63", " 64-127", "128-191",
                            "192-255"};
    int hitung[4] = {0, 0, 0, 0};

    for (int p : piksel) {
        int kelompok = p / 64;      // 0, 1, 2, atau 3
        hitung[kelompok]++;
    }

    for (int i = 0; i < 4; i++) {
        std::cout << label[i] << " | ";
        for (int j = 0; j < hitung[i]; j++) {
            std::cout << "*";
        }
        std::cout << " (" << hitung[i] << ")\n";
    }
    return 0;
}
