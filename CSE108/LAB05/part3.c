#include <stdio.h>

int converter(int nbr, int base)
{
    int res;
    int tmp;

    res = 0;
    tmp = 1;
    while (nbr != 0)
    {
        res += (nbr % 10) * tmp;
        tmp *= base;
        nbr /= 10;
    }
    return (res);
}

void print_nbrs()
{
    int nbr;

    printf("Enter a number: ");
    scanf("%d", &nbr);
    printf("Decimal equivalent: %d\n", converter(nbr, 10));
    printf("Binary equivalent: %d\n", converter(nbr, 2));
    printf("Octal equivalent: %d\n", converter(nbr, 8));
    printf("Hexadecimal equivalent: %d\n", converter(nbr, 16));
}

void    menu()
{
    int op;

    op = 1;
    while (op == 1)
    {
        printf("1) Convert a number to decimal, binary, octal and hexadecimal\n");
        printf("2) Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &op);
        
        if (op == 1)
        {
            print_nbrs();
        }
        else if (op == 2)
            return ;
    }
}

int main()
{
    menu();
    return (0);
}