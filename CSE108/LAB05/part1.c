#include <stdio.h>

double  temperature_converter(int op, double nbr)
{
    double res;

    if (op == 1)
    {
        res = (nbr * 9) / 5 + 32;
    }
    else if (op == 2)
    {
        res = (5 * (nbr - 32)) / 9;
    }
    return (res);
}

void    menu()
{
    int op;
    double  res;
    double  nbr;

    op = 1;
    while (op == 1 || op == 2)
    {
        printf("Temperature Conversion Menu\n");
        printf("1) Convert Celsius to Fahrenheit\n");
        printf("2) Convert Fahrenheit to Celcius\n");
        printf("3) Quit\n");

        printf("Enter your choice (1-3): ");
        scanf("%d", &op);

        if (op == 1)
        {
            printf("Enter the temperature value to convert: "); //scanning celcius nbr to convert fahrenheit
            scanf("%lf", &nbr); //scanning
            res = temperature_converter(op, nbr);
            printf("%.2lf Celcius = %.2lf Fahrenheit\n\n", nbr, res);
        }
        else if (op == 2)
        {
            printf("Enter the temperature value to convert: "); //scanning fahrenheit nbr to convert celcius
            scanf("%lf", &nbr); // scanning
            res = temperature_converter(op, nbr);
            printf("%.2lf Fahrenheit = %.2lf Celcius\n\n", nbr, res);
        }
        else if (op == 3)
        {
            return ;
        }
    }
}

int main()
{
    menu();
    return (0);
}