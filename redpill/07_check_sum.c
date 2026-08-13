#include <stdio.h>
#include <stdint.h>

uint8_t checkSum(uint8_t data[], int data_width);
void printTX(uint8_t *data, int data_width, uint8_t TX_check_sum);
void runRX(uint8_t data[], int data_width, uint8_t TX_check_sum);

int main(void)
{
    printf("=== Day 7: XOR Checksum Calculation ===\r\n\r\n");

    uint8_t data[] = {0x01, 0x04, 0x10, 0x20, 0x30, 0x40};
    int data_width = sizeof(data)/sizeof(data[0]);
    uint8_t TX_check_sum = checkSum(data, data_width);
    printTX(data, data_width, TX_check_sum);
    runRX(data, data_width, TX_check_sum);


    uint8_t corrupted_data[] = {0x01, 0x04, 0xEF, 0x20, 0x30, 0x40};
    runRX(corrupted_data, data_width, TX_check_sum);
    return 0;
}

uint8_t checkSum(uint8_t data[], int data_width)
{
    uint8_t check_sum = 0x00;
    for (int i = 0 ; i < data_width; i++)
    {
        check_sum ^= *(data+i);
    }

    return check_sum;
}

void printTX(uint8_t *data, int data_width, uint8_t TX_check_sum)
{
    printf("[TX] Sending Packet...\r\n");
    printf("     Data:");
    for(int i = 0; i < data_width ; i++) printf(" 0x%02X", *(data+i));
    printf("\r\n     Calculated Checksum: 0x%02X\r\n\r\n", TX_check_sum);
}

void runRX(uint8_t data[], int data_width, uint8_t TX_check_sum)
{
    uint8_t RX_check_sum = checkSum(data, data_width);
    uint8_t result = TX_check_sum^RX_check_sum;
    if(!(result))
    {
        printf("[RX] Receiving Normal Packet...\r\n");
        printf("     >> Verification SUCCESS (Result: 0x00)\r\n\r\n");
    }
    else
    {
        printf("[RX] Receiving Corrupted Packet (Noise injected)...\r\n");
        printf("     Corrupted Data: ");
        for(int i = 0; i < data_width ; i++) printf(" 0x%02X", *(data+i));
        printf("\r\n     >> Verification FAIL (Result: 0x%02X)\r\n", result);
        printf("     >> Error detected! Discarding packet.\r\n\r\n");
    }
}