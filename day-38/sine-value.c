#include<stdio.h>
#include<math.h>

int main()
{
    int i = 0;
    float angle = 0;

    while(i < 100)
    {
        float value = sin(angle);
        
        printf("sine of the angle %f radian: %f\n",angle, value);
        angle += 0.1;
        i++;
    }
}