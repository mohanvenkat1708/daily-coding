# include<stdio.h>
# include<windows.h>
# include<conio.h>

#define SA_FREQ 262
#define RE_FREQ 294
#define GA_FREQ 330
#define MA_FREQ 349
#define PA_FREQ 392
#define DHA_FREQ 440
#define NI_FREQ 494
#define SAA_FREQ 523

#define SILENCE_DURATION 100

#define NOTE_DURATION 1000

void main()
{
    printf("Day - 18 - Daily Coding - Play audio in C\n");
    // DWORD - a data type of 32 bit unsigned int.
    // it is of size 32 bits regardless of the system 16/32 bit

    // syntax: Beep(x, y); 
    // x - frequency
    // y - time in ms
    // Eg: Beep(750, 800);
    //Beep(750, 20000);
    
    Beep(SA_FREQ, NOTE_DURATION);
    Sleep(SILENCE_DURATION);
    Beep(RE_FREQ, NOTE_DURATION);
    Sleep(SILENCE_DURATION);
    Beep(GA_FREQ, NOTE_DURATION);
    Sleep(SILENCE_DURATION);
    Beep(MA_FREQ, NOTE_DURATION);
    Sleep(SILENCE_DURATION);
    Beep(PA_FREQ, NOTE_DURATION);
    Sleep(SILENCE_DURATION);
    Beep(DHA_FREQ, NOTE_DURATION);
    Sleep(SILENCE_DURATION);
    Beep(NI_FREQ, NOTE_DURATION);
    Sleep(SILENCE_DURATION);
    Beep(SAA_FREQ, NOTE_DURATION);
    Sleep(SILENCE_DURATION);



    //Beep(700, 1000);
    return;
}