#include <stdio.h>

int main()
{
    int nbr;

    printf("Please enter an integer between 1 and 100 : ");
    scanf("%d", &nbr);
    
    if (nbr % 3 == 0 && (nbr >= 1 && nbr <= 100))
        printf("Fizz");
    if (nbr <= 50 && nbr >= 5)
        printf("Buzz");
    printf("\n");
}
