#include<stdio.h>
#include<windows.h>

#define width 60
#define height 20

int x_pos = 10;
int y_pos = 5;

int color = 1;

int dx = 1;
int dy = 1;

int main()
{
    printf("\033[?25l");
    while(1)
    {
        printf("\033[H"); // bring the cursor to the starting point - alternative to system("cls")

        printf("Bouncing Text\n");

        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                if(i == y_pos && j == x_pos)
                {
                    printf("\033[1;%dmMOHAN\033[0m", 30 + color);
                    j+=4;
                }
                else if( i == 0 || i == height - 1)
                {
                    printf("-");
                }
                else if(j == 0 || j == width - 1)
                {
                    printf("|");
                }
                else{
                    printf(" ");
                }
            }
            printf("\n");
        }

        printf("position x: %d position y: %d   ", x_pos, y_pos);

        x_pos += dx;
        y_pos += dy;

        int hit = 0;
        if(x_pos <= 1 || x_pos == width - 6)
        {
            dx *= -1;
            hit = 1;
        }
        
        if(y_pos <= 1 || y_pos == height - 2)
        {
            dy *= -1;
            hit = 1;
        }

        if(hit)
        {
            color = (color % 6) + 1; // keep 0 - 6
        }
        
        Sleep(50); // in milliseconds
    }
}

/*
31,Red
32,Green
33,Yellow
34,Blue
35,Magenta (Purple)
36,Cyan (Light Blue)
37,White
*/
