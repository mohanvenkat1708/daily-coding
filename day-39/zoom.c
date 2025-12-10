#include<stdio.h>
#include<windows.h>

#define WIDTH 40
#define HEIGHT 20

int star1_x = 10, star1_y = 5;
int star2_x = 20, star2_y = 10;
int star3_x = 30, star3_y = 15; 

char sizes[] = {'.', '+', '*', '0', '@'};
int current_size = 0;

int main()
{
    
    printf("\033[?25l"); // hide cursor
    while(1)
    {
        printf("\033[H"); // reset the cursor

        printf("Zoom in Animation\n");    
        
        // draw grid
        for(int i = 0; i < HEIGHT; i++)
        {
            for(int j = 0; j < WIDTH; j++)
            {
                if((i == star1_y && j == star1_x) || (i == star2_y && j == star2_x) || (i == star3_y && j == star3_x))
                {
                    printf("\033[1;33m%c", sizes[current_size]);
                }
                else
                {
                    printf(" ");
                }
            }
        }
        
        current_size++;
        current_size %= 5;

        Sleep(500);
    }
    
}