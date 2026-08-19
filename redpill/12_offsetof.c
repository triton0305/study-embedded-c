#include <stdio.h>
#include <stddef.h>

#define MY_OFFSET(STRUCT, DATA) (size_t)&((STRUCT*)0)->DATA

typedef struct {
    char a;     
    int b;       
    double c;    
} Sample;

int main(void)
{
    printf("=== Day 12: offsetof Implementation ===\r\n\r\n");
    printf("Struct Size: %zu bytes\r\n", sizeof(Sample));
    printf("[Standard] Offset of a: %zu\r\n",offsetof(Sample, a));
    printf("[Standard] Offset of b: %zu\r\n",offsetof(Sample, b));
    printf("[Standard] Offset of c: %zu\r\n",offsetof(Sample, c));
    printf("\r\n-----------------------------\r\n\r\n");
    printf("[My Macro] Offset of a: %zu\r\n", MY_OFFSET(Sample, a));
    printf("[My Macro] Offset of b: %zu\r\n", MY_OFFSET(Sample, b));
    printf("[My Macro] Offset of c: %zu\r\n", MY_OFFSET(Sample, c));
    printf("\r\n>> Success! Implementation is correct.\r\n");

    return 0;
}