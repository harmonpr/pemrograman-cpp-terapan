# Instalasi Lingkungan Kerja

Panduan ini menyiapkan semua alat yang dibutuhkan untuk menjalankan kode di buku, di Windows 10 atau 11 versi 64 bit. Ikuti urutannya dari langkah 1.

## 1. MinGW-w64 (WinLibs)

WinLibs adalah paket GCC untuk Windows yang tidak perlu dipasang, cukup diekstrak. Paket ini sudah berisi `g++`, `gdb`, `mingw32-make`, `cmake`, dan `ninja`.

1. Buka https://winlibs.com dan cari bagian Download.
2. Pilih rilis terbaru dengan keterangan UCRT runtime, lalu unduh versi Win64 dalam bentuk ZIP yang tanpa LLVM/Clang/LLD/LLDB.
3. Ekstrak sehingga terbentuk folder `C:\mingw64`, dengan file `C:\mingw64\bin\g++.exe` di dalamnya.

Jika file berformat `.7z`, gunakan 7-Zip untuk mengekstraknya.

## 2. Menambahkan folder ke Path

Path adalah daftar folder tempat Windows mencari program.

1. Tekan tombol Windows, ketik `environment`, lalu pilih Edit the system environment variables.
2. Tekan Environment Variables.
3. Di bagian User variables, pilih Path lalu tekan Edit.
4. Tekan New dan isi `C:\mingw64\bin`.
5. Tekan OK pada semua jendela.

Tutup semua jendela PowerShell dan VS Code, lalu buka PowerShell baru dan periksa:

```powershell
g++ --version
gdb --version
cmake --version
mingw32-make --version
where.exe gcc
```

Perintah `where.exe gcc` sebaiknya hanya menampilkan satu baris, yaitu `C:\mingw64\bin\gcc.exe`. Jika muncul lebih dari satu (misalnya dari Strawberry Perl, Anaconda, atau MSYS2), pindahkan `C:\mingw64\bin` ke urutan paling atas dalam Path.

## 3. Visual Studio Code

1. Unduh dan pasang dari https://code.visualstudio.com.
2. Buka menu Extensions (Ctrl+Shift+X), cari C/C++ buatan Microsoft, lalu pasang.

## 4. OpenCV 4.14.0

OpenCV untuk MinGW tidak tersedia dalam bentuk siap pakai, jadi perlu dikompilasi sendiri satu kali. Prosesnya memakan waktu 30 sampai 90 menit, tergantung kecepatan komputer.

1. Buka https://github.com/opencv/opencv/releases/tag/4.14.0 dan unduh Source code (zip).
2. Ekstrak sehingga terbentuk `C:\opencv\opencv-4.14.0`, dengan file `C:\opencv\opencv-4.14.0\CMakeLists.txt` di dalamnya.
3. Buka PowerShell di folder repositori ini, lalu jalankan:

```powershell
powershell -ExecutionPolicy Bypass -File scripts\build-opencv.ps1
```

Komputer harus terhubung ke internet selama tahap konfigurasi, karena CMake mengunduh beberapa komponen, termasuk pembaca video FFmpeg.

Jika ingin mengetik perintahnya sendiri tanpa skrip, gunakan urutan berikut. Ketik setiap perintah dalam satu baris.

```powershell
cd C:\opencv
cmake -S opencv-4.14.0 -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=C:/mingw64/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe -DCMAKE_MAKE_PROGRAM=C:/mingw64/bin/mingw32-make.exe -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=C:/opencv/install -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_opencv_python3=OFF -DBUILD_opencv_java=OFF -DWITH_IPP=OFF -DWITH_MSMF=OFF -DWITH_OBSENSOR=OFF -DWITH_OPENCL_D3D11_NV=OFF -DENABLE_PRECOMPILED_HEADERS=OFF -DCPU_DISPATCH= -DOPENCV_ALLOCATOR_STATS_COUNTER_TYPE=int64_t
cmake --build build -j 4
cmake --install build
```

## 5. Menambahkan OpenCV ke Path

Ulangi langkah 2 untuk menambahkan folder berikut ke Path:

```
C:\opencv\install\x64\mingw\bin
```

Buka PowerShell baru dan periksa:

```powershell
opencv_version
```

Hasilnya harus `4.14.0`. Periksa juga bahwa file pembaca video ada:

```powershell
dir C:\opencv\install\x64\mingw\bin\opencv_videoio_ffmpeg*
```

Jika file `opencv_videoio_ffmpeg4140_64.dll` tidak ada, jalankan:

```powershell
powershell -ExecutionPolicy Bypass -File scripts\unduh-ffmpeg.ps1
```

## 6. Pemeriksaan akhir

```powershell
powershell -ExecutionPolicy Bypass -File scripts\cek-lingkungan.ps1
```

Jika semua baris menunjukkan `[OK]`, lingkungan kerja sudah siap. Coba kompilasi program Bab 6:

```powershell
cd bab06
cmake -S . -B build -G "MinGW Makefiles" -D OpenCV_DIR=C:/opencv/install
cmake --build build
.\build\versi_opencv.exe
```
