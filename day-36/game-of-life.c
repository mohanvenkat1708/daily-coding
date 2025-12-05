#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define width 40
#define height 20

int grid[height][width];
int new_grid[height][width];

int count_neighbours(int row, int col)
{
    int count = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if(i == 0 && j == 0)
            {
                // skip self
                continue;
            }

            int new_row = row + i;
            int new_col = col + j;
            
            if (new_row >= 0 && new_row < height && new_col >= 0 && new_col < width)
            {
                if (grid[new_row][new_col] == 1)
                {
                    count++;
                }
            }
        }
    }
    return count;
}

int main()
{
    srand(time(NULL));

    printf("\033[?25l"); // hide the cursor

    // initialize the grid randomly
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            grid[i][j] = rand() % 2;
        }
    }

    while (1)
    {
        printf("\033[H"); // reset the cursor

        printf("Day - 36 - Conway's Game of Life\n\n");

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (grid[i][j] == 1)
                {
                    printf("\033[1;32mO");
                }
                else
                {
                    printf(" ");
                }   
            }
            printf("\n");
        }

        // applying the rules of life:
        // 1. Loneliness - if neighbour count < 2, dies
        // 2. OverCrowding - if neighbour count > 3, dies
        // 3. Survival - if neighbour count 2 or 3, survives
        // 4. Reproduction - if dead cell has exactly 3 neighbours, it becomes alive

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int neighbour_count = count_neighbours(i, j);
                if (grid[i][j] == 1)
                {
                    // dies or stay alive
                    if (neighbour_count > 3 || neighbour_count < 2)
                    {
                        // update in the new grid
                        new_grid[i][j] = 0;
                    }
                }
                else
                {
                    // get born or stay dead
                    if (neighbour_count == 3)
                    {
                        new_grid[i][j] = 1;
                    }
                }
            }
        }

        // update the grid

        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                grid[i][j] = new_grid[i][j];
            }
        }

        Sleep(50);
    }
}