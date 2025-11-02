#include<stdio.h>
#include<string.h>
int main()
{
     char strings[][100] = {"apple", "zebra", "cat", "ball", "Ant"};

     int arr_size = 5;

     for(int i = 0; i < arr_size; i++)
     {
          for(int j = i; j > 0; j--)
          {    
               int sorted_and_stop = 0;
               for(int k = 0; k < 100; k++)
               {
                    // if either of the two string ends are reached
                    if(strings[j][k] == '\0' && strings[j - 1][k] == '\0')
                    {
                         break;
                    }
                    // if the character of the first string is greater than the character of the second string,
                    // swap and proceed to compare forward
                    if(strings[j - 1][k] > strings[j][k])
                    {
                         char temp[100];
                         strcpy(temp, strings[j - 1]);
                         strcpy(strings[j - 1], strings[j]);
                         strcpy(strings[j], temp);
                         break;
                    }
                    else if(strings[j - 1][k] < strings[j][k])
                    {
                         sorted_and_stop = 1;
                         break;
                    }
               }

               if(sorted_and_stop)
               {
                    break;
               }
          }
     }

     for(int i = 0; i< arr_size; i++)
     {
          for(int j = i; j > 0; j--)
          {
               //returns 0, if both are equal. > 0, if the first string is greater than the second one. else, negative value (Lexicographically)
               if(strcmp(strings[j - 1], strings[j]) > 0) // if the result is positive
               {
                    char temp[100];
                    strcpy(temp, strings[j - 1]);
                    strcpy(strings[j - 1], strings[j]);
                    strcpy(strings[j], temp);
               }
               else{
                    break;
               }
          }
     }
     for(int i = 0; i < 5; i++)
     {
          printf("%s\n", strings[i]);
     }
}