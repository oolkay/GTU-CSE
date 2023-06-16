#include <stdio.h>

int calculate_note(int nbr)
{
    switch (nbr / 10)
    {
        case 10:
            printf("A+");
            break;
        case 9:
            printf("A+ ");
            break;
        case 8:
            printf("A ");
            break;
        case 7:
            printf("B+ ");
            break;
        case 6:
            printf("A+ ");
            break;
        case 5:
            printf("B ");
            break;
        case 4:
            printf("D ");
            break;
        default:
            printf("F ");
    }

}

int main()
{
    int ex1;
    int ex2;
    int ex3;
    double avrg;

    printf("Enter The Scores: ");
    scanf("%d %d %d", &ex1, &ex2, &ex3);
    avrg = ((double)ex1 + (double)ex2 + (double)ex3) / 3;

    printf("Your letter grades are ");
    ex1 = calculate_note(ex1);
    printf(",");
    ex2 = calculate_note(ex2);
    printf("and ");
    ex3 = calculate_note(ex3);
    printf(" with an %.1lf average\n", avrg);
}