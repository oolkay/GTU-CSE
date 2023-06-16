#include <stdio.h>

int main()
{
    double x;
    double y;
    double z;
    double max;

    printf("Please enter the x value : ");
    scanf("%lf", &x);
    printf("Please enter the y value : ");
    scanf("%lf", &y);

    if (x > y)
        max = x;
    else 
        max = y;

    z = (x / y) + max / (x + y);

    printf("Calculated z value : %lf\n", z);
}
