# Masalah Umum dan Solusinya

## PowerShell: "-D is not recognized as the name of a cmdlet"

Perintah yang ditulis dalam beberapa baris di PowerShell memakai tanda backtick (`` ` ``) di akhir baris. Pesan ini muncul jika ada spasi setelah backtick, atau ada baris kosong di antara baris perintah. PowerShell lalu menganggap baris berikutnya sebagai perintah baru.

Solusi termudah adalah menulis seluruh perintah dalam satu baris, seperti di [instalasi.md](instalasi.md), atau memakai skrip `scripts\build-opencv.ps1`.

## CMake: "CMAKE_SIZEOF_VOID_P is not defined" atau masalah bitness

Biasanya penyebabnya adalah folder `build` sisa percobaan sebelumnya, atau CMake menemukan compiler yang salah.

1. Hapus folder build: `Remove-Item -Recurse -Force C:\opencv\build`
2. Periksa `where.exe gcc` dan `where.exe g++`. Baris pertama harus `C:\mingw64\bin\...`.
3. Ulangi konfigurasi dengan menyebut compiler secara langsung: `-DCMAKE_C_COMPILER=C:/mingw64/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe -DCMAKE_MAKE_PROGRAM=C:/mingw64/bin/mingw32-make.exe`

Peringatan bertuliskan `deprecated` saat konfigurasi tidak berbahaya dan boleh diabaikan.

## CMake: "Could not find a package configuration file provided by OpenCV"

CMake tidak tahu letak OpenCV. Pastikan perintah konfigurasi menyertakan `-D OpenCV_DIR=C:/opencv/install` dan folder tersebut berisi file `OpenCVConfig.cmake`. Jika sebelumnya konfigurasi gagal, hapus folder `build` di folder bab lalu ulangi.

## Program langsung tertutup atau muncul pesan "libopencv_core4140.dll was not found"

Windows tidak menemukan DLL OpenCV. Tambahkan `C:\opencv\install\x64\mingw\bin` ke Path, lalu tutup dan buka ulang PowerShell atau VS Code. Jika pesannya menyebut `libstdc++-6.dll` atau `libgcc_s_seh-1.dll`, berarti `C:\mingw64\bin` yang belum ada di Path.

## "Gambar tidak bisa dibaca" atau gambar kosong

Program membuka gambar dengan alamat relatif `gambar/buah.png`, yang dihitung dari folder tempat program dijalankan. Jalankan program dari folder bab:

```powershell
cd bab06
.\build\tampil_gambar.exe
```

Jangan menjalankan program dari dalam folder `build`, dan jangan klik dua kali file `.exe` di File Explorer.

## Video MP4: "Sumber video tidak bisa dibuka"

Ada tiga kemungkinan penyebab. Program `bab12/cek_video.cpp` memeriksa ketiganya sekaligus:

```powershell
cd bab12
.\build\cek_video.exe
```

Jika baris "File ada?" bernilai TIDAK, program dijalankan dari folder yang salah atau file `gambar/bola.mp4` tidak ada.

Jika baris "FFMPEG siap?" bernilai TIDAK, file `opencv_videoio_ffmpeg4140_64.dll` tidak ada di `C:\opencv\install\x64\mingw\bin`. File ini biasanya diunduh otomatis saat konfigurasi OpenCV, tetapi bisa gagal jika koneksi internet terputus. Jalankan `scripts\unduh-ffmpeg.ps1`, atau unduh secara manual dari alamat berikut lalu simpan dengan nama `opencv_videoio_ffmpeg4140_64.dll` di folder tersebut:

```
https://raw.githubusercontent.com/opencv/opencv_3rdparty/bd9418020a5c342be979c56d6e6434261959d3af/ffmpeg/opencv_videoio_ffmpeg_64.dll
```

Jika kedua baris bernilai ya tetapi video tetap tidak terbuka, coba file video lain untuk memastikan file video tidak rusak.

## Kamera tidak menyala

1. Buka Settings, Privacy & security, Camera, lalu pastikan akses kamera untuk aplikasi desktop diaktifkan.
2. Tutup aplikasi lain yang sedang memakai kamera, misalnya Zoom atau Teams.
3. Jika komputer memiliki lebih dari satu kamera, ubah nomor kamera di kode dari `0` menjadi `1`.

## gdb tidak berjalan di VS Code

Buka folder `bab04` (bukan folder repositori) di VS Code melalui menu File, Open Folder, supaya pengaturan di `bab04/.vscode` terbaca. Pastikan `C:\mingw64\bin\gdb.exe` ada, karena alamat itulah yang dipakai di `launch.json`.

## PowerShell menolak menjalankan skrip

Jika muncul pesan `running scripts is disabled on this system`, jalankan skrip dengan awalan berikut:

```powershell
powershell -ExecutionPolicy Bypass -File scripts\nama-skrip.ps1
```
