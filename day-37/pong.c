#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define WIDTH 40
#define HEIGHT 20

int grid[HEIGHT][WIDTH];

int player_pos = HEIGHT / 2;
int opponent_pos = HEIGHT / 2;

int ball_x = 5;
int ball_y = 5;

int ball_direction_x = 1;
int ball_direction_y = 1;

int player_score = 0;
int opponent_score = 0;

void draw()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

void generate_ball_random()
{
    int margin_limit = 3;
    ball_x = margin_limit + (rand() % (WIDTH - margin_limit - 1));
    ball_y = margin_limit + (rand() % (HEIGHT - margin_limit - 1));
}

void update()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            grid[i][j] = ' ';
        }
    }

    // draw ceiling and floor
    for (int i = 0; i < WIDTH; i++)
    {
        grid[0][i] = '-';
        grid[HEIGHT - 1][i] = '-';
    }

    // drawing paddles
    for (int i = player_pos; i < player_pos + 4; i++)
    {
        grid[i][0] = '|';
    }

    for (int i = opponent_pos; i < opponent_pos + 4; i++)
    {
        grid[i][WIDTH - 1] = '|';
    }

    // ball
    grid[ball_y][ball_x] = 'O';

}

void get_input_and_act()
{

    char choice = '\0';

    if (kbhit())
    {
        choice = getch();

        switch (choice)
        {
        case 'w':

            if (player_pos > 0)
            {
                player_pos--;
            }
            break;
        case 's':
            if (player_pos + 3 < HEIGHT - 1)
            {
                player_pos++;
            }
            break;
        }

    }
}

void move_ball()
{

    int new_ball_x = ball_x + ball_direction_x;
    int new_ball_y = ball_y + ball_direction_y;


    if (new_ball_x != 0 && new_ball_x != WIDTH - 1)
    {
        ball_x = new_ball_x;
    }
    else
    {
        if (grid[new_ball_y][new_ball_x] == ' ')
        {
            // update score

            if (new_ball_x == 0)
            {
                opponent_score++;
            }
            else if (new_ball_x == WIDTH - 1)
            {
                player_score++;
            }

            generate_ball_random();
        }
        else if (grid[new_ball_y][new_ball_x] == '|')
        {
            // reverse the direction and move the ball
            ball_direction_x *= -1;

            ball_x += ball_direction_x;
            Beep(1000, 500);
        }
    }

    if (new_ball_y != 0 && new_ball_y != HEIGHT - 1)
    {
        ball_y = new_ball_y;
    }
    else
    {
        ball_direction_y *= -1;
        ball_y += ball_direction_y;
    }

}

void move_opponent_paddle()
{
    if(ball_direction_x > 0)
    {
        if(ball_direction_y < 0 && opponent_pos > 0)
        {
            opponent_pos--;
        }
        else if(ball_direction_y > 0 && opponent_pos < HEIGHT - 4)
        {
            opponent_pos++;
        }
    }
}

int main()
{
    printf("\033[?25l");

    // random direction
    ball_direction_x = rand() % 2 ? 1 : -1;
    ball_direction_y = rand() % 2 ? 1 : -1;

    generate_ball_random();
    update();
    
    while (1)
    {
        printf("\033[H");
        printf("Day 37 - Pong Game in C\n");

        draw();
        printf("player score: %d opponent score: %d\n", player_score, opponent_score);
        move_ball();
        get_input_and_act();
        move_opponent_paddle();

        update();

        Sleep(50);
    }
}