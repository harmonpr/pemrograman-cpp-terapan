cmake_minimum_required(VERSION 3.16)
project(Bab07)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
link_libraries(${OpenCV_LIBS})

add_executable(colorscan_v07 colorscan_v07.cpp)
add_executable(gambar_bentuk gambar_bentuk.cpp)
add_executable(kotak_pembatas kotak_pembatas.cpp)
add_executable(palet_warna palet_warna.cpp)
add_executable(struct_opencv struct_opencv.cpp)
add_executable(warna_struct warna_struct.cpp)
