#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

void main(void)
{
    srand(time(NULL)); // seed the random number generator
    printf("Day 34 - Matrix Effect in \n");

    printf("\033[1;32m\033[?25l"); // \033 - means - escape character for a command
    // [ - start of a command
    // 1 - bold
    // 32 - green
    // m - end of a command

    // \033[?25l - for hiding the cursor
    while ((1))
    {
        int r = rand() % 2; // get zero or one
        int space = rand() % 20;

        if(space < 5)
        {
            printf(" ");
        }
        else{
            printf("%d", r);
        }

        // randomly break to create the falling effect
        if(rand() % 25 == 0)
        {
            printf("\n"); 
        }
        Sleep(1); // millisecond
    }
    printf("\033[0m"); // reset terminal color


}