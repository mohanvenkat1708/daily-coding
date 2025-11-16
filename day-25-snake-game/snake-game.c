#include<stdio.h>
#include<stdlib.h> // for rand and srand
#include<time.h> // for time
#include<conio.h> // for _kbhit
#include<windows.h> // for Sleep

#define GRID_WIDTH 10
#define GRID_HEIGTH 10

#define MOVE_UP 0
#define MOVE_LEFT 1
#define MOVE_DOWN 2
#define MOVE_RIGHT 3

void set_border();
void init_snake();
void start_game();
void set_direction(char choice);
int move_snake();
void spawn_food();
int is_snake_pos(int row, int col);
int is_food_pos(int row, int col);

char grid[GRID_HEIGTH][GRID_WIDTH] = {' '};

int snake_head_row = -1;
int snake_head_col = -1;

int food_row;
int food_col;

int score = 0;

int current_direction = MOVE_UP;


int main()
{
    srand(time(NULL)); // to create a seed value for the pseudo random number generator

    printf("Day - 25 - Snake Game");

    set_border();

    init_snake();

    spawn_food();

    start_game();
}

void init_snake()
{

    int snake_head_row_start = 1; // start position
    int snake_head_row_end = GRID_HEIGTH - 2; // last position

    snake_head_row = snake_head_row_start + rand() % (snake_head_row_end - snake_head_row_start + 1);

    int snake_head_col_start = 1; // start position
    int snake_head_col_end = GRID_WIDTH - 2; // last position

    snake_head_col = snake_head_col_start + rand() % (snake_head_col_end - snake_head_col_start + 1);

    grid[snake_head_row][snake_head_col] = '@';

}

void spawn_food()
{

    int valid_spawn = 0;
    while(!valid_spawn)
    {
        int row_range_start = 1; // start position
        int row_range_end = GRID_HEIGTH - 2; // last position

        food_row = row_range_start + rand() % (row_range_end - row_range_start + 1);

        int col_range_start = 1; // start position
        int col_range_end = GRID_WIDTH - 2; // last position

        food_col = col_range_start + rand() % (col_range_end - col_range_start + 1);

        if(grid[food_row][food_col] == ' ')
        {
            valid_spawn = 1;
        }
    }

    grid[food_row][food_col] = '+';
}

void set_border()
{
    // draw the border
    for(int i = 0; i < GRID_HEIGTH; i++)
    {
        for(int j = 0; j < GRID_WIDTH; j++)
        {
            char char_to_set = '\0';
            if(i == 0 || i == GRID_HEIGTH - 1 || j == 0 || j == GRID_WIDTH - 1)
            {
                char_to_set = '#';
            }
            else
            {
                char_to_set = ' ';
            }

            grid[i][j] = char_to_set;
        }
    }
}

void set_direction(char choice)
{
    switch(choice)
        {
            case 'w':
                current_direction = MOVE_UP;
                break;
            case 'a':
                current_direction = MOVE_LEFT;
                break;
            case 's':
                current_direction = MOVE_DOWN;
                break;
            case 'd':
                current_direction = MOVE_RIGHT;
                break;
        }
}
int move_snake()
{
    int is_game_over = 0;
    
    // move
    switch(current_direction)
    {
        case MOVE_UP:

            if(snake_head_row - 1 <= 0) // check self collision in future
            {
                is_game_over = 1;
            }
            else
            {
                grid[snake_head_row][snake_head_col] = ' '; // clear previous step
                snake_head_row = snake_head_row - 1;
            }
            break;

        case MOVE_LEFT:

            if(snake_head_col - 1 <= 0)
            {
                is_game_over = 1;
            }
            else
            {
                grid[snake_head_row][snake_head_col] = ' '; // clear previous step
                snake_head_col = snake_head_col - 1;
            }
            break;

        case MOVE_DOWN:
            if(snake_head_row + 1 >= GRID_HEIGTH - 1)
            {
                is_game_over = 1;
            }
            else
            {
                grid[snake_head_row][snake_head_col] = ' '; // clear previous step
                snake_head_row = snake_head_row + 1;
            }
            break;

        case MOVE_RIGHT:
            if(snake_head_col + 1 >= GRID_WIDTH - 1)
            {
                is_game_over = 1;
            }
            else
            {
                grid[snake_head_row][snake_head_col] = ' '; // clear previous step
                snake_head_col = snake_head_col + 1;
            }
            break;
    }

    grid[snake_head_row][snake_head_col] = '@';

    if(is_food_pos(snake_head_row, snake_head_col))
    {
        score++;
        spawn_food();
    }

    return is_game_over;
}

int is_snake_pos(int row, int col)
{
    if(row == snake_head_row && col == snake_head_col)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int is_food_pos(int row, int col)
{
    if(row == food_row && col == food_col)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void start_game()
{
    char choice = '\0';

    while(choice != 'q' && choice != 'Q')
    {
        system("cls");

        if(kbhit())
        {
            choice = getch();
        }

        set_direction(choice);
        

        printf("Score: %d\n", score);

        for(int i = 0; i < GRID_HEIGTH; i++)
        {
            for(int j = 0; j < GRID_WIDTH; j++)
            {
                printf("%c ", grid[i][j]);
            }

            printf("\n");
        }

        int is_game_over = move_snake();

        if(is_game_over)
        {
            printf("Game Over!!!\n");
            break;
        }
        Sleep(1000);
        
    }
}


