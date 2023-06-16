#include <stdio.h>

int main()
{
    int age;
    int exp;

    printf("Enter the age : ");
    scanf("%d", &age);
    printf("Enter the experience time : ");
    scanf("%d", &exp);
    
    if (age < 20 && exp >= 0 && exp <= 10)
        printf("The salary is 10.000\n");

    else if (age < 20 && exp > 10)
        printf("Error\n");

    else if ((age <= 50 && age >= 20)
                    && (exp >= 0 && exp <= 10))
        printf("The salary is 15.000\n");

    else if ((age <= 50 && age >= 20)
                    && (exp > 10))
        printf("The salary is 20.000\n");

    else if (age > 50 && (exp >= 0 && exp <= 10))
        printf("The salary is 20.000\n");

    else if (age > 50 && exp > 10)
        printf("THe salary is 25.000\n");

    return (0);   

}
