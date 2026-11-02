cmake_minimum_required(VERSION 3.16)
project(ColorScan VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(OpenCV REQUIRED)

# Pustaka inti: semua bagian ColorScan kecuali main
add_library(colorscan_inti STATIC
    src/detektor.cpp
    src/deteksi.cpp
    src/teks.cpp
    src/laporan.cpp
    src/interaktif.cpp
)
target_include_directories(colorscan_inti PUBLIC include)
target_link_libraries(colorscan_inti PUBLIC ${OpenCV_LIBS})
target_compile_options(colorscan_inti PRIVATE -Wall -Wextra)

# Program utama
add_executable(colorscan src/main.cpp)
target_link_libraries(colorscan PRIVATE colorscan_inti)
target_compile_options(colorscan PRIVATE -Wall -Wextra)

# Program pengujian
enable_testing()
add_executable(uji_deteksi tests/uji_deteksi.cpp)
target_link_libraries(uji_deteksi PRIVATE colorscan_inti)
add_test(NAME uji_deteksi COMMAND uji_deteksi)

# Alat tambahan yang memakai pustaka yang sama
add_executable(hitung_benda tools/hitung_benda.cpp)
target_link_libraries(hitung_benda PRIVATE colorscan_inti)
