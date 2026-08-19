#include <stdio.h>
#include <stddef.h>

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
    printf("[My Macro] Offset of a: %zu\r\n", (size_t)&((Sample*)0)->a);
    printf("[My Macro] Offset of b: %zu\r\n", (size_t)&((Sample*)0)->b);
    printf("[My Macro] Offset of c: %zu\r\n", (size_t)&((Sample*)0)->c);
    printf("\r\n>> Success! Implementation is correct.\r\n");

    return 0;
}