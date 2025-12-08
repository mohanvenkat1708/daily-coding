#include<stdio.h>
#include<math.h>
#include<windows.h>

int base_margin = 20; // remember, the sin value will be negative

int main()
{
    int i = 0;
    float angle = 0.0;

    while(1)
    {
        int pos1 = base_margin + (int)(sin(angle) * 10);
        int pos2 = base_margin + (int)(sin(angle + 3.14159) * 10);

        int left = (pos1 < pos2) ? pos1 : pos2;
        int right = (pos1 > pos2) ? pos1 : pos2;

        for(int i = 0; i < left; i++)
        {
            printf(" ");
        }
        printf("\033[1;37mO"); // left part

        int color_code = 31 + ((i/2) % 6); // dividing by 2 to slow down the color change

        // the gap between the strands

        printf("\033[1;%dm", color_code);

        for(int i = 0; i < (right - left) - 1; i++)
        {
            if(right - left > 2)
            {
                printf("-");
            }
            else
            {
                printf(" ");
            }
        }

        printf("\033[1;37mO");
        printf("\n");
        
        angle += 0.1;
        i++;

        Sleep(25);
    }
}