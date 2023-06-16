#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void    part1()
{
    int year;

    //SCANNING YEAR from USER
    printf("**************************\n");
    printf("Please Enter a Year: ");
    scanf("%d", &year);

    //CHECKING WHETHER THE YEAR LEAP YEAR OR NOT
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        printf("%d is a leap year\n", year);
    else
        printf("%d is not a leap year\n", year);
    printf("**************************\n\n");
}

//THIS FUNCTION IS USED BY PART2 for I_format and S_format
//It finds the digit amount of int number
//for ex: 123: it will return 3
int find_digit(int res)
{
    int cnt;

    cnt = 0;
    while (res != 0)
    {
        res /= 10;
        cnt++;
    }
    return (cnt);
}

//THIS FNCTION IS USED BY PART2 FOR S_format
//It finds how many numbers after the ',' expect '0'
//for ex: 00.12340000000 : it will return 4 (1,2,3,4)
int find_digit_fraction(double nbr)
{
    int fdigit;

    fdigit = 0;
    while (nbr != (double)(int)nbr)
    {
        nbr *= 10;
        fdigit++;
    }
    return (fdigit);
}

void    s_format_printer(double res, int m, int n)
{
    int i; //its temporary variable for n
    double nbr; //its my main variable, it will be used while printing
    double tmp; //its temporary variable for nbr
    int e;  // its refers to the x on e^x
    int zero; // its refers that how many times i will print zero for the m variable

    nbr = res;
    zero = 0;
    e = 0;
    i = n;
    while (nbr != (double)(int)nbr) //If the number is double, i make it kind of integer
        nbr *= 10;                  //for ex: 12.35 -> 1235.000...

    while ((int)nbr % 10 == 0)      //If the number is has zero on its end, i simplfy it
        nbr /= 10;                  //for ex: 120.00... -> 12.000...

    while (i-- > 0)                 //I divide the number by 10 n times                 
        nbr /= 10;                  //for ex (n=2): 1235.000... -> 12.35000...


    //find_digit_fraction: for ex nbr = 12.35000..., it will return the amount of the
    //                                               numbers after '.' expect 0 in this case it returns 2
    //find_digit: for ex nbr = 12.35, it will return the amount of the numbers before '.',
    //                                               in this case it returns 2
    //so that i calculate how many digits that i print then i calculate how many digits left
    //for ex m = 8 and nbr = 12.35 i should print 4 zeros -> 000012.35
    zero = m - (find_digit_fraction(nbr) + find_digit((int)nbr));

    if (find_digit((int)nbr) == 0) //if the nbr like this 0.123000...
        zero--;                    //find_digit returns 0 but the nbr
    tmp = nbr;                     //has its own zero so that i should print '0' zero - 1 times

    while ((int)tmp != (int)res) //I calculate the x variable on e^x 
    {
        if (tmp > res) //FOR EX: RES: 7.35, M:7, N:1 -> temp = 000073.5
        {              //in this case e should be negative
            tmp /= 10; //i divide the tmp by 10 until int(tmp) = int(res)
            e--;       //each run e -= 1 (in this case e is -1)
        }
        else           //FOR EX: RES: 120, M:4, N:2 -> temp = 00.12
        {              //in this case e should be positive
            tmp *= 10; //i muliply the tmp by 10 until int(tmp) = int(res)
            e++;       //each run e += 1 (in this case e is 3)
        }            
    }
    while (zero-- > 0)
        printf("0");
    printf("%.*fe%d\n\n", n, nbr, e); //n refers to the how many digit after the '.'
}

//THIS FUNCTION IS USED BY PART2, IT DOES THE GIVEN OPERATION WITH GIVEN NUMBERS
double  do_op(double nbr1, double nbr2, char op)
{
    double res;
    double tmp;

    res = 1;
    switch(op)
    {
        case '!': // FACTORIAL OP
            tmp = nbr1;
            res = 1;
            while (tmp > 0)  // multiplying the result which is 1, by tmp 
            {                // which is nbr1, nbr1 - 1, nbr1 - 2 ...
                res *= tmp;
                tmp--;
            }
            break;
        case '+': // ADDITION
            res = nbr1 + nbr2;
            break;
        case '-': // SUBSTRACTION
            res = nbr1 - nbr2;
            break;
        case '*': // MULTIPLICATION
            res = nbr1 * nbr2;
            break;
        case '/': // DIVISION
            res = nbr1 / nbr2;
            break;
        case '%': // MOD
            res = fmod(nbr1, nbr2);
            break;
        case '^': // EXPONENTIAL OPERATION
            tmp = nbr2;
            res = 1;
            while (tmp > 0)  //multiplying res which is 1, nbr=tmp times
            {                //for ex 5 ^ 3 = 1 * 5 * 5 * 5
                res *= nbr1;
                tmp--;
            }
            break;
    }
    return (res);
}

