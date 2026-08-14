#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    size_t row = 3;
    size_t col = 4;
    int * arr = malloc (row * col * sizeof(*arr));
    if (arr == NULL) return 1;
    int ** ptr = malloc(row * sizeof(*ptr));
    if (ptr == NULL)
    {   
        free(arr);
        return 1;
    }
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
    for (size_t i =  0; i < (row*col) ; i++) *(arr+i) = (int)(i+1); 
    for (size_t i = 0; i < row ; i++) *(ptr+i) = (arr+i*col);
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
    printf("=== Day 10: Dynamic 2D Array Allocation ===\r\n\r\n");
    printf("Generated Matrix (%zux%zu):\r\n", row, col);
    for (size_t i = 0 ; i < row; i++) 
    {
        for(size_t j = 0 ; j < col ; j++)
        {
            printf("%2d ", *(*(ptr+i)+j));
        }
        printf("\r\n");
    }
    for (size_t i = 0 ; i < row ; i++)
    {        
        if(*(ptr+i) == arr+(i*col))
        {
            if(i+1 == row)
            {
                free(arr);
                free(ptr);
                printf("\r\n>> Memory successfully freed.\r\n");
            }
        }
        else
        {
            free(arr);
            free(ptr);
            printf("\r\n>> Verification failed, but memory was safely freed.\r\n");
            break;
        }
    }

    return 0 ;
}