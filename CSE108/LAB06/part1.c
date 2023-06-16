#include <stdio.h>

#define SIZE 50
#define sentinel -100

//scan from user and assing it to the array
void    read_input(int arr[], int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        printf("Enter a number: ");
        scanf("%d", &arr[i]);
        if (arr[i] == sentinel)
            break;
        i++;
    }
}

//label the values and assing it to the array
void label(char label_arr[], int arr[], int size)
{
    int i;
    char ch;

    i = 0;
    while (i < size && arr[i] != sentinel)
    {
        if (arr[i] % 2 == 0)
            ch = 'e';
        else
            ch = 'o';
        label_arr[i] = ch;
        i++;
    }
}

void    print_res(int arr[], char label_arr[], int size)
{
    int i;

    i = 0;
    while (i < size && arr[i] != sentinel)
    {
        printf("%d %c\n", arr[i], label_arr[i]);
        i++;
    }
}

int main()
{
    int arr[SIZE];
    char label_arr[SIZE];

    read_input(arr, SIZE);
    label(label_arr, arr, SIZE);
    print_res(arr, label_arr, SIZE);
}