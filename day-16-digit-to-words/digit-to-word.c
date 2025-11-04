#include<stdio.h>
#include<string.h>
void digit_to_word(int digit);

void get_word_under_thousand(int digit);
void get_word_under_hundred(int digit);


char numbers[20][15] = { "zero ", "one ", "two ", "three ", "four ", 
                      "five ", "six ", "seven ", "eight ", "nine ", 
                      "ten ", "eleven ", "twelve ", "thirteen ", "fourteen ", 
                      "fifteen ", "sixteen ", "seventeen ", "eighteen ", "nineteen " };
char word[256];
char word_under_thous[128]; // 12,123,456
int main()
{
    int digit;
    printf("Number: ");
    scanf("%d", &digit);

    if(digit == 0)
    {
        printf("%s",numbers[0]);
        return 0;
    }
    digit_to_word(digit);

    printf("the word: %s", word);
}

void digit_to_word(int digit)
{
    char limits[5][10] = {"", "thousand ", "million ", "billion ", "trillion " };

    int index = 0;
    char temp_word[256];

    strcpy(word, "");
    while(digit > 0) //12,346,789  seven eighty nine - three hundred fourty six thousand,
    {
        get_word_under_thousand(digit % 1000);
        strcpy(temp_word, word);

        // to reverse the word
        snprintf(word, sizeof(word), "%s%s%s", word_under_thous, limits[index], temp_word);
        
        digit /= 1000;
        index++;
    }
    
}

void get_word_under_thousand(int digit)
{
    strcpy(word_under_thous , "");
    if(digit/100 != 0) //456
    {
        strcat(word_under_thous, numbers[digit/100]);
        strcat(word_under_thous, " hundred ");
    }
    
    get_word_under_hundred(digit%100);

}

void get_word_under_hundred(int digit)
{
    if(digit == 0)
    {
        return;
    }

    char tens[8][15] = {"twenty ", "thirty ", "fourty ", "fifty ", "sixty ", "seventy ", "eighty ", "ninety "};
    if(digit < 20)
    {
        strcat(word_under_thous, numbers[digit]);
    }
    else if(digit >= 20)
    {
        strcat(word_under_thous, tens[digit/10 - 2]);
        if(digit % 10 > 0)
        {
            strcat(word_under_thous, numbers[digit%10]);
        }
        
    }
}
