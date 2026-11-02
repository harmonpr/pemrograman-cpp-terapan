// teks.hpp - pengolahan teks
#pragma once

#include <string>
#include <vector>

// Memecah baris berdasarkan pemisah; bagian kosong dibuang
std::vector<std::string> pecah(const std::string& baris,
                               char pemisah);
