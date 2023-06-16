#include "utils.h"

//THIS FUNCTION IS USED IN PART_3
//it is similar to pow() funct in math.h
int power(int base, int pwr) 
{
    int result;

    result = 1;
    if (pwr == 0)
        return (1);
    else if (pwr == 1)
        return (base);
    while (pwr > 0)
    {
        result *= base;
        pwr--;
    }
    return (result);
}

//THIS FUNCTION IS USED IN PART_3
//it is basically print the value(ı explained the value ın p3)
// for example 123*0, it will print
// 000, 19*7 it will print 133
void    print_value(int value, int nbr1, int i)
{
    int cnt;
    int tmp;

    cnt = 0;
    tmp = nbr1;

    //Finding the nbr1's digit count to print
    //whitespace for the math operations
    //since we are using base 10 dividing by 10
    while (tmp > 0)
    {
        tmp /= 10;
        cnt++;
    }

    //if the value(explained in p3) is 0, 
    //if condition manages to print'0', nbr1's digits times
    //for ex nbr1 = 123, it will print 0 '3' times
    if (value == 0)
    {
        while (10 - cnt - i++ > 0)
            printf(" ");//printing whiteespace
        while (nbr1 > 0)
        {
            printf("%d", value);
            nbr1 /= 10;
        }
        printf("\n");
    }
    //no need to check if the 
    //value(I explained the value in p3) is not '0'
    else
    {
        printf("%*d\n", 10 - i, value);//the first parameter
    }                                  //refers to the *
}                                      //used while multiplication

void    part_1(void)
{
    int nbr1;
    int nbr2;
    int r; // it refers to remainder
    int tmp1;
    int tmp2;

    printf("The First Number: ");
    scanf("%d",&nbr1);
    printf("The Second Number : ");
    scanf("%d",&nbr2);
    printf("\n");
    r = 0;
    tmp1 = nbr1; // i use tmp1 at the end 
    tmp2 = nbr2; // i used tmp2 at the end
    if (nbr1 == 0 || nbr2 == 0)
    {
        printf("There is no common divisor\n");
        return ;
    }
    if (nbr1 < 0 || nbr2 < 0)
    {
        printf("There is no common divisor\n");
        return ;
    }

    //Euclidean algorithm finds the remainder of 
    //greater / smaller so that if nbr2 is greater
    //than nbr1, I am swapping the numbers, because
    //I am going to do operation as nbr1 % nbr2
    if (nbr1 < nbr2) 
    {                
        int temp;
        
        temp = nbr1;
        nbr1 = nbr2;
        nbr2 = temp;
    }

    //Assume that we are trying to find GCD of number A
    //and number B, the euclidean algorithm works as
    //diving a to b and each run new value of a is b
    // new value of b is r(remainder)
    // the algorithm keeps doing it until b is zero
    // and the gcd is the last value of a
    while (nbr2 != 0)
    {
        r = nbr1 % nbr2;
        nbr1 = nbr2;
        nbr2 = r;
    }
    printf("The Gcd of %d and %d is: %d\n", tmp1, tmp2, nbr1);
}

void    part_2(void)
{
    int nbr1;
    int nbr2;
    int sum;

    printf("The First Number: ");
    scanf("%d",&nbr1);
    printf("The Second Number : ");
    scanf("%d",&nbr2);
    printf("\n");
    sum = nbr1 + nbr2;

    printf("%7d\n", nbr1);
    printf("%7d\n", nbr2);
    printf("+\n");
    printf("-------\n");
    printf("%7d\n", sum);
}

void    part_3(void)
{
    int nbr1;
    int nbr2;
    int tmp1;
    int tmp2;
    int value;
    int sum;
    int i;

    printf("The First Number: ");
    scanf("%d",&nbr1);
    printf("The Second Number : ");
    scanf("%d",&nbr2);
    printf("\n");
    tmp1 = nbr1;
    tmp2 = nbr2;
    sum = 0;
    i = 0;
    value = 0;

    printf("%10d\n", nbr1);
    printf("%10d\n", nbr2);
    printf("*\n");
    printf("----------\n");

    //My algorithm multiply the first number
    //by second number's each digit then
    //adds the result to the sum by considering
    //the digit value for ex;
    //17 * 9 = (7 * 9 * 1) + (1 * 9 * 10)
    //1 and 10 are digit value
    // my "power()" function is used while 
    // calculating the digit value
    while (tmp2 != 0)
    {
        value = tmp1 * (tmp2 % 10); //for ex 17 * 10: first run 0, second run its 17
        if (i == 0)
            sum += value;
        else if (i != 0)
            sum += (value * power(10 , i));//for ex 17*10: it is 17 * (10^1)
        print_value(value, tmp1, i);
        tmp2 /= 10;
        i++;
    }

    if (nbr2 == 0)
    {
        printf("%10d\n",0);
    }
    printf("+\n");
    printf("----------\n");
    printf("%10d", sum);
}

void    part_4(void)
{
    int nbr;

    printf("Please enter an integer between 1 and 10(inclusive): ");
    scanf("%d", &nbr);

    if (nbr <= 10 && nbr >= 1)
    {
        if (nbr <= 5)
            printf("The integer you entered is less than or equal to 5");
        else
            printf("The integer you entered is greater than 5");
        return ;
    }
    printf("Invalid input");
}