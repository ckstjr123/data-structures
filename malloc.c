#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define SIZE 10

int main(void) {

    int *p = (int *) malloc(SIZE * sizeof(int));
    if (p == NULL) {
        fprintf(stderr, "힙 메모리 부족하므로 할당 불가\n");
        exit(1);
    }

    for (int i = 0; i < SIZE; i++){
        p[i] = i;
    }
    
    *p = 10000;
    *(p+1) = 20000;
    *(p+2) = 30000;
    for (int i = 0; i < SIZE; i++){
        printf("%d\n", p + i);
        printf("%d\n", p[i]);
    }

    free(p);
    return 0;
}