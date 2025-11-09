#include<stdio.h>
#define LIST_SIZE 15

void bubble_sort();
int linear_search(int val);
int binary_search(int val);

int arr[15] = {1, 8, 0, 34, 67, 45, 11, 13, 89, 12, 20, 43, 52, 91, 72};
int main()
{
    
    printf("Daily Coding - Day 20 - Binary Search\n");

    int value = 60;
    bubble_sort();
    int result = binary_search(value);
    if(result != -1)
    {
        printf("Element found\n", result);
    }
    else
    {
        printf("Element not found!!!\n");
    }

    return 0;
}

void bubble_sort()
{
    int temp;
    for(int i = 0; i < LIST_SIZE; i++)
    {
        for(int j = i; j < LIST_SIZE - 1; j++)
        {
            if(arr[j] > arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int linear_search(int val)
{
    for(int i = 0; i < 15; i++)
    {
        if(arr[i] == val)
        {
            return 1;
        }
    }
    return 0;
}

int binary_search(int val)
{
    int mid;

    int start = 0;
    int end = LIST_SIZE - 1;

    while(start <= end)
    {
        mid = start + (end - start) / 2;

        if(arr[mid] == val)
        {
            return mid;
        }
        else if(arr[mid] > val)
        {
            end = mid - 1;
        }
        else if(arr[mid] < val)
        {
            start = mid + 1;
        }
    }
    return -1;
}