#include <stdio.h>
#include <math.h>     // Required for sin()
#include <windows.h>  // Required for Sleep()

int main() {
    float angle = 0.0;
    
    // 1. Set Color to Cyan (Sci-Fi look) and Hide Cursor
    printf("\033[1;36m\033[?25l"); 

    while (1) {
        // 2. The Math: sin() returns -1 to +1. 
        // We multiply by 10 to make it bigger, and add 20 so it's never negative.
        // Result: A number that smoothly oscillates between 10 and 30.
        int length = 20 + (int)(sin(angle) * 15);

        // 3. Print the "Bar"
        for (int i = 0; i < length; i++) {
            printf("#");
        }
        printf("\n"); // Move to next line

        // 4. Move the wave forward slightly
        angle += 0.1; 

        // 5. Control the speed
        Sleep(20); 
    }

    return 0;
}