#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

void studyMemmove(void *dest, const void * src, size_t size);
void dataPrint(const void * data, size_t size);
void testPrint(unsigned int * test_num, ptrdiff_t comp);

int main (void)
{
    unsigned int test_num = 1;
    uint8_t data1[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
    unsigned char * src = (unsigned char *)&data1[0];
    unsigned char * dest = (unsigned char *)&data1[2];
    size_t size = 5;

    printf("=== Day 8: Safe Memcpy (memmove) Implementation ===\r\n\r\n");
    printf("[Initial]");
    dataPrint(data1, sizeof(data1)/sizeof(data1[0]));
    testPrint(&test_num, dest - src);

    studyMemmove(dest , src, size);

    printf("[Result ]");
    dataPrint(data1, sizeof(data1)/sizeof(data1[0]));
    printf("\r\n>> Success!\r\n\r\n");
//=======================================================================================

    uint8_t data2[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
    src = (unsigned char *)&data2[2];
    dest = (unsigned char *)&data2[0];
    size = 5;
    printf("[Initial]");
    dataPrint(data2, sizeof(data2)/sizeof(data2[0]));
    testPrint(&test_num, dest - src);

    studyMemmove(dest , src, size);

    printf("[Result ]");
    dataPrint(data2, sizeof(data2)/sizeof(data2[0]));
    printf("\r\n>> Success!\r\n\r\n");

    return 0;
}

void studyMemmove(void *dest, const void * src, size_t size)
{
    ptrdiff_t comp = (unsigned char *)dest - (const unsigned char *)src ;
    if (comp < 0)
    {
        for (size_t i = 0 ; i < size ; i ++)
        {
            *((unsigned char *)dest+i) = *((const unsigned char*)src+i);
        }
    }
    else if (comp > 0)
    {
        for (size_t i = size - 1; i < size ; i--)
        {
            *((unsigned char *)dest+i) = *((const unsigned char*)src+i);
        }
    }
}

void dataPrint(const void * data, size_t size)
{
    for (size_t i = 0 ; i < size; i++) printf(" %02X", *((uint8_t*)data+i));
}

void testPrint(unsigned int * test_num, ptrdiff_t comp)
{
    if(comp > 0)
    {
        printf("\r\nTest %u: Overlap (Dest > Src) -> Shift Right %td bytes\r\n",
            *test_num ,comp);
        (*test_num) ++;
    }
    else if(comp == 0)
    {
        printf("\r\nTest %u: Overlap (Dest = Src) -> Not Shift\r\n",
            *test_num);
        (*test_num) ++;
    }
    else
    {   
        comp = -comp;
        printf("\r\nTest %u: Overlap (Dest < Src) -> Shift Left %td bytes\r\n",
            *test_num ,comp);
        (*test_num) ++;
    }
}