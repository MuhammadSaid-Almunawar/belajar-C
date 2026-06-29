#include <stdio.h>

int main() {
    int rahasia = 99;
    int nilai[5] = {10, 20, 30, 40, 50};

    printf("sebelum  → rahasia = %d\n", rahasia);
    printf("alamat nilai[5] = %p\n", &nilai[5]);
    printf("alamat rahasia  = %p\n", &rahasia);

    nilai[5] = 1337;
    nilai[6] = 1337;
    nilai[7] = 1337;

    printf("sesudah  → rahasia = %d\n", rahasia);

    return 0;
}
