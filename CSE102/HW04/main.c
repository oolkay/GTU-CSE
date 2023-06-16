#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//this function calculates the digit of the number
//for ex 123 digit = 3
int find_digit(int nbr)
{
    int digit;
    
    digit = 0;
    while (nbr != 0)
    {
        nbr /= 10;
        digit++;
    }
    return (digit);
}

//THIS FUNCTION READ FROM TXT CHAR BY CHAR
//PRINTS THE PRODUCTS
//AND RETURNS THE AMOUNT OF PRODUCTS
int print_menu(FILE *fd)
{
    int i;
    char ch;

    i = 1;
    printf("Yemek Listesi:\n");
    while (ch != '\n') //in txt first line is containts Product and Price
        ch = fgetc(fd);      //this while manages to skip this line as we shown in pdf
    ch = fgetc(fd);
    while (i && ch != EOF)
    {
        printf("%d. ", i);
        while (ch != 32 && ch!= '\t' && ch) //We are supposed to only print products
        {                                   //this while reads only products and print it
            printf("%c", ch);
            ch = fgetc(fd);
        }
        printf("\n");
        while ((ch > 'Z' || ch < 'A')               //this while skips if char is not alphabetical
            && (ch > 'z' || ch < 'a') && ch != EOF) //in other words this while skips whitespaces and numbers
            ch = fgetc(fd);                         //and runs until the next line's product
        i++;
    }
    return (i - 1);
}

//thıs function make receipt and print it receipt.txt
/*
 2* Lahmacun                43.00

 3* Pide                   120.00

 4* Döner                  222.40*/
double make_receipt(int nbr, int srv)
{
    FILE *fd1 = fopen("menu.txt", "r");
    FILE *fd2 = fopen("receipt.txt", "a+");
    int    cnt = 0; //newline count
    char   ch;
    int    len = 0;
    double price = 0;
    int    flag = 0;

    //this while finds the correct selection
    //for ex user choose 3, this while finds line 2
    while (nbr != cnt)
    {
        ch = fgetc(fd1);
        if (ch == '\n')
            cnt++;
        if (!ch || ch == EOF)
            break;
    }

    ch = fgetc(fd1);
    fprintf(fd2, " ");
    if (srv > 1)
    {
        fprintf(fd2, "%d* ", srv);
        len += find_digit(srv) + 2;
    }
    while (ch != ' ' && ch != '\t')
    {
        fprintf(fd2, "%c", ch);
        if (ch > 127 || ch < 0) //if char is unicode for ex 'ö', the while runs 2 times
            flag = 1;           //that means i increment len 2 times instead of 1 so, this flag
        ch = fgetc(fd1);        //triggers line 87 and i decrement len by 1
        len++;
    }
    if (flag == 1)
        len--;
    fscanf(fd1, "%lf", &price);
    price *= srv;
    len = len + find_digit((int)price) + 3;
    for (int j = 0; j < 32 - len; j++)
        fprintf(fd2, " ");
    fprintf(fd2, "%.2lf\n", price);
    fprintf(fd2, "\n");
    fclose(fd1);
    fclose(fd2);
    return (price);
}

//this function check whether the user is student or not
//if the user is student, it calculates and prints that 
//discount to the receipt. Returns the price after the discount
double  student_discount(FILE *fd, double price)
{
    char   ch;

    ch = '1';
    fprintf(fd, "\n\n");
    while ((ch != 'Y' && ch != 'N') && (ch != 'y' && ch != 'n'))
    {
        printf("Are you student? (Y/N): ");
        scanf(" %c", &ch);
    }
    if (ch == 'N' || ch == 'n')
        return (price);
    else if (ch == 'Y' || ch == 'y')
    {
        fprintf(fd, " Student Discount:");
        for (int i = 0; i < 34 - (18 + find_digit((int)price) + 4); i++)
            fprintf(fd, " ");
        fprintf(fd, "-%.2lf\n\n", (price * 125)/1000);
    }
    price -= (price * 125)/1000;
    return (price);
}

/*this function prints top and bottom part to the receipt
10104004039        10.04.2023/20:27
------------------------------------

 Product                 Price (TL)

------------------------------------
                AND
------------------------------------

 Price:                       0.00

 Price + VAT:                0.00*/
