#include <stdio.h>
#include <stdint.h>

void swap(void * a, void * b, size_t size);

typedef struct {
    char name [20];
    int age; 
}Person;



int main (void)
{
    int integer_num1 = 10;
    int integer_num2 = 20;

    double double_num1 = 3.141592;
    double double_num2 = 99.99000;

    Person struct_data1 = {"KIM", 1};
    Person struct_data2 = {"LEE", 2};

    size_t size = sizeof(integer_num1);
    printf("=== Day 9: Generic Swap Implementation ===\r\n\r\n");
    printf("[Int] Before: %d, %d\r\n", integer_num1, integer_num2);
    swap(&integer_num1, &integer_num2, size);
    printf("[Int] After : %d, %d\r\n\r\n",integer_num1, integer_num2);

    size = sizeof(double_num1);
    printf("[double] Before: %lf, %lf\r\n", double_num1, double_num1);
    swap(&double_num1, &double_num2, size);
    printf("[double] After : %lf, %lf\r\n\r\n",double_num1, double_num1);

    size = sizeof(struct_data1);
    printf("[struct] After : %s(%d), %s(%d)\r\n",
        struct_data1.name, struct_data1.age, struct_data2.name, struct_data2.age);
    swap(&struct_data1, &struct_data2, size);
    printf("[struct] After : %s(%d), %s(%d)\r\n\r\n",
        struct_data1.name, struct_data1.age, struct_data2.name, struct_data2.age);

    return 0;
}
void swap(void*a, void *b, size_t size)
{
    for (int i = 0; i < size ; i++)
    {
        uint8_t temp;
        temp = *((uint8_t*)a  + i);
        *((uint8_t*)a+i) = *((uint8_t*)b+i);
        *((uint8_t*)b+i) = temp;
    }
}