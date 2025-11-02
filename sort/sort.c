#include<stdio.h>
void print_array(int* arr, int size);
void swap(int* a, int* b);
void bubble_sort(int*arr, int size);
void insertion_sort(int* arr, int size);
int main()
{
    printf("Day 12 of daily Coding! - insertion sorting\n");

    int arr[] = {5, 3, 6, 8, 9, 1, 0};
    
    print_array(arr, 7);
    //bubble_sort(arr, 7);
    insertion_sort(arr, 7);
    print_array(arr, 7);
}

void print_array(int* arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

void bubble_sort(int* arr, int size)
{
    // 5, 3, 6, 8, 9, 1, 0
    // 3, 5, 6
    // 3, 5, 6, 8
    // 3, 5, 6, 8, 9, 1
    // 3, 5, 6, 8, 1, 9, 0
    // 3, 5, 6, 8, 1, 0, 9
    //                8, 9
    //             6, 8, 9
    //          5, 6, 8, 9
    //       3, 5, 6, 8, 9
    //    1, 3, 5, 6, 8, 9
    // 0, 1, 3, 5, 6, 8, 9

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size - i - 1 ; j++)
        {
            if(arr[j] > arr[j+1])
            {
                swap(&arr[j], &arr[j+1]);
            }
        }
        print_array(arr, size);
    }
}

void insertion_sort(int* arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = i; j > 0; j--)
        {
            if(arr[j - 1] > arr[j])
            {
                swap(&arr[j], &arr[j - 1]);
            }
        }
    }
}

void swap(int* a, int* b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
    // Always remember, dereferencing means, getting the value in the address pointed by the address.
    // Assigning to a dereferenced variable means, assigning to the address pointed by the address.
}