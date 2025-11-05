#include<stdio.h>
#include<string.h>
#include<unistd.h> // for ftruncate
#include<fcntl.h> // fileno
int main()
{
    printf("Day 17 of Daily Coding - Encrypt and Decrypt files using XOR\n");

    FILE* file = fopen("./files.txt", "r+");

    if(file == NULL)
    {
        printf("file not present!");
        return 1;
    }
    char file_buffer[1000] = "";
    char line[100];

    int key;
    printf("Give key: ");
    scanf("%d", &key);

    while(fgets(line, 100, file) != NULL)
    {
        strcat(file_buffer, line);
    }

    //printf("%s", file_buffer);

    for(int i = 0; i < strlen(file_buffer); i++)
    {
        file_buffer[i] = file_buffer[i] ^ key;
    }

    // reset the file pointer to he beginning of the file
    fseek(file, 0, SEEK_SET);

    fprintf(file, "%s", file_buffer);

    ftruncate(fileno(file), strlen(file_buffer));

    printf("File Processed and written successfully!");

    fclose(file);
}