void    top_bottom_receipt(char ch, double price)
{
    FILE *fd;
    //top part
    if (ch == 't')
    {
        char    str[50];
        struct tm    *st_time;
        time_t       real_time;

        fd = fopen("receipt.txt", "w");
        time(&real_time);
        st_time = localtime(&real_time);
        strftime(str,50,"%d.%m.%Y/%H:%M", st_time);
        fprintf(fd, "210104004039");
        for (int i = 0; i < 8; i++)
            fprintf(fd, " ");
        fprintf(fd, "%s\n\n", str);
        for (int i = 0; i < 36; i++)
            fprintf(fd, "-");
        fprintf(fd, "\n\n");
        fprintf(fd, " ");
        fprintf(fd, "Product");
        for (int i = 0; i < 17; i++)
            fprintf(fd, " ");
        fprintf(fd, "Price (TL)\n\n");
        for (int i = 0; i < 36; i++)
            fprintf(fd, "-");
        fprintf(fd, "\n\n");
    }
    //bottom part
    else if (ch == 'b')
    {
        fd = fopen("receipt.txt", "a+");
        for (int i = 0; i < 36; i++)
            fprintf(fd, "-");
        fprintf(fd, "\n\n");
        fprintf(fd, " ");
        fprintf(fd, "Price:");
        for (int i = 0; i < 26 - (find_digit((int)price) + 3); i++)
            fprintf(fd, " ");
        fprintf(fd, "%.2lf\n\n", price);
        fprintf(fd, " Price + VAT:");
        for (int i = 0; i < 20 - (find_digit((int)price) + 3); i++)
            fprintf(fd, " ");
        fprintf(fd, "%.2lf", price + (price * 18)/100);
    }
    fclose(fd);
}

//this function is applied when the user enter 0
//which means end of the order. It prints some
//values to the receipt and returns the price after discount
/*
Total:                       0.00

 Student Discount:         -0.00*/
double  end_of_the_order(double price)
{
    FILE *fd;
    double tmp; //temporary price

    fd = fopen("receipt.txt", "a+");
    tmp = price;
    fprintf(fd, " ");
    fprintf(fd, "Total:");
    for (int i = 0; i < 26 - (find_digit((int)price) + 3); i++)
        fprintf(fd, " ");
    fprintf(fd, "%.2lf", price);
    price = student_discount(fd, price);
    if ((int)tmp >= 150)
    {
        fprintf(fd, " Additional Discount:");
        for (int i = 0; i < 34 - (21 + find_digit((int)price) + 4); i++)
            fprintf(fd, " ");
        fprintf(fd, "-%.2lf\n\n", (tmp * 10)/100);
        price -= (tmp * 10)/100;
    }
    fclose(fd);
    return (price);
}

void    print_receipt_to_terminal()
{
    FILE *fd;
    char ch;

    fd = fopen("receipt.txt", "r");
    ch = fgetc(fd);
    printf("\n\n");
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(fd);
    }
    printf("\n\n");
    fclose(fd);
}

void    part1()
{
    FILE   *fd1 = fopen("menu.txt", "r");
    int    nbr = 1; //choosen product
    int    cnt; //amount of the products
    int    srv; //amount of the servings
    double price;

    price = 0;
    cnt = print_menu(fd1);
    fclose(fd1);
    top_bottom_receipt('t', price);
    while (nbr)
    {
        printf("\n\n");
        printf("Please choose a product (1-%d): ", cnt);
        scanf("%d", &nbr);
        while (nbr < 0 || nbr > cnt)
        {
            printf("\nINVALID PRODUCT\n");
            printf("Please choose a product (1-%d): ", cnt);
            scanf("%d", &nbr);
        }
        printf("\n");
        if (nbr == 0)
        {
            price = end_of_the_order(price);
            break;
        }
        printf("How many servings do you want?: ");
        scanf("%d", &srv);
        while (srv < 0)
        {
            printf("\nINVALID PRODUCT\n");
            printf("How many servings do you want?: ");
            scanf("%d", &srv);
        }
        if (srv == 0)
        {
            end_of_the_order(price);
            break;
        }
        price += make_receipt(nbr, srv);
    }
    top_bottom_receipt('b', price);
    print_receipt_to_terminal();
}

void    part2()
{
    int player;  //user choice
    int computer;//random choice by computer
    char flag;   //yes or no
    srand(time(NULL));

    flag = 'Y';
    while (flag == 'Y')
    {
        printf("Please make a choice !\n\n");
        printf("1: Stone, 2: Paper, 3: Scissors\n\n");
        scanf("%d", &player);

        //INVALID INPUT, ASKS AGAIN
        while (player < 1 || player > 3)
        {
            printf("INVALID INPUT\n");
            printf("1: Stone, 2: Paper, 3: Scissors\n");
            scanf("%d", &player);
        }
        printf("\n\n");
        computer = rand() % 3 + 1;
        switch(player)
        {
            case 1:
                printf("You chose Stone. ");
                if (computer == 1)
                    printf("I chose Stone. It's a tie!\n\n");
                else if (computer == 2)
                    printf("I chose Paper. I won!\n\n");
                else
                    printf("I chose Scissors. You won!\n\n");
                break;

            case 2:
                printf("You chose Paper. ");
                if (computer == 1)
                    printf("I chose Stone. You won!\n\n");
                else if (computer == 2)
                    printf("I chose Paper. It's a tie!\n\n");
                else
                    printf("I chose Scissors. I won!\n\n");
                break;

            case 3:
                printf("You chose Scissors. ");
                if (computer == 1)
                    printf("I chose Stone. I won!\n\n");
                else if (computer == 2)
                    printf("I chose Paper. You won!\n\n");
                else
                    printf("I chose Scissors. It's a tie!\n\n");
                break;
        }
        printf("Do you want to play again? (Y/N): ");
        scanf(" %c", &flag);
    }
}

int main()
{
    part1();
    printf("\n\n");
    part2();
    return (0);
}