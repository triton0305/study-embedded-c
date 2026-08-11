#include <stdint.h>
#include <stdio.h>

void reverse(uint8_t *data);
void print_binary(uint8_t data);
void compare(uint8_t org_data, uint8_t res_data);

int main(int argc, char const *argv[])
{
    uint8_t input_num[] = {0xD2, 0x0F, 0xAA, 0x12};

    printf("=== Day 4: Bitwise Reverse (toTheMoon) ===\r\n");

    for (int i = 0; i < sizeof(input_num) / sizeof(input_num[0]); i++)
    {
        printf("Case %d:\r\n", i + 1);

        printf("\tInput  : 0x%02X ", *(input_num+i));
        print_binary(*(input_num+i));

        uint8_t org_num = *(input_num+i);

        reverse((input_num+i));

        printf("\tOutput : 0x%02X ", *(input_num+i));
        print_binary(*(input_num+i));

        printf("\tVerify : ");
        compare(org_num, *(input_num+i));

        printf("--------------------------------\r\n");
    }

    return 0;
}

void reverse(uint8_t *data)
{
    *data = (((*data)*0x2020202020ULL)&
            ((1ULL<<37)|(1ULL<<6)|(1ULL<<15)|
            (1ULL<<24)|(1ULL<<33)|(1ULL<<42)|
            (1ULL<<11)|(1ULL<<20)))%1023;
}

void print_binary(uint8_t data)
{
    printf("(");
    for (int i = 7 ; i >= 0 ; i --)
    {   
        printf("%d", (data>>i)&1);
        if (i == 4)
        {
            printf(" ");
        }
    }
    printf(")\r\n");
}

void compare(uint8_t org_data, uint8_t res_data)
{   int count = 0;
    for (int i = 0; i < 8 ; i++)
    {
        if ((((org_data>>(7-i))&1)^((res_data>>i)&1))==0)
        {
            count++;
        }
    }
    if (count == 8)
    {
        printf("OK\r\n");
    }
    else
    {
        printf("NO\r\n");
    }

}