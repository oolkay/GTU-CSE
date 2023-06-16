#include <stdio.h>

void    foo_min_max(int arr[], int n)
{
    int max = arr[0];
    int min = arr[0];
    int i = 0;
    while (i < n)
    {
        if (arr[i] < min)
            min = arr[i];
        if (arr[i] > max)
            max = arr[i];
        i++;
    }
    printf("Min: %d Max: %d", min, max);
}

int main()
{
    int arr[100];
    
    int n;
    printf("Enter size: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter an integer: ");
        scanf("%d", &arr[i]);
    }
    foo_min_max(arr, n);

    return (0);
}