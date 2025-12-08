#include<stdio.h>
#include<math.h>
#include<windows.h>

int base_margin = 20; // remember, the sin value will be negative
int main()
{
    int i = 0;
    float angle = 0;


    printf("\033[1;36m"); // cyan color - light blue
    
    while(1)
    {
        int breadth = base_margin + (int)(sin(angle) * 10);
        
        for(int i = 0; i < breadth; i++)
        {
            printf("#");
        }
        printf("\n");

        angle += 0.1;
        i++;

        Sleep(50);
    }
}