//THIS FUNCTION IS USED BY PART2 FOR THE I FORMAT PART
void    I_format()
{
    char op;
    double res;

    //SCANNING THE OPERATION
    printf("Enter the operation(+,-,/,*,%%,!,^): ");
    scanf(" %c", &op);

    // IF OP FACTORIAL, I NEED ONLY 1 OPERAND
    if (op == '!')
    {
        double nbr;

        printf("Enter the operand: ");
        scanf("%lf", &nbr); //SCANNING OPERAND
        res = do_op(nbr, 0, op); //DOING THE OPERATION IN DO_OP FUNCTION
        printf("%d%c = %d\n", (int)nbr, op, (int)res); // PRINTING THE RESULT
    } //ELSE 2 OPERAND
    else if (op == '+' || op == '-' || op == '/' || op == '*'
                || op == '%' || op == '^')
    {
        double nbr1;
        double nbr2;

        //SCANNING THE OPERANDS
        printf("Enter the first operand: ");
        scanf("%lf", &nbr1);
        printf("Enter the second operand: ");
        scanf("%lf", &nbr2);

        // DOING THE OPERATION IN DO_OP FUNCTION THEN PRINTING THE RESULT
        res = do_op(nbr1, nbr2, op);
        printf("%d%c%d = %d\n", (int)nbr1, op, (int)nbr2, (int)res);
    }
    else
    {
        printf("Error! Invalid Operation\n");
        return ;
    }
}

//THIS FUNCTION IS USED BY PART2 FOR THE S FORMAT PART
void    S_format()
{
    char    op; //rrefers to operation
    double  res; //refers to result
    int     m;
    int     n;

    //SCANNING M N VALUES AND OPERATION
    printf("Enter m n values: ");
    scanf("%d %d", &m, &n);
    if (m <= n)
    {
        printf("Warning! m should be greater than n");
        return ;
    }
    printf("Enter the operation(+,-,/,*,%%,!,^): ");
    scanf(" %c", &op);
    res = 0;

    //IF OPERATION IS FACTORIAL, I NEED 1 OPERAND
    if (op == '!')
    {
        double nbr;
        printf("Enter the operand: ");
        scanf("%lf", &nbr);
        res = do_op(nbr, 0, op);
        s_format_printer(res, m, n);
    } //ELSE 2 OPERAND
    else if (op == '+' || op == '-' || op == '/' || op == '*'
                || op == '%' || op == '^')
    {
        double  nbr1;
        double  nbr2;

        //SCANNING THE OPERANDS
        printf("Enter the first operand :");
        scanf("%lf", &nbr1);
        printf("Enter the second operand :");
        scanf("%lf", &nbr2);

        //DOING THE OPERATION IN DO_OP FUNCTION THEN PRINTING THE RESULT
        res = do_op(nbr1, nbr2, op);
        s_format_printer(res, m, n);
    }
    else
    {
        printf("Error! Invalid Operation\n");
        return ;
    }
}

void    part2()
{
    char frmt; // refers to format

    //SCANNING FORMAT, M, N VALUES, OPERATION
    printf("************************************\n");
    printf("Enter the format of output (S or I): ");
    scanf(" %c",&frmt);
    if (frmt == 'I')
    {
        I_format();
    }
    else
    {
        S_format();
    }
}

void    part3()
{
    double exam1;
    double exam2;
    double exam3;
    double hw1;
    double hw2;
    double final;

    //SCANNING 3 EXAM GRADES OF STUDENT
    printf("************************************\n");
    printf("Enter 3 exam grades of student out of 100: ");
    scanf("%lf %lf %lf", &exam1, &exam2, &exam3);

    //SCANNING 2 ASSIGNMENT GRADES OF STUDENT
    printf("Enter 2 assignment grades of student out of 100: ");
    scanf("%lf %lf", &hw1, &hw2);

    //CHECKING WHETHER THE GRADES ARE OUT OF 100 OR NOT
    //IF NOT THE PROGRAM ENDS
    if (exam1 > 100 || exam2 > 100 || exam3 > 100
            || hw1 > 100 || hw2 > 100)
    {
        printf("Please enter a grade out of 100\n");
        return ;
    }


    //CALCULATING THE FINAL GRADE OF STUDENT by using the formula below
    //f.grade = [(exam1 + exam2 + exam3)/3]*(0.6) + [(hw1 + hw2)/2]*(0.4)
    final = ((exam1 + exam2 + exam3) * 6) / 30 + ((hw1 + hw2) * 4) / 20;

    //CHECKING WHETHER STUDENT FAILED OR PASSED
    if (final >= 60)
        printf("Final Grade: %.1lf Congrats Passed!\n", final);
    else
        printf("Final Grade: %.1lf Failed!\n", final);
    printf("************************************\n\n");
}

int main()
{
    //******PART_1***********
    part1();
    //******PART_1 END*******
    
    //******PART_2***********
    part2();
    //******PART_1 END*******
    
    //**********PART_3********
    part3();
    //*********PART_3 END*****

    return (0);
}
