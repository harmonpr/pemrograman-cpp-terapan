# unduh-ffmpeg.ps1
# Mengunduh pembaca video FFmpeg untuk OpenCV 4.14.0 jika file
# opencv_videoio_ffmpeg4140_64.dll tidak ikut terpasang.
#
# Cara menjalankan:
#   powershell -ExecutionPolicy Bypass -File scripts\unduh-ffmpeg.ps1

param(
    [string]$Install = "C:\opencv\install"
)

$bin = Join-Path $Install "x64\mingw\bin"
$tujuan = Join-Path $bin "opencv_videoio_ffmpeg4140_64.dll"
$url = "https://raw.githubusercontent.com/opencv/opencv_3rdparty/" +
       "bd9418020a5c342be979c56d6e6434261959d3af/ffmpeg/" +
       "opencv_videoio_ffmpeg_64.dll"

if (-not (Test-Path $bin)) {
    Write-Host "Folder $bin tidak ditemukan. Pasang OpenCV lebih dulu."
    exit 1
}
if (Test-Path $tujuan) {
    Write-Host "File sudah ada: $tujuan"
    exit 0
}

Write-Host "Mengunduh $url"
Invoke-WebRequest -Uri $url -OutFile $tujuan
if (Test-Path $tujuan) {
    Write-Host "Berhasil disimpan ke $tujuan" -ForegroundColor Green
} else {
    Write-Host "Unduhan gagal. Periksa koneksi internet." -ForegroundColor Red
    exit 1
}
