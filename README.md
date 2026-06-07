# Belajar C — Kurikulum untuk Cybersecurity

> Dokumentasi perjalanan belajar bahasa C dengan fokus pada **Exploit Development** dan **Security Research**.  
> Repo ini aktif diupdate seiring progress belajar.

---

## 🎯 Tujuan

Bukan sekadar belajar sintaks C — tapi memahami bagaimana program bekerja di level memory, yang menjadi fondasi dari:
- Buffer overflow & exploit development
- Analisis malware di level rendah
- Reverse engineering binary
- Penulisan security tools dari nol

---

## 📊 Progress Belajar

| Sesi | Topik | Status | File Utama |
|------|-------|--------|------------|
| 01 | Struktur Program & Kompilasi | ✅ Selesai | `first.c` |
| 02 | Tipe Data, Memory & Integer Overflow | ✅ Selesai | `integer_overflow.c` |
| 03 | Operator, Bitwise & XOR Encryption | ✅ Selesai | `xor_encrypt.c` |
| 04 | Loop & Brute Force Logic | ✅ Selesai | `brute_force_pin.c`, `brute_force_char.c` |
| 05 | Function, Stack Frame & Null Terminator | ✅ Selesai | `cetak_hex.c` |
| 06 | Array & Memory Address | 🔄 On Progress | `array_memory.c` |
| 07 | Pointer | ⏳ Belum | — |
| 08 | String & Buffer Manipulation | ⏳ Belum | — |
| 09 | Dynamic Memory (malloc/free) | ⏳ Belum | — |
| 10 | Struct & Memory Layout | ⏳ Belum | — |

---

## 🧠 Konsep yang Sudah Dikuasai

- **Integer Overflow** — bagaimana nilai integer meluber dan kenapa ini menjadi vulnerability nyata (kasus Ariane 5, Diablo III)
- **XOR Encryption** — implementasi enkripsi/dekripsi manual; teknik yang dipakai malware untuk menyembunyikan string dari antivirus
- **Brute Force Logic** — implementasi character-by-character brute force dari level bit
- **Stack Frame** — bagaimana function membuat ruang memory sendiri saat dipanggil
- **Return Address** — mengapa ini menjadi target utama buffer overflow
- **Null Terminator** — bagaimana string disimpan di memory dan kenapa absennya `\0` bisa dieksploitasi
- **Memory Address** — membaca alamat memory langsung dari program menggunakan `%p`

---

## 🔗 Koneksi ke Cybersecurity

Setiap sesi dirancang dengan konteks security nyata:

```
Sesi 02 — Integer Overflow  →  Pernah meledakkan roket Ariane 5 (1996)
Sesi 03 — XOR              →  Teknik obfuscation yang dipakai malware nyata  
Sesi 04 — Loop + Brute     →  Fondasi dari tools seperti Hydra dan Medusa
Sesi 05 — Stack Frame      →  Landasan memahami buffer overflow
Sesi 06 — Memory Address   →  Dasar untuk pointer dan exploit writing
Sesi 07 — Pointer          →  Titik kritis menuju exploit development
```

---

## 📁 Struktur Repository

```
belajar-C/
├── sesi-01-struktur/
│   ├── summary.md
│   └── first.c
├── sesi-02-tipe-data/
│   ├── summary.md
│   └── integer_overflow.c
├── sesi-03-operator/
│   ├── summary.md
│   └── xor_encrypt.c
├── sesi-04-loop/
│   ├── summary.md
│   ├── brute_force_pin.c
│   └── brute_force_char.c
├── sesi-05-function/
│   ├── summary.md
│   └── cetak_hex.c
└── sesi-06-array/
    ├── summary.md
    └── array_memory.c
```

---

## 🛣️ Roadmap Selanjutnya

Setelah kurikulum C selesai, fondasi ini akan dipakai untuk:

- **pwn.college** — binary exploitation challenges
- **Buffer Overflow praktik** — THM Buffer Overflow Prep room
- **pwntools** — Python library untuk exploit development
- **CTF kategori Pwn** — kompetisi capture the flag

---

*Repo ini bagian dari perjalanan menuju **Exploit Developer** dan **Security Researcher**.*  
*Lihat juga: [soc-analyst-portfolio](https://github.com/MuhammadSaid-Almunawar/soc-analyst-portfolio)*
