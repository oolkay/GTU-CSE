#include <stdio.h>

int main()
{
    float bmi;
    float weight;
    float height;

    printf("Enter your height(m): ");
    scanf("%f", &height);
    printf("Enter your weight(kg): ");
    scanf("%f", &weight);

    bmi = weight / (height * height);

    printf("Your bmi: %.1f\n", bmi);
    if (bmi < 18.5)
    {
        printf("Underweight\n");
    }
    else if (bmi <= 24.9 && bmi >= 18.5)
    {
        printf("Average weight\n");
    }
    else if (bmi <= 29.9 && bmi >= 25)
    {
        printf("Overweight\n");
    }
    else if (bmi >= 30)
    {
        printf("Obese\n");
    }
}