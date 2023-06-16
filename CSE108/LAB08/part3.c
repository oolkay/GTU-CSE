#include <stdio.h>
#include <math.h>

typedef struct {
    double arr[4];
} third_order_polynominal;

typedef struct {
    double arr[7];
} polynominal;

polynominal calculate_integral(third_order_polynominal poly1, third_order_polynominal poly2, int a, int b)
{
    double multiplied[7];
    double result_integral[7];
    
    polynominal res_poly;
    polynominal poly;

    for (int i=0 ; 6>=i ; i++)
    {
        poly.arr[i] = 0;
        for (int j=0; j<=3 ; j++)
            if (i-j >= 0)
                poly.arr[i] += poly1.arr[j]*poly2.arr[i-j];
    }
    for (int i = 0; i < 7; i++)
        res_poly.arr[i] = poly.arr[i] / (i+1);

    // for (int i = 0; i < 7; i++)
    //     printf("%lf ", res_poly.arr[i]);
    // printf("\n");
    // for (int i = 0; i < 7; i++)
    //     printf("%lf ", poly.arr[i]);
    // printf("\n");
    return res_poly;
}

int main(void)
{
    int a, b;
    polynominal integrated;
    third_order_polynominal poly1;
    third_order_polynominal poly2;

    printf("Enter the variables of first polynom in order x^0 to x^3: ");
    scanf("%lf %lf %lf %lf", &poly1.arr[0], &poly1.arr[1], &poly1.arr[2], &poly1.arr[3]);

    printf("Enter the variables of second polynom in order x^0 to x^3: ");
    scanf("%lf %lf %lf %lf", &poly2.arr[0], &poly2.arr[1], &poly2.arr[2], &poly2.arr[3]);

    printf("Please enter the interval that is used in integral (a, b): ");
    scanf("%d %d", &a, &b);

    integrated = calculate_integral(poly1, poly2, a, b);

    double upper = 0,lower = 0;
    for (int i = 0; 6 >= i ; i++)
    {
        lower += integrated.arr[i]*pow(a,i+1);
        upper += integrated.arr[i]*pow(b,i+1);
    }
    double diff = upper - lower;
    printf("%lf", diff);
}