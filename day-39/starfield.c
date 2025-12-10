#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define HEIGHT 25
#define WIDTH 80

#define NUM_STARS 200

typedef struct Star
{
    float x, y, z;
    int color_code;
} Star;

Star stars[NUM_STARS];
float speed = 10.0f;

// 40 rows * 80 cols * 20 chars for color codes + another 1000 for the new line and other chars => ~ 65000 chars
char render_buffer[65000];

void setup()
{
    srand(time(NULL));
    for(int i = 0; i < NUM_STARS; i++)
    {
        stars[i].x = (rand() % 600) - 300;
        stars[i].y = (rand() % 600) - 300;
        stars[i].z = (rand() % 600) + 1;

        stars[i].color_code = 31 + rand() % 6;
    }
}

char grid[HEIGHT][WIDTH];
int colors[HEIGHT][WIDTH];
int zoom_factor = 100;

int main()
{
    
    printf("\033[?25l");
    while(1)
    {

        // clear the grid
        for(int i = 0; i < HEIGHT; i++)
        {
            for(int j = 0; j < WIDTH; j++)
            {
                grid[i][j] = ' ';
                colors[i][j] = 0;
            }
        }

        // move the stars backward
        for(int i = 0; i < NUM_STARS; i++)
        {
            stars[i].z -= speed;

            if(stars[i].z < 1)
            {
                stars[i].z = 600;
                stars[i].x = (rand() % 600) - 300;
                stars[i].y = (rand() % 600) - 300;

                stars[i].color_code = 31 + rand() % 6;
            }

            int screen_x = ((stars[i].x / stars[i].z) * zoom_factor) + WIDTH / 2;
            int screen_y = ((stars[i].y / stars[i].z) * zoom_factor / 2) + HEIGHT / 2;

            if(screen_x >= 0 && screen_x < WIDTH && screen_y >= 0 && screen_y < HEIGHT)
            {
                char symbol = stars[i].z < 200 ? '@' : '.';

                grid[screen_y][screen_x] = symbol;
                colors[screen_y][screen_x] = stars[i].color_code;

                if(stars[i].z < 300)
                {
                    int trail_x = (stars[i].x / (stars[i].z + 40)) * zoom_factor + (WIDTH / 2); // the trail is a bit back
                    int trail_y = (stars[i].y / (stars[i].z + 40)) * zoom_factor / 2 + (HEIGHT / 2);

                    if(trail_x >= 0 && trail_x < WIDTH && trail_y >= 0 && trail_y < HEIGHT)
                    {
                        if(grid[trail_y][trail_x] == ' ')
                        {
                            grid[trail_y][trail_x] = '-';
                            colors[trail_y][trail_x] = stars[i].color_code;
                        }
                    }
                }
            }
            
        }

        // render to the buffer

        // if we don't keep track of the character count, sprintf will start overwriting again

        int p = 0;
        p += sprintf(render_buffer + p, "\033[H");

        p += sprintf(render_buffer + p, "Day - 39 - Starfield Animation (Warp Speed)\n");

        for(int i = 0; i < HEIGHT; i++)
        {
            for(int j = 0; j < WIDTH; j++)
            {
                if(grid[i][j] == ' ')
                {
                    render_buffer[p++] = grid[i][j];
                }
                else
                {
                    p += sprintf(render_buffer + p, "\033[1;%dm%c", colors[i][j], grid[i][j]);
                }
            }
            p += sprintf(render_buffer + p, "\033[0m\n"); // reset color at the end of the row to prevent bleeding
        }

        printf("%s", render_buffer);
        Sleep(30);
        
    }
    
}