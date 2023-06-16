#include <stdio.h>

int main()
{
    int nbr1;
    int nbr2;
    int nbr3;
    int med;

    printf("Please enter 3 integers: ");
    scanf("%d %d %d", &nbr1, &nbr2, &nbr3);
    
    if (nbr1 > nbr2)
    {
        if (nbr2 > nbr3)
            med = nbr2;
        else if (nbr3 > nbr2)
        {
            if (nbr3 > nbr1)
                med = nbr1;
            else
                med = nbr3;
        }
    }
    else if (nbr2 > nbr1)
    {
        if (nbr1 > nbr3)
            med = nbr1;
        else if (nbr3 > nbr1)
        {
            if (nbr3 > nbr2)
                med = nbr2;
            else
                med = nbr3;
        }
    }
    printf("Median Number: %d\n", med);
}