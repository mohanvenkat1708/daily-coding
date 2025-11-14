#include<stdio.h>
int main()
{
    printf("Patterns:\n");
    
    // steps:
    // 1. Count the rows -> outer loop
    // 2. For Every row, How many elements are there
    //    How many symbols are there


    // * square
    int size = 5;
    for(int i = 1; i <= size; i++)
    {
        for(int j = 1; j <= size; j++)
        {
            printf("* ");
        }
        printf("\n");
    }


    // * triangle
    int row = 5;
    int col = 5;

    for(int i = 1; i <= row; i++)
    {
        for(int j = 1; j <= i; j++)
        {
            printf("* ");
        }
        printf("\n");
    }

    // * inverse triangle
    for(int i = 1; i <= row; i++)
    {
        for(int j = 1; j <= col - i + 1; j++)
        {
            printf("* ");
        }
        printf("\n");
    }

    // * pyramid

    row = 10;
    col = 10;
    for(int i = 1; i <= row; i++)
    {
        for(int j = 1; j <= col - i; j++)
        {
            printf("  ");
        }
        for(int k = 1; k <= (2 * i) - 1; k++)
        {
            printf("* ");
        }
        printf("\n");
    }
}