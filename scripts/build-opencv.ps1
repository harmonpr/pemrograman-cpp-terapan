# build-opencv.ps1
# Mengompilasi dan memasang OpenCV 4.14.0 dengan MinGW (WinLibs).
#
# Cara menjalankan dari PowerShell:
#   powershell -ExecutionPolicy Bypass -File scripts\build-opencv.ps1
#
# Sebelum menjalankan, pastikan:
#   1. MinGW (WinLibs) sudah diekstrak ke C:\mingw64
#   2. Kode sumber OpenCV sudah diekstrak ke C:\opencv\opencv-4.14.0

param(
    [string]$Sumber  = "C:\opencv\opencv-4.14.0",
    [string]$Build   = "C:\opencv\build",
    [string]$Install = "C:\opencv\install",
    [string]$MinGW   = "C:\mingw64\bin",
    [int]$Jobs       = 4
)

function Berhenti($pesan) {
    Write-Host ""
    Write-Host "GAGAL: $pesan" -ForegroundColor Red
    exit 1
}

# 1. Pemeriksaan awal
if (-not (Test-Path (Join-Path $Sumber "CMakeLists.txt"))) {
    Berhenti "Kode sumber OpenCV tidak ditemukan di $Sumber"
}
foreach ($alat in @("gcc.exe", "g++.exe", "mingw32-make.exe")) {
    if (-not (Test-Path (Join-Path $MinGW $alat))) {
        Berhenti "Tidak ditemukan: $(Join-Path $MinGW $alat)"
    }
}
if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    Berhenti "Perintah cmake tidak ditemukan. Periksa Path."
}

# 2. Hapus hasil konfigurasi lama
if (Test-Path $Build) {
    Write-Host "Menghapus folder build lama: $Build"
    Remove-Item -Recurse -Force $Build
}

# 3. Konfigurasi
$mg = $MinGW -replace '\\', '/'
$ins = $Install -replace '\\', '/'
$opsi = @(
    "-G", "MinGW Makefiles",
    "-DCMAKE_C_COMPILER=$mg/gcc.exe",
    "-DCMAKE_CXX_COMPILER=$mg/g++.exe",
    "-DCMAKE_MAKE_PROGRAM=$mg/mingw32-make.exe",
    "-DCMAKE_BUILD_TYPE=Release",
    "-DCMAKE_INSTALL_PREFIX=$ins",
    "-DBUILD_TESTS=OFF", "-DBUILD_PERF_TESTS=OFF",
    "-DBUILD_EXAMPLES=OFF", "-DBUILD_DOCS=OFF",
    "-DBUILD_opencv_python3=OFF", "-DBUILD_opencv_java=OFF",
    "-DWITH_IPP=OFF", "-DWITH_MSMF=OFF", "-DWITH_OBSENSOR=OFF",
    "-DWITH_OPENCL_D3D11_NV=OFF",
    "-DENABLE_PRECOMPILED_HEADERS=OFF",
    "-DCPU_DISPATCH=",
    "-DOPENCV_ALLOCATOR_STATS_COUNTER_TYPE=int64_t"
)
Write-Host "Konfigurasi OpenCV..."
cmake -S $Sumber -B $Build @opsi
if ($LASTEXITCODE -ne 0) { Berhenti "Konfigurasi CMake gagal." }

# 4. Kompilasi dan instalasi
Write-Host "Kompilasi OpenCV (30 sampai 90 menit)..."
cmake --build $Build -j $Jobs
if ($LASTEXITCODE -ne 0) { Berhenti "Kompilasi gagal." }

cmake --install $Build
if ($LASTEXITCODE -ne 0) { Berhenti "Instalasi gagal." }

# 5. Pemeriksaan akhir
$bin = Join-Path $Install "x64\mingw\bin"
$ffmpeg = Join-Path $bin "opencv_videoio_ffmpeg4140_64.dll"
Write-Host ""
Write-Host "OpenCV terpasang di $Install" -ForegroundColor Green
if (-not (Test-Path $ffmpeg)) {
    Write-Host "Peringatan: $ffmpeg tidak ada." -ForegroundColor Yellow
    Write-Host "File video MP4 tidak akan bisa dibuka."
    Write-Host "Jalankan scripts\unduh-ffmpeg.ps1 untuk memperbaikinya."
}
Write-Host "Langkah berikutnya: tambahkan folder berikut ke Path,"
Write-Host "lalu buka PowerShell baru dan jalankan opencv_version:"
Write-Host "  $bin"
