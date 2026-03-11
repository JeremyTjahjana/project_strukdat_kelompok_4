# Topik 4 – Sistem Kompresi Data Sederhana

## Latar Belakang

Dalam industri modern, perusahaan harus mengelola volume data teks yang terus meningkat, seperti:

- Log aktivitas sistem
- Data transaksi
- Pesan komunikasi internal

Pada tahap awal, ukuran data masih kecil sehingga penyimpanan dan transmisi dapat dilakukan tanpa optimasi. Namun, seiring pertumbuhan data:

- Kebutuhan ruang penyimpanan meningkat
- Waktu transmisi data menjadi lebih lama

Untuk mengatasi hal tersebut, dibutuhkan sistem kompresi data sederhana yang efisien dan mudah dikelola.

Pada proyek ini, kompresi data diartikan sebagai proses pengkodean data sehingga ukurannya lebih kecil.

Catatan:
Mahasiswa tidak diwajibkan mengimplementasikan algoritma kompresi kompleks seperti:

- ZIP
- LZW
- Huffman penuh

Fokus utama proyek adalah penggunaan dan analisis struktur data untuk mengelola proses kompresi.

---

## Permasalahan di Lapangan

Beberapa permasalahan yang muncul ketika data terus bertambah:

- Ukuran data teks meningkat sehingga membutuhkan ruang penyimpanan lebih besar
- Proses transmisi data menjadi lebih lambat
- Pengelolaan data tanpa kompresi menjadi tidak efisien
- Pemilihan struktur data yang kurang tepat menyebabkan proses kompresi dan dekompresi lambat

---

## Tujuan Proyek

Membangun sistem kompresi data teks sederhana serta menganalisis struktur data yang paling efisien untuk proses kompresi.

Fokus analisis:

- Kecepatan pemrosesan
- Efisiensi memori
- Skalabilitas saat data bertambah

---

## Domain Data

Minimal data yang harus dikelola dalam sistem:

| Data               | Deskripsi                           |
| ------------------ | ----------------------------------- |
| Teks               | Input data berupa string            |
| Karakter           | Setiap karakter dalam teks          |
| Frekuensi karakter | Jumlah kemunculan setiap karakter   |
| Kode kompresi      | Representasi kode hasil encoding    |
| Ukuran data        | Ukuran sebelum dan sesudah kompresi |

---

## Aktivitas Sistem (Wajib)

Sistem minimal harus mendukung:

- Input data teks
- Analisis frekuensi karakter
- Generate kode kompresi sederhana
- Search kode karakter
- Dekompresi data teks

---

## Fokus Analisis Struktur Data

Proyek ini akan menganalisis bagaimana struktur data mempengaruhi performa sistem, khususnya pada:

- Kecepatan analisis frekuensi karakter
- Kecepatan encoding
- Kecepatan decoding
- Efisiensi penggunaan memori
- Dampak pertumbuhan ukuran data terhadap performa sistem

---

## Target Progress (Minggu ke-7)

Checklist progress awal:

- [ ] Spesifikasi sistem
- [ ] Skenario penggunaan data teks
- [ ] Implementasi minimal 1 struktur data
- [ ] Dataset awal (teks dummy / simulasi)
- [ ] Pengujian awal analisis frekuensi karakter
- [ ] Pengujian encoding sederhana

---

## Target Final (Minggu ke-14)

Deliverables akhir proyek:

- [ ] Implementasi ≥ 2 struktur data
- [ ] Grafik perbandingan waktu eksekusi
- [ ] Grafik penggunaan memori
- [ ] Demo aplikasi kompresi data
- [ ] Demo aplikasi dekompresi data
- [ ] Laporan analisis performa
- [ ] Rekomendasi struktur data terbaik

---

## Catatan Penting

- Tidak perlu implementasi algoritma kompresi kompleks.
- Algoritma kompresi boleh sederhana.
- Penilaian utama ada pada pemilihan struktur data dan analisis performa sistem.
