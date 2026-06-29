
#include <stdio.h>

int main (){
    int x = 10;
    int *p = &x;

    printf("p   = %p\n", p);
    printf("p + 1  = %p\n", p + 1);
    printf("p + 2  = %p\n", p + 2);
    


    return 0 ;

}
