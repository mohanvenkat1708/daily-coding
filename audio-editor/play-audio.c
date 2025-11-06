# include<stdio.h>
# include<windows.h>
#include<conio.h> // for _kbhit and getch
# include<mmsystem.h> // for the PlaySound

// when compiling, tell the linker with "-l" flag to include the library:
// gcc play-audio.c -o play-audio.exe -lwinmm
void main()
{
    printf("Day - 18 - Daily Coding - Play audio in C\n");
    
    char* music_path = "./happy.wav";

    printf("playing the sond in the path: %s", music_path);


    // SND_FILENAME - means, we are giving the FileNameInfo
    // SND_SYNC - to play the sound synchronously

    // The NULL can be the handle for the instance of the application that contains the sound resource to be played.
    // PlaySound(music_path, NULL, SND_FILENAME | SND_SYNC);
    // printf("hello!");
    // SND_SYNC - tells the program to wait till the music ends

    
    printf("Audio Player Control 🎶\ns : start\\restart\nx : stop\nq : quit\n");

    char command;
    while(1)
    {
        if(_kbhit()) // check for a keyboard hit
        {
            command = getch();

            if(command == 's' || command == 'S')
            {
                printf("Music Starting / Restarting \n");

                // ensure the music starts from the beginning
                PlaySound(NULL, NULL, 0);

                int success  = PlaySound(music_path, NULL, SND_FILENAME | SND_ASYNC);

                if(success)
                {
                    printf("Sound played asynchronously.\n");
                }
                else{
                    printf("could not play audio. please check the audio or format\n");
                }
            }

            else if(command == 'x' || command == 'X')
            {

                // stopping all the sound initiated by the application
                PlaySound(NULL, NULL, 0);

                printf("Music Stopped \n");
            }
            else if(command == 'q' || command == 'Q')
            {

                // stopping all the sound before quitting
                PlaySound(NULL, NULL, 0);

                printf("Application is quit!\n");
                break;
            }

            // PlaySound doesn't include support to play forward and backward. For that, we can use other advanced libraries like SDL_mixer
        }
    }

    
    return;
}