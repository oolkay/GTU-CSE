#include <stdio.h>

int main()
{
    int nbr1;
    int nbr2;
    int tmp;
    int res;
    char op;

    tmp = 0;
    printf("Enter the operation (+,-,/,*): ");
    scanf("%c", &op);
    printf("Enter two numbers: ");
    scanf("%d %d", &nbr1, &nbr2);
    printf("Result: ");
    scanf("%d", &res);
    switch(op)
    {
        case '+':
            tmp = nbr1 + nbr2;
            if (res != tmp)
                printf("Wrong Answer Try Again\n");
            break;

        case '-':
            tmp = nbr1 - nbr2;
            if (res != tmp)
                printf("Wrong Answer Try Again\n");
            break;

        case '*':
            tmp = nbr1 * nbr2;
            if (res != tmp)
                printf("Wrong Answer Try Again\n");
            break;

        case '/':
            tmp = nbr1 / nbr2;
            if (res != tmp)
                printf("Wrong Answer Try Again\n");
            break;
    }
    if (tmp == res)
        printf("Bravo Correct Answer\n");
    return (0);
}