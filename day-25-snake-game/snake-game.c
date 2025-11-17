#include<stdio.h>
#include<stdlib.h> // for rand and srand
#include<time.h> // for time
#include<conio.h> // for _kbhit
#include<windows.h> // for Sleep

#define GRID_WIDTH 10
#define GRID_HEIGHT 10

#define MOVE_UP 0
#define MOVE_LEFT 1
#define MOVE_DOWN 2
#define MOVE_RIGHT 3

typedef struct sect
{
    int row;
    int col;
    struct sect* next;
}sect;

sect* head;

void set_border();
void init_snake();
void start_game();
void set_direction(char choice);
int move_snake();
void spawn_food();
int is_snake_pos(int row, int col);
int is_food_pos(int row, int col);
sect* create_sect(int row, int col);
void draw_grid();
void add_head(int row, int col);
void remove_tail();
void set_snake();
int is_wall_hit(int row, int col);

char grid[GRID_HEIGHT][GRID_WIDTH];

int food_row;
int food_col;

int score = 0;

int current_direction = MOVE_UP;

int row_range_start = 1; // start position
int row_range_end = GRID_HEIGHT - 2; // last position

int col_range_start = 1; // start position
int col_range_end = GRID_WIDTH - 2; // last position

void printc(char ch, int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    printf("%c ", ch);
}

int main()
{
    // console - black background & white text
    system("color 07");

    srand(time(NULL)); // to create a seed value for the pseudo random number generator

    printf("Day - 25 - Snake Game");

    set_border();

    init_snake();

    spawn_food();

    start_game();
}

void init_snake()
{

    int rand_row = row_range_start + rand() % (row_range_end - row_range_start + 1);

    int rand_col = col_range_start + rand() % (col_range_end - col_range_start + 1);

    head = create_sect(rand_row, rand_col);

}

sect* create_sect(int row, int col)
{
    sect* part = (sect*)malloc(sizeof(sect));

    part->row = row;
    part->col = col;

    part->next = NULL;

    return part;
}

void spawn_food()
{

    int valid_spawn = 0;
    while(!valid_spawn)
    {

        food_row = row_range_start + rand() % (row_range_end - row_range_start + 1);

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
    for(int i = 0; i < GRID_HEIGHT; i++)
    {
        for(int j = 0; j < GRID_WIDTH; j++)
        {
            char char_to_set = '\0';
            if(i == 0 || i == GRID_HEIGHT - 1 || j == 0 || j == GRID_WIDTH - 1)
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

    int new_head_row = head->row;
    int new_head_col = head->col;

    // move
    switch(current_direction)
    {
        case MOVE_UP:
            new_head_row--;
            break;

        case MOVE_LEFT:
            new_head_col--;
            break;

        case MOVE_DOWN:
            new_head_row++;
            break;

        case MOVE_RIGHT:
            new_head_col++;
            break;
    }

    // check if wall / snake is hit / bit :)
    if(is_wall_hit(new_head_row, new_head_col) || is_snake_pos(new_head_row, new_head_col))
    {
        return 1; // game over
    }
    

    if(is_food_pos(new_head_row, new_head_col))
    {
        score++;
        spawn_food();

        add_head(new_head_row, new_head_col);

    }
    else
    {
        // just move forward
        add_head(new_head_row, new_head_col);
        remove_tail();
    }
    
    return 0;
}

int is_wall_hit(int row, int col)
{
    if(row <= 0 || row >= GRID_HEIGHT - 1 || col <= 0 || col >= GRID_WIDTH - 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void add_head(int row, int col)
{
    sect* new_head = create_sect(row, col);
    new_head->next = head;
    head = new_head;
}

void remove_tail()
{

    // empty or size 1 snake

    if(head == NULL || head->next == NULL)
    {
        return;
    }

    // size - 2 or more

    sect* section = head;
    while(section->next->next != NULL) // get the sect before the last one
    {
        section = section->next; 
    }

    sect * tail = section->next;

    // detaching the tail from the linked list
    section->next = NULL;

    // resetting the tail's trace
    grid[tail->row][tail->col] = ' ';
    free(tail);
}

 void set_snake()
{
    // set head as '@'
    grid[head->row][head->col] = '@';

    if(head->next != NULL)
    {
        sect* section = head->next;
        while(section != NULL)
        {
            grid[section->row][section->col] = '*';
            section = section->next;
        }
    }
}

int is_snake_pos(int row, int col)
{
    sect* section = head;

    // checking the whole snake body (except the tail)
    while(section->next != NULL)
    {
        if(row == section->row && col == section-> col)
        {
            return 1;
        }
        section = section->next;
    }
    
    return 0;
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

void draw_grid()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int i = 0; i < GRID_HEIGHT; i++)
    {
        for(int j = 0; j < GRID_WIDTH; j++)
        {
            char ch = grid[i][j];
            int color;
            switch(ch)
            {
                case '#':
                color = 14; // yellow
                break;

                case '@':
                color = 10; // bright green
                break;

                case '*':
                color = 2; // dark green
                break;

                case '+':
                color = 12; // bright red
                break;

                case ' ':
                color = 8; // gray empty space
                break;
            }
            printc(ch, color);
        }
        printf("\n");
    }

    SetConsoleTextAttribute(h, 7); // reset to normal gray
}
void start_game()
{
    char choice = '\0';

    while(choice != 'q' && choice != 'Q')
    {
        system("cls");

        // black background and white text
        system("color 0F");

        if(kbhit())
        {
            choice = getch();
            set_direction(choice);
        }

        printf("Score: %d\n", score);

        int is_game_over = move_snake();

        set_snake();

        draw_grid();

        if(is_game_over)
        {
            printf("Game Over!!!\n");
            break;
        }

        Sleep(1000);
        
    }
}


