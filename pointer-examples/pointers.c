#include<stdio.h>
#include<stdlib.h>

void pointer_demo();
void swap(int* a, int* b);
void pointer_arithmetic_demo();
void dynamic_allocation_demo();

int main()
{
    printf("Day 7 - Daily Coding - Pointers\n");

    // 1. pointer example
    // pointer_demo();
    
    //2. pass by reference
    /*
    int a = 10;
    int b = 20;

    printf("before swapping\na: %d\tb: %d\n", a, b);
    swap(&a, &b);
    printf("after swapping\na: %d\tb: %d\n", a, b);

    */

    // 3. pointer arithmetic demo
    // pointer_arithmetic_demo();

    // 4. dynamic allocation demo
    dynamic_allocation_demo();

    return 0;
}

void pointer_demo()
{
    int val = 42;
    int* p_val = &val;

    printf("val: %d\n", val); // 42
    printf("address of val: %p\n", &val); // address of val
    printf("content of p_val: %p\n", p_val); // address of val
    printf("dereferencing p_val %d\n", *p_val); // 42
    printf("address of p_val: %p\n", &p_val); // address of p_val

    // modifying the variable, via the pointer
    *p_val = 100;
    printf("val value after changing via p_val: %d\n", val); // val will be 100
}

void swap(int* p_a, int* p_b)
{
    int temp;

    temp = *p_a;
    *p_a = *p_b;
    *p_b = temp;

}

void pointer_arithmetic_demo()
{
    int array[] = {10, 20, 30, 40, 50};

    int* p_array = array;

    printf("first value of array: %d\n", array[0]);

    printf("value in p_array %d\n", *p_array); // will also be the same value


    printf("value in the p_array: %p\n", p_array);

    p_array = p_array + 1;
    // p_array++; // we expect the address value to be incremented by 1. But, it will be incremented by 4.
    printf("value in the p_array (after incrementing): %p\n", p_array);
    printf("value dereferenced by the incremented p_array: %d\n", *p_array);

}

void dynamic_allocation_demo()
{
    int array_size = 5;
    // int array[5];
    // malloc(20);
    int* array = (int*) malloc(array_size * sizeof(int));

    // using the pointer like an array

    for(int i = 0; i < array_size; i++)
    {
        // here pointer arithmetic is happening here
        *(array + i) = i * 10; // simply to change the value
    }

    for(int i = 0; i < array_size; i++)
    {
        printf("value at %d: %d\n", i, array[i]);
    }

    // here, &array will be on the stack. but, the allocated memory in the address contained in array will be on the heap
    printf("address of array size: %p\naddress of the array pointer: %p\n", &array_size, array);

    // always remember to free the memory on the heap. Because, unlike stack memory, they are not freed with function calls
    free(array);
}
