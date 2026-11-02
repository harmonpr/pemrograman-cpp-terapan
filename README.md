# Pemrograman C++ Terapan

Kode sumber dan materi pendukung untuk buku **Pemrograman C++ Terapan: Dari Aplikasi Konsol Hingga Pengolahan Gambar dengan OpenCV**.

Repositori ini berisi semua program yang dibahas di buku, dikelompokkan per bab, beserta gambar contoh, video contoh, dan skrip bantu untuk menyiapkan lingkungan kerja di Windows. Proyek berjalan buku ini adalah **ColorScan**, penganalisis warna dan objek yang tumbuh dari versi 0.1 di Bab 1 sampai versi 1.0 di Bab 13.

## Mengunduh repositori

Ada dua cara. Cara paling mudah adalah menekan tombol hijau **Code** di halaman ini, lalu pilih **Download ZIP** dan ekstrak ke folder kerja, misalnya `C:\latihan\pemrograman-cpp-terapan`. Cara kedua, jika Git sudah terpasang:

```powershell
git clone https://github.com/harmonpr/pemrograman-cpp-terapan.git
```

## Isi repositori

```
pemrograman-cpp-terapan/
├── bab01/ ... bab05/   program konsol C++ (cukup g++)
├── bab06/ ... bab12/   program OpenCV, masing-masing dengan CMakeLists.txt
│   └── gambar/         buah.png, mainan.png, taman.jpg, bola.mp4
├── bab13/              proyek akhir ColorScan 1.0
│   ├── include/        file header
│   ├── src/            file implementasi dan main.cpp
│   ├── tests/          program pengujian (ctest)
│   └── tools/          alat tambahan hitung_benda
├── docs/
│   ├── instalasi.md    langkah lengkap memasang semua alat
│   └── masalah-umum.md solusi untuk error yang sering muncul
└── scripts/
    ├── build-opencv.ps1    mengompilasi dan memasang OpenCV
    ├── unduh-ffmpeg.ps1    mengunduh pembaca video MP4 untuk OpenCV
    └── cek-lingkungan.ps1  memeriksa apakah semua alat sudah siap
```

| Bab | Topik | Cara menjalankan |
|---|---|---|
| 1 | Persiapan, variabel, input dan output | g++ |
| 2 | Percabangan dan flowchart | g++ |
| 3 | Perulangan dan validasi input | g++ |
| 4 | Function, reference, debugger | g++ (dan gdb) |
| 5 | Array, vector, string | g++ |
| 6 | Mengenal OpenCV dan cv::Mat | CMake |
| 7 | Struct, Point, Rect, Scalar, menggambar | CMake |
| 8 | File, folder, CSV, exception | CMake |
| 9 | Class, inheritance, polimorfisme | CMake |
| 10 | Pointer, smart pointer, memori Mat | CMake |
| 11 | STL dan algoritma, menghitung objek | CMake |
| 12 | Trackbar, mouse, video, kamera | CMake |
| 13 | Proyek multi-file ColorScan 1.0 | CMake dan ctest |

## Yang perlu diunduh

Semua alat di bawah ini gratis. Bab 1 sampai 5 hanya membutuhkan nomor 1 dan 2. Bab 6 sampai 13 membutuhkan ketiganya.

| No | Alat | Tautan | Keterangan |
|---|---|---|---|
| 1 | MinGW-w64 dari WinLibs (GCC, gdb, CMake, mingw32-make) | https://winlibs.com | Pilih rilis UCRT, Win64, ZIP, tanpa LLVM. Ekstrak ke `C:\mingw64` |
| 2 | Visual Studio Code dan ekstensi C/C++ dari Microsoft | https://code.visualstudio.com | Editor kode |
| 3 | OpenCV 4.14.0, kode sumber (Source code zip) | https://github.com/opencv/opencv/releases/tag/4.14.0 | Ekstrak ke `C:\opencv\opencv-4.14.0`, lalu kompilasi dengan `scripts\build-opencv.ps1` |

Setelah terpasang, folder berikut harus ada di variabel lingkungan Path:

```
C:\mingw64\bin
C:\opencv\install\x64\mingw\bin
```

Langkah lengkapnya, termasuk cara mengubah Path, ada di [docs/instalasi.md](docs/instalasi.md). Untuk memastikan semuanya siap, jalankan:

```powershell
powershell -ExecutionPolicy Bypass -File scripts\cek-lingkungan.ps1
```

## Menjalankan kode

### Bab 1 sampai 5

Buka PowerShell di folder bab, kompilasi, lalu jalankan:

```powershell
cd bab01
g++ -Wall halo.cpp -o halo.exe
.\halo.exe
```

Beberapa file memang sengaja dibuat salah sebagai bahan latihan membaca pesan error, yaitu `bab01/salah_nama.cpp`, `bab01/salah_titikkoma.cpp`, dan `bab04/urutan_salah.cpp`. File `bab04/bug_kecerahan.cpp` bisa dikompilasi tetapi hasilnya salah, dan dipakai untuk latihan debugger. Folder `bab04/.vscode` berisi pengaturan VS Code untuk kompilasi dan debugging dengan gdb.

### Bab 6 sampai 12

Setiap folder bab memiliki `CMakeLists.txt` yang membuat semua program di bab tersebut sekaligus:

```powershell
cd bab06
cmake -S . -B build -G "MinGW Makefiles" -D OpenCV_DIR=C:/opencv/install
cmake --build build
.\build\tampil_gambar.exe
```

Jalankan program dari folder bab (bukan dari dalam folder `build`), karena program membuka gambar dengan alamat relatif seperti `gambar/buah.png`.

### Bab 13, ColorScan 1.0

```powershell
cd bab13
cmake -S . -B build -G "MinGW Makefiles" -D OpenCV_DIR=C:/opencv/install
cmake --build build
cd build
ctest
cd ..
.\build\colorscan.exe
```

## Jika ada masalah

Solusi untuk masalah yang paling sering muncul, misalnya pesan `-D tidak dikenali` di PowerShell, error `CMAKE_SIZEOF_VOID_P`, DLL tidak ditemukan, video MP4 tidak bisa dibuka, atau kamera tidak menyala, ada di [docs/masalah-umum.md](docs/masalah-umum.md). Untuk masalah video, program `bab12/cek_video.cpp` membantu menemukan penyebabnya.

Jika menemukan kesalahan pada kode atau buku, silakan laporkan melalui menu **Issues** di repositori ini.

## Lisensi

Kode di repositori ini dirilis dengan lisensi MIT (lihat [LICENSE](LICENSE)). Isi buku tidak termasuk dalam lisensi ini.
