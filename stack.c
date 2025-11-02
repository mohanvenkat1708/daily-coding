#include<stdio.h>

#define max_size 50

int stack[max_size];

int top = 0; // top

void push(int value); // add
void pop(); // remove
void peek(); // look up


// 4 - 4  
// 7 - 3 -> top
// 6 - 2 
// 8 - 1 
// 7 - 0 


// Data Structure - How we store the data?

// Arrays - continuous, homogenous data structure - accessed with indices.
// Stacks - Last In, First Out data structure
// Queues - First In, First Out

int main()
{
    
    printf("Day 5 - Daily Coding - Stack Example!!!\n");
    
    push(1);
    push(2);
    push(3);
    push(4);

    peek(); // 4
    pop(); // top - 3
    push(5); // top - 5
    pop(); // top - 3
    peek(); // top - 3
}

void push(int value)
{
    if(top == max_size)
    {
        printf("Cannot push! Stack Overflow!\n");
        return;
    }

    stack[top] = value;
    printf("Value inserted: %d!\n", stack[top]);

    top++;
}

void pop()
{
    if(top < 0)
    {
        printf("Cannot pop further! Stack Underflow!\n");
        return;
    }

    int deleting_value = stack[top - 1];
    top--;

    printf("Value deleted: %d!\n", deleting_value);
}

void peek()
{
    if(top <= 0)
    {
        printf("The stack is empty!\n");
        return;
    }

    printf("Top value: %d\n",stack[top - 1]);
}

