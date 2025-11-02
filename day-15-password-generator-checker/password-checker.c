#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void generate_password();
int password_score(char* password, int size);
char rand_upper();
char rand_lower();
char rand_digit();
char rand_special();

int main()
{
    srand(time(0));
    printf("Day - 15 - Daily Coding - Password Generator & Checker\n");

    char password[25];
    int choice;
    do
    {
        printf("What do you want to do?\t(1 - generate password\t2 - check password strength\t0 - quit)\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                generate_password();
                break;
            case 2:
                printf("Give the password:\n");
                scanf("%24s", password);
                int strength = password_score(password, strlen(password));
                printf("The password strength: %d\n", strength);
                break;
            default:
                break;
        }
    } while (choice != 0);
    
}

void generate_password()
{
    char pass[25];
    int pass_len;
    printf("Give the password length:\n");
    scanf("%d", &pass_len);

    for(int i = 0; i < pass_len; i++)
    {
        int char_category =  rand() % 4; // upper - 0, lower - 1, digit - 2, special - 3

        switch(char_category)
        {
            case 0:
                pass[i] = rand_upper();
                break;
            case 1:
                pass[i] = rand_lower();
                break;
            case 2:
                pass[i] = rand_digit();
                break;
            case 3:
                pass[i] = rand_special();
                break;
                
        }
    }
    pass[pass_len] = '\0';
    printf("Generate Password: %s\n", pass);
    printf("Generated Password Strength: %d\n", password_score(pass, pass_len));
}

int password_score(char* password, int size)
{
    /*
    rules:

    length >= 12  : +3 points
    length >= 8   : +2 points
    has uppercase : +2 points
    has lowercase : +1 points
    has digit     : +2 points
    has special   : +2 points
    
    max: 10 points
    */

    int strength = 0;
    
    // length
    if(size >= 12)
    {
        strength += 3;
    }
    else if( size >= 8)
    {
        strength += 2;
    }
    else if( size >= 6)
    {
        strength += 1;
    }

    int upper_count = 0;
    int lower_count = 0;
    int special_count = 0;
    int digit_count = 0;
    for(int i = 0; i < size; i++)
    {
        char c = password[i];
        // uppercase
        if(c >= 'A' && password[i] <= 'Z')
        {
            upper_count++;
        }

        // smallercase
        if(c >= 'a' && c <= 'z')
        {
            lower_count++;
        }

        // digits
        if(c >= '0' && c <= '9')
        {
            digit_count++;
        }

        // special chars
        if((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126))
        {
            special_count++;
        }
    }

    if(upper_count > 0)
    {
        strength += 2;
    }
    
    if(lower_count > 0)
    {
        strength += 1;
    }

    if(digit_count > 0)
    {
        strength += 2;
    }

    if(special_count > 0)
    {
        strength += 2;
    }

    return strength > 10 ? 10 : strength;
}

char rand_upper()
{
    return (rand() % 26) + 'A';
}

char rand_lower()
{
    return (rand() % 26) + 'a';
}

char rand_digit()
{
    return (rand() % 10) + '0';
}

char rand_special()
{
    // since, there are 4 different stretches, we can choose from them randomly
    int choice = rand() % 4;

    char rand_char;
    switch(choice)
    {
        case 0:
            rand_char = (rand() % 14) + '!';
            break;
        case 1:
            rand_char = (rand() % 7) + ':';
            break;
        case 2:
            rand_char = (rand() % 6) + '[';
            break;
        case 3:
            rand_char = (rand() % 4) + '{';
            break;
    }
}