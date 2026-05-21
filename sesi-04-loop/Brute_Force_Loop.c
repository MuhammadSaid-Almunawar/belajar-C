#include <stdio.h>

int main() {
    char target = 'x';
    int  nomor  = 0;

    for (int i = 32; i <= 127; i++) {
        nomor++;
        printf("mencoba: %c (ASCII: %d)\n", i, i);
        if (i == target) {
            printf("ditemukan: %c (ASCII: %d) setelah %d percobaan\n", i, i, nomor);
            break;
        }
    }

    return 0;
}
// Output akhir: ditemukan: x (ASCII: 120) setelah 89 percobaan