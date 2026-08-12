#include <stdio.h>
#include <stdint.h>

#define max_rot 32

typedef struct{
    uint32_t input;
    int index;
    int rot_cnt;
}test;

void printInit (void);
void printBinary(uint32_t data);
void printPrologue(test data);
void rotateRight(test* data);
void rotateLeft(test* data);


int main (int agrc, char const * argv [])
{
    printInit();
    test firstTest = {
        .input = 0xF0000000u,
        .index = 1,
        .rot_cnt = 4
    };
    test secondTest = {
        .input = 0x12345678u,
        .index = 2,
        .rot_cnt = 8
    };
    printPrologue(firstTest);
    rotateRight(&secondTest);

    return 0;
}

void printInit(void)
{
    printf("=== Day 6: Circular Shift (Rotate) ===\r\n");
    printf("\r\n");
}

void printBinary(uint32_t data)
{
    for (int i = 31; i >= 0 ; i--)
    {
        printf("%u", (data>>i)&1u);
        if (!(i%4)) printf(" ");
    }
    printf("\r\n");
}

void printPrologue(test data)
{   
    printf("[Init]   Hex: 0x%08X\r\n         Bin: ", data.input);
    printBinary(data.input);
    printf("\r\n");
    data.input = ((data.input)<<(data.rot_cnt))|((data.input)>>(max_rot-data.rot_cnt));
    printf("[ROL %d]  Hex: 0x%08X\r\n         Bin: ", data.rot_cnt, data.input);
    printBinary(data.input);
    printf("         (MSB bits moved to LSB)\r\n");
        printf("\r\n");
    data.input = ((data.input)>>(data.rot_cnt))|((data.input)<<(max_rot-data.rot_cnt));
    printf("[ROR %d]  Hex: 0x%08X\r\n         Bin: ", data.rot_cnt, data.input);
    printBinary(data.input);
    printf("         (Restored to original)\r\n");
    printf("\r\n");
}

void rotateRight(test* data)
{
    printf("[test %d] Data: 0x%08X -> ",data->index, data->input);
    data->input = ((data->input)>>(data->rot_cnt))|((data->input)<<(max_rot-data->rot_cnt));
    printf("ROR %d -> 0x%08X\r\n", data->rot_cnt, data->input);
}

void rotateLeft(test* data)
{
    printf("[test %d] Data: 0x%08X -> ",data->index, data->input);
    data->input = ((data->input)<<(data->rot_cnt))|((data->input)>>(max_rot-data->rot_cnt));
    printf("ROL %d -> 0x%08X\r\n", data->rot_cnt, data->input);
}
