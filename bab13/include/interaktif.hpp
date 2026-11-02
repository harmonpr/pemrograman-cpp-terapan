// interaktif.hpp - mode interaktif dengan mouse, trackbar, dan video
#pragma once

#include <string>

#include "detektor.hpp"

// Sumber: file gambar, file video, atau kata "kamera"
void modeInteraktif(const std::string& sumber,
                    DaftarDetektor& daftar);
