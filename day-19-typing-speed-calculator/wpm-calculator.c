#include<stdio.h>
#include<string.h>
#include<time.h>
#include<conio.h>

#define INTERVAL_SECS 20
#define CHAR_LIMIT 300

// typing speed calculator - calculate wpm
// Things to know:
// How to track time and enforce time limit - use time.h - time, difftime
// How to get the input from console without waiting for the user to press enter - use _kbhit and getch (handle pressing return)
// Note:
// For the user to know what they are printing, we have to print each character in the terminal as they type
// For correcting the typing, we have to allow backspace

int main()
{
    printf("Day - 19 - wpm calculator\n");

    char typed_words[CHAR_LIMIT] = {0}; // initialize the array to 0
    char reference_words[CHAR_LIMIT] = {0};

    time_t start_time, end_time;

    double elasped_time;

    
    
    int char_pos = 0;

    FILE *fptr = fopen("./words.txt", "r");
    int ref_pos = 0;
    char ch;
    while((ch = fgetc(fptr)) != EOF && ref_pos < CHAR_LIMIT - 1)
    {
        if(ch == '\n') // skip new line
        {
            ch = ' ';
        }

        if(ch == ' ' && reference_words[ref_pos] == ' ' && ref_pos > 0) // skip dulicate spaces
        {
            continue;
        }

        reference_words[ref_pos] = ch;
        ref_pos++;
    }

    reference_words[ref_pos] = '\0';

    // close the file pointer
    fclose(fptr);

    time(&start_time);
    // use do while, when you first want to initialize the value for checking before checking
    do{
        if(_kbhit())
        {
            char c = getch();
            if(c == '\r' || c == '\n')
            {
                continue;
            }
            else if(c == '\b')
            {
                if(char_pos > 0)
                {
                    char_pos--;
                    printf("\b \b"); // move the cursor back, replace the existing character with space and then move the cursor back again
                }
                
                continue;
            }
            typed_words[char_pos] = c;
            printf("%c", typed_words[char_pos]);
            char_pos++;
        }
        
        time(&end_time);
        elasped_time = difftime(end_time, start_time);
        //printf("\nelasped_time: %f\n", elasped_time);
        
    }
    while(elasped_time < INTERVAL_SECS && char_pos < CHAR_LIMIT - 1);
    
    if(elasped_time >= INTERVAL_SECS)
    {
        printf("\ntime over!!! Well done !!!\n");
    }
    else if (char_pos >= CHAR_LIMIT)
    {
        printf("\ncharacter typing limit reached\n");
    }
    
    typed_words[char_pos] = '\0';

    printf("The words you typed:\n%s\n", typed_words);

    int word_count = 0;

    int len_typed = strlen(typed_words);
    for(int i = 0; i < len_typed; i++)
    {
        if(typed_words[i] != reference_words[i])
        {
            break;
        }
        if(typed_words[i] == ' ')
        {
            word_count++;
        }

        
    }
    // last typed word without space
    if(len_typed > 0 && typed_words[len_typed - 1] != ' ' && typed_words[len_typed - 1] == reference_words[len_typed - 1])
    {
        word_count++;
    }
    
    printf("The correct word count: %d\n", word_count);
}