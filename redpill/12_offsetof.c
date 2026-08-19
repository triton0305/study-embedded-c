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
    printf("[My Macro] Offset of a: %zu", (size_t)&((Sample*)0)->a);

    return 0;
}