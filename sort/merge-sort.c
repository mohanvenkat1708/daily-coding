
#include <stdio.h>
void merge_sort(int* arr, int start, int end);
void print_arr(int* arr, int size);
void merge(int* arr, int first_start, int first_end, int sec_start, int sec_end);
int main() {
    
    int arr[] = { 1, 2, 7, 0, 4, 8 };
    int size = 6;
    merge_sort(arr, 0, size - 1);
    print_arr(arr, size);
    
    return 0;
}

void merge_sort(int* arr, int start, int end)
{
    if(start >= end)
    {
        return;
    }
    else
    {
        int mid = start + (end - start)/2;
        merge_sort(arr, start, mid); 

        merge_sort(arr, mid + 1, end);
        
        merge(arr, start, mid, mid+1, end);
    }
}
void print_arr(int* arr, int size)
{
    for(int i = 0; i< size; i++)
    {
        printf("%d\n", arr[i]);
    }
}

void merge(int* arr, int first_start, int first_end, int sec_start, int sec_end)
{
    int temp[sec_end - first_start + 1];
    int first = first_start;
    int sec = sec_start;
    int i = 0; // index
    while(first <= first_end && sec <= sec_end)
    {
        if(arr[first] <= arr[sec])
        {
            temp[i] = arr[first];
            first++;
        }
        else
        {
            temp[i] = arr[sec];
            sec++;
        }
        i++;
    }
    
    while(first <= first_end)
    {
        temp[i] = arr[first];
        first++;
        i++;
    }

    while(sec <= sec_end)
    {
        temp[i] = arr[sec];
        sec++;
        i++;
    }
    
    // write temp to arr
    int replace_index = first_start;
    for(int i = 0; i < sec_end - first_start + 1; i++)
    {
        arr[replace_index] = temp[i];
        replace_index++;
    }
    
    
}
