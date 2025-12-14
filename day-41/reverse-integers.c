#include<stdio.h>
#include<limits.h>

// 1234567 % 10 = 7
// 1234567 / 10
// 123456 % 10 = 6 

// (7 * 10) + 6
// 7654321

-14 % 10 = (-4 * 10) + (-1) = -41

int main()
{
    printf("Day 41 - reversing integers\n");

    int num;
    printf("The number to reverse: ");
    scanf("%d", &num);

    int reverse = 0;

    while(num != 0) // handle both positive and negative values
    {

        // num = 1534236469  // ✓ Valid int (< INT_MAX)
        // reverse = 9646324350  // ✓ Valid int (< INT_MAX)
        // 9646324351 - cause buffer overflow

        if(reverse > INT_MAX / 10)
        {
            printf("Buffer Overflow\n");
            break;
        }

        reverse*= 10;
        int digit = num % 10;
        num /= 10;

        reverse += digit;
    }

    printf("reversed value: %d", reverse);
    getch();
}