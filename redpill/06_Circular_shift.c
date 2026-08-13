#include <stdio.h>
#include <stdint.h>

#define BIT_WIDTH 32

typedef struct{
    uint32_t input;
    unsigned int index;
    unsigned int rot_cnt;
}rotateTest;

void printInit (void);
void printBinary(uint32_t data);
void printLogue(rotateTest data);
void leftRun(rotateTest*data);
void rightRun(rotateTest*data);

rotateTest leftShifter(rotateTest data);
rotateTest rightShifter(rotateTest data);

int main (int argc, char const * argv [])
{
    printInit();

    rotateTest firstTest = {
        .input = 0xF0000000u,
        .index = 1,
        .rot_cnt = 4
    };

    rotateTest secondTest = {
        .input = 0x12345678u,
        .index = 2,
        .rot_cnt = 8
    };

    printLogue(firstTest);

    rightRun(&secondTest);

    return 0;
}

void printInit(void)
{
    printf("=== Day 6: Circular Shift (Rotate) ===\r\n");
    printf("\r\n");
}

void printBinary(uint32_t data)
{
    for (int i = BIT_WIDTH-1; i >= 0 ; i--)
    {
        printf("%u", (data>>i)&1u);
        if (!(i%4)) printf(" ");
    }
    printf("\r\n");
}


void printLogue(rotateTest data)
{   
    printf("[Init]   Hex: 0x%08X\r\n         Bin: ", data.input);
    printBinary(data.input);
    printf("\r\n");
    data = leftShifter(data);
    printf("[ROL %u]  Hex: 0x%08X\r\n         Bin: ", data.rot_cnt, data.input);
    printBinary(data.input);
    printf("         (MSB bits moved to LSB)\r\n");
    printf("\r\n");
    data = rightShifter(data);
    printf("[ROR %u]  Hex: 0x%08X\r\n         Bin: ", data.rot_cnt, data.input);
    printBinary(data.input);
    printf("         (Restored to original)\r\n");
    printf("\r\n");
}

void leftRun(rotateTest*data)
{
    printf("[Test %u] Data: 0x%08X -> ",data->index, data->input);
    *data = leftShifter(*data);
    printf("ROL %u -> 0x%08X\r\n", data->rot_cnt, data->input);
}

void rightRun(rotateTest*data)
{
    printf("[Test %u] Data: 0x%08X -> ",data->index, data->input);
    *data = rightShifter(*data);
    printf("ROR %u -> 0x%08X\r\n", data->rot_cnt, data->input);
}

rotateTest leftShifter(rotateTest data)
{
    data.rot_cnt %= BIT_WIDTH;
    if (data.rot_cnt == 0) return data;
    data.input = ((data.input)<<(data.rot_cnt))|((data.input)>>(BIT_WIDTH-data.rot_cnt));
    return data;
}

rotateTest rightShifter(rotateTest data)
{
    data.rot_cnt %= BIT_WIDTH;
    if (data.rot_cnt == 0) return data;
    data.input = ((data.input)>>(data.rot_cnt))|((data.input)<<(BIT_WIDTH-data.rot_cnt));
    return data;
}
