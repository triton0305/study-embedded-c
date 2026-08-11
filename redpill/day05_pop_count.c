#include<stdio.h>
#include<stdint.h>
void initPrint(void);
void inputPrint(int i, uint32_t input);
void kernighanAlgorithm(uint32_t data);
void swarAlgorithm(uint32_t data);

int main(int argc, char const * argv[])
{   
    uint32_t arr[] = {0x00000000, 0x00000007, 0x12345678, 0xFFFFFFFF};
    initPrint();
    for (int i = 0 ; i < sizeof(arr)/sizeof(arr[0]); i++)
    {
        inputPrint(i, arr[i]);
        // Native
        kernighanAlgorithm(arr[i]);
    }







    return 0;
}

void initPrint(void)
{
    printf("=== Day 5: Population Count (Counting Set Bits) ===");
}

void inputPrint(int i, uint32_t input)
{
    printf("Case %d: Input 0x%08X\r\n", i+1, input);
}

void kernighanAlgorithm(uint32_t data)
{   
    int count = 0;
    while (data)
    {
        data = data & (data-1);
        count+=1;
    }
    printf("\t[Kernighan] : %d (Recommended Logic)", count);
}

void swarAlgorithm(uint32_t data)
{
    data = (data-((data>>1)&(0x55555555)));
    data = (data&0x33333333)+((data>>2)&0x33333333);
    data = (data+(data>>4))&0x0F0F0F0F;
    data = (data+(data>>8));
    data = (data+(data>>16));
    data &= 0x3F;
    printf("\t[SWAR]      : %d (Strict Loop-free)\r\n", (unsigned int)data);
}