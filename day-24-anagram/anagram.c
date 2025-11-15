#include<stdio.h>
#include<string.h>

void sort(char* str, int len);

void main()
{
    // silent - listen
    // act - cat
    // race - care
    // night - thing
    // secure - rescue
    // share - hear
    // below - elbow
    // dusty - study

    printf("Day - 24 - Anagram ");

    char str1[50], str2[50];

    printf("string 1:");
    scanf("%s", str1);
    printf("string 2:");
    scanf("%s", str2);

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if(len1 != len2)
    {
        printf("Not anagram!!!\n");
        return;
    }

    // sort and compare

    sort(str1, len1);
    sort(str2, len2);

    for(int i = 0; i < len1; i++)
    {
        if(str1[i] != str2[i])
        {
            printf("Not Anagram!!!\n");
            return;
        }
    }
    printf("Anagram!!!\n");


    
    // array approach

    // a b c d e f g h i j k l m n o p q r s t u v w x y z
    // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

    int alph_arr1[26] = {0};
    int alph_arr2[26] = {0};

    for(int i = 0; i < len1; i++)
    {
        alph_arr1[str1[i] - 97]++; // a - 97
        alph_arr2[str2[i] - 97]++;
    }

    for(int i = 0; i < 26; i++)
    {
        if(alph_arr1[i] != alph_arr2[i])
        {
            printf("Not Anagram!!!");
            return;
        }
    }

    printf("Anagram!!!");
}

void sort(char* str, int len)
{
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len - i - 1; j++)
        {
            if(str[j] > str[j + 1])
            {
                // swap
                char temp = str[j];
                str[j] = str[j+1];
                str[j+1] = temp;
            }
            
        }
    }
}
