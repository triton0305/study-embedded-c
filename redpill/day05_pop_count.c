#include<stdio.h>
#include<stdint.h>
#include<intrin.h>

typedef struct {
    int num;
    int count;
    uint32_t data;
}pill;

void initPrint(void);
void inputPrint(int i, uint32_t input);
void count4Bit(pill * p_pill);
void count32Bit(pill * p_pill);
void kernighanAlgorithm(uint32_t data);
void swarAlgorithm(uint32_t data);
void builtIn(uint32_t data);
void linePrint(void);
void runCase(pill dream);

int main(int argc, char const * argv[])
{   
    initPrint();
    pill eins = {
        .num = 1,
        .count = 0,
        .data = 0x00000000u
    };
    runCase(eins);
//===============================================
    pill zwei = {
        .num = 2,
        .count = 0,
        .data = 0x00000007u
    };
    runCase(zwei);
//===============================================
    pill drei = {
        .num = 3,
        .count = 0,
        .data = 0x12345678u
    };
    runCase(drei);
//===============================================
    pill vier = {
        .num = 4,
        .count = 0,
        .data = 0xFFFFFFFFu
    };
    runCase(vier);
    return 0;
}

void initPrint(void)
{
    printf("=== Day 5: Population Count (Counting Set Bits) ===\r\n");
}

void inputPrint(int i, uint32_t input)
{
    printf("Case %d: Input 0x%08X\r\n", i, input);
}

void count4Bit(pill* p_pill)
{
    if((p_pill->data)&1u) p_pill->count++;
    if(((p_pill->data)>>1)&1u) p_pill->count++;
    if(((p_pill->data)>>2)&1u) p_pill->count++;
    if(((p_pill->data)>>3)&1u) p_pill->count++;
}

void count32Bit(pill *p_pill)
{   
    count4Bit(p_pill);
    p_pill->data >>= 4;
    count4Bit(p_pill);
    p_pill->data >>= 4;
    count4Bit(p_pill);
    p_pill->data >>= 4;
    count4Bit(p_pill);
    p_pill->data >>= 4;
    count4Bit(p_pill);
    p_pill->data >>= 4;
    count4Bit(p_pill);
    p_pill->data >>= 4;
    count4Bit(p_pill);
    p_pill->data >>= 4;
    count4Bit(p_pill);
    printf("\t[Naive]     : %d\r\n",p_pill->count);
}

void kernighanAlgorithm(uint32_t data)
{   
    int count = 0;
    while (data)
    {
        data = data & (data-1u);
        count+=1;
    }
    printf("\t[Kernighan] : %d (Recommended Logic)\r\n", count);
}

void swarAlgorithm(uint32_t data)
{
    data = (data-((data>>1)&(0x55555555u)));
    data = (data&0x33333333u)+((data>>2)&0x33333333u);
    data = (data+(data>>4))&0x0F0F0F0Fu;
    data = (data+(data>>8));
    data = (data+(data>>16));
    data &= 0x3Fu;
    printf("\t[SWAR]      : %u (Strict Loop-free)\r\n",(unsigned int)data);
}

void builtIn(uint32_t data)
{
    int temp = __popcnt(data);
    printf("\t[Built-in]  : %d\r\n", temp);
}

void linePrint(void)
{
    printf("----------------------------------------\r\n");
}

void runCase(pill dream)
{
    uint32_t temp = dream.data;
    inputPrint(dream.num, dream.data);
    count32Bit(&dream);
    dream.data = temp;
    kernighanAlgorithm(dream.data);
    swarAlgorithm(dream.data);
    builtIn(dream.data);
    linePrint();
}