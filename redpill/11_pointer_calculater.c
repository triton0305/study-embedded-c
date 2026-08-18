#include <stdio.h>

enum{
    Add,
    Sub,
    Mul,
    Div,
    Exit
};

int (*calFunc[5])(int, int);
int numAdd(int num1, int num2);
int numSub(int num1, int num2);
int numMul(int num1, int num2);
int numDiv(int num1, int num2);

int main (void)
{
    int num1, num2, answer;
    int index = 305;
    printf("=== Day 11: Function Pointer Array Calculator ===\r\n\r\n");
    while(index<Add || index>Exit){
        printf("Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): ");
        scanf("%d", &index);
    }
    while(index!=Exit)
    {
        printf("Input two integers: ");
        scanf("%d %d", &num1, &num2);
        answer = calFunc[index](num1, num2);
        printf(">>> Result: %d\r\n\r\n", answer);
        index = 305;
        while(index<Add || index>Exit)
        {
            printf("Select (0:Add, 1:Sub, 2:Mul, 3:Div, 4:Exit): ");
            scanf("%d", &index);
        }
    }

    return 0;
}

int (*calFunc[5])(int, int)=
{
    [Add] = numAdd,
    [Sub] = numSub,
    [Mul] = numMul,
    [Div] = numDiv
};

int numAdd(int num1, int num2)
{
    return num1 + num2;
}

int numSub(int num1, int num2)
{
    return num1 - num2;
}

int numMul(int num1 , int num2)
{
    return num1 * num2;
}

int numDiv(int num1, int num2)
{
    return (num2==0) ? 0 : num1 / num2;
}