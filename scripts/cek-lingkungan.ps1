# cek-lingkungan.ps1
# Memeriksa apakah semua alat yang dibutuhkan buku ini sudah siap.
#
# Cara menjalankan:
#   powershell -ExecutionPolicy Bypass -File scripts\cek-lingkungan.ps1

$semuaSiap = $true

function Periksa($nama, $perintah) {
    $c = Get-Command $perintah -ErrorAction SilentlyContinue
    if ($c) {
        Write-Host ("[OK]    {0,-14} {1}" -f $nama, $c.Source)
    } else {
        Write-Host ("[BELUM] {0,-14} tidak ditemukan di Path" -f $nama) `
            -ForegroundColor Yellow
        $script:semuaSiap = $false
    }
}

Write-Host "Alat untuk Bab 1 sampai 5:"
Periksa "g++" "g++"
Periksa "gdb" "gdb"

Write-Host ""
Write-Host "Alat untuk Bab 6 sampai 13:"
Periksa "cmake" "cmake"
Periksa "mingw32-make" "mingw32-make"
Periksa "opencv_version" "opencv_version"

$dll = Get-Command "libopencv_core4140.dll" -ErrorAction SilentlyContinue
if ($dll) {
    $ff = Join-Path (Split-Path $dll.Source) "opencv_videoio_ffmpeg4140_64.dll"
    if (Test-Path $ff) {
        Write-Host "[OK]    FFmpeg         $ff"
    } else {
        Write-Host "[BELUM] FFmpeg         jalankan scripts\unduh-ffmpeg.ps1" `
            -ForegroundColor Yellow
        $semuaSiap = $false
    }
}

$gcc = Get-Command "gcc" -All -ErrorAction SilentlyContinue
if ($gcc -and @($gcc).Count -gt 1) {
    Write-Host ""
    Write-Host "Peringatan: ada lebih dari satu gcc di Path:" `
        -ForegroundColor Yellow
    $gcc | ForEach-Object { Write-Host "  $($_.Source)" }
}

Write-Host ""
if ($semuaSiap) {
    Write-Host "Semua alat siap." -ForegroundColor Green
} else {
    Write-Host "Ada alat yang belum siap. Lihat docs/instalasi.md."
}
