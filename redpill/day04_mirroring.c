#include <stdint.h>
#include <stdio.h>

void mirrorInit(void);
void mirroring (uint8_t * data);
void compare(uint8_t * org , uint8_t * mirror, int length);
void binaryPrint(uint8_t *data);
void linePrint(void);
void inputPrint(int i, uint8_t arr);
void outputPrint(uint8_t arr);

int main (int argc , char const * argv[])
{
    uint8_t arr[] = {0xD2, 0x0F, 0xAA, 0x12};

    mirrorInit();

    for (int i = 0; i < (sizeof(arr)/sizeof(arr[0]));i++)
    {   
        uint8_t org = *(arr+i);
        inputPrint(i+1, *(arr+i));
        binaryPrint(arr+i);
        mirroring(arr+i);
        outputPrint(*(arr+i));
        binaryPrint(arr+i);
        compare(&org, arr+i, 8);
        linePrint();
    }

    return 0;
}

void mirrorInit(void)
{
    printf("=== Day 4: Bitwise Reverse (Mirroring) ===\r\n");
}

//Source: HAKMEM, MIT AI Memo 239 (1972).
void mirroring (uint8_t * data)
{
    *data = ((((*data)*(0x0808080808ULL))&
            ((1ULL<<27)|(1ULL<<36)|(1ULL<<5)|
            (1ULL<<14)|(1ULL<<23)|(1ULL<<32)|
            (1ULL<<41)|(1ULL<<10)))%1023);
}

void compare(uint8_t * org , uint8_t * mirror, int bit_num)
{   
    printf("\tVerify:  ");
    int count = 0;
    for (int i = 0 ; i <bit_num; i++)
    {
        if(((((*org)>>(7-i))&1)^(((*mirror)>>(i))&1))==0)
        {
            count++;
        }  
    }
    if (count == bit_num)
    {
        printf("OK\r\n");
    }
    else
    {
        printf("NO\r\n");
    }
}

void binaryPrint(uint8_t *data)
{   
    printf("(");
    for (int i = 7 ; i >=0;i--)
    {
        printf("%d", ((*data)>>i)&1);
        if (i==4)
        {
            printf(" ");
        }
    }
    printf(")\r\n");
}

void linePrint(void)
{
    printf("------------------------------------------------\r\n");
}

void inputPrint(int i, uint8_t arr)
{
    printf("Case %d:\r\n\tInput  :  0x%02X ",i, arr);
}

void outputPrint(uint8_t arr)
{
    printf("\tOutput:  0x%02X ",arr);
}