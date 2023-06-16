#include <stdio.h>

//FINDING DIGIT COUNT OF NBR
int find_digit(int nbr)
{
    int digit;

    digit = 0;
    while (nbr != 0)
    {
        digit++;
        nbr /= 10;
    }
    return (digit);
}

//REVERSING THE NUMBER
int rev_nbr(int nbr)
{
    int rev_nbr;

    rev_nbr = 0;
    while (nbr != 0)
    {
        rev_nbr = rev_nbr * 10 + (nbr % 10);
        nbr /= 10;
    }
    return (rev_nbr);
}

int main()
{
    int nbr;
    int digit;
    int res;

    printf("Enter a number (3, 4, or 5): ");
    scanf("%d", &nbr);
    digit = find_digit(nbr);
    while (digit > 5 || digit < 3)
    {
        printf("INVALID INPUT, ENTER AGAIN\n");
        printf("Enter a number (3, 4, or 5): ");
        scanf("%d", &nbr);
        digit = find_digit(nbr);
    }
    res = rev_nbr(nbr);
    printf("Reversed number: %d\n", res);
    return (0);
}