cmake_minimum_required(VERSION 3.16)
project(Bab09)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
link_libraries(${OpenCV_LIBS})

add_executable(colorscan_v09 colorscan_v09.cpp)
add_executable(detektor_polimorfik detektor_polimorfik.cpp)
add_executable(filter_gambar filter_gambar.cpp)
add_executable(histogram_kelas histogram_kelas.cpp)
add_executable(kelas_warna kelas_warna.cpp)
add_executable(warna_enkapsulasi warna_enkapsulasi.cpp)
