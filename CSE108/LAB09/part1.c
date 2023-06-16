#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_furniture
{
    char name[30];
    char color[6];
    double price;
    int serial_number;
    int quantity;
}furniture;

void search_by_name(furniture database[100], int i, int cnt, char str[20])
{
    if (i >= cnt)
        return ;
    if (strcmp(database[i].name, str) == 0)
    {
        printf("Name: %s\n", database[i].name);
        printf("Color: %s\n", database[i].color);
        printf("Price: %.2lf\n", database[i].price);
        printf("Serial Number: %d\n", database[i].serial_number);
        printf("Quantity: %d\n", database[i].quantity);
    }
    search_by_name(database, i + 1, cnt, str);
}

void search_by_color(furniture database[100], int i, int cnt, char str[20])
{
    if (i >= cnt)
        return ;
    if (strcmp(database[i].color, str) == 0)
    {
        printf("Name: %s\n", database[i].name);
        printf("Color: %s\n", database[i].color);
        printf("Price: %.2lf\n", database[i].price);
        printf("Serial Number: %d\n", database[i].serial_number);
        printf("Quantity: %d\n", database[i].quantity);
    }
    search_by_name(database, i + 1, cnt, str);
}

void search_furniture(furniture database[100], int cnt)
{
    int i;
    char str[20];
    printf("1) Search by name\n");
    printf("2) Search by color\n");
    printf("Select a propery to make a search: ");
    scanf("%d", &i);
    switch (i)
    {
        case 1:
            printf("\nEnter the name of product: ");
            scanf("%s", str);
            search_by_name(database, 0, cnt, str);
            break;
        case 2:
            printf("\nEnter the color of product: ");
            scanf("%s", str);
            search_by_color(database, 0, cnt, str);
            break;
        default:
            return ;
    }
}

void fill_database(furniture database[100], int cnt)
{
    int i = 0;
    FILE *fp = fopen("furniture_database.txt", "r");
    while (i < cnt)
    {
        fscanf(fp, "%[^,], %[^,], %lf, %d, %d", database[i].name, database[i].color, &database[i].price, &database[i].serial_number, &database[i].quantity);
        i++;
    }
    fclose(fp);
}

void see_all_furnitures(furniture database[100], int cnt)
{
    int i = 0;
    while (i < cnt)
    {
        printf("Name: %s\n", database[i].name);
        printf("Color: %s\n", database[i].color);
        printf("Price: %.2lf\n", database[i].price);
        printf("Serial Number: %d\n", database[i].serial_number);
        printf("Quantity: %d\n", database[i].quantity);
        printf("\n\n");
        i++;
    }
}

void remove_furnitures(furniture database[100], int cnt)
{
    FILE *fp = fopen("furniture_database.txt", "w");
    int serial_num;
    char ch = fgetc(fp);
    int indx;
    int i = 0;
    int quantity;
    printf("Enter the index of product you want to remove: ");
    scanf("%d", &indx);
    while (i < cnt)
    {
        if (i != indx)
            fprintf(fp, "%s, %s, %.2lf, %d, %d\n", database[i].name, database[i].color, database[i].price, database[i].serial_number, database[i].quantity);
        i++;
    }
    fclose(fp);
}

void add_new_furniture(furniture database[100], int cnt)
{
    FILE *fp = fopen("furniture_database.txt", "a");
    char ch;
    char name[30];
    char color[6];
    double price;
    int serial_number;
    int quantity;


    printf("Please Enter the properties of new furniture(Name, color, price, serial number, quantity): ");
    scanf("%s %s %lf %d %d", name, color, &price, &serial_number, &quantity);

    printf("\nFollowing furnitre is added to the database: \n");
    printf("Name: %s\n", name);
    printf("Color: %s\n", color);
    printf("Price: %.2lf\n", price);
    printf("Serial Number: %d\n", serial_number);
    printf("Quantity: %d\n", quantity);

    strcpy(database[cnt].name, name);
    strcpy(database[cnt].color, color);
    database[cnt].price = price;
    database[cnt].serial_number = serial_number;
    database[cnt].quantity = quantity;
    fprintf(fp, "%s, %s, %.2lf, %d, %d\n", name, color, price, serial_number, quantity);
    fclose(fp);
}

void menu(furniture database[100])
{
    int i = 1;
    int cnt = 0;
    while (i == 1 || i == 2 || i == 3 || i == 4)
    {
        printf("\n1)See all furnitures.\n");
        printf("2)Add new furniture.\n");
        printf("3)Remove furniture.\n");
        printf("4)Search furniture.\n");
        printf("5)Exit\n");
        printf("Select an option: ");
        scanf("%d",&i);
        switch(i)
        {
            case 1:
                see_all_furnitures(database, cnt);
                break;
            case 2:
                add_new_furniture(database, cnt);
                cnt++;
                break;
            case 3:
                remove_furnitures(database, cnt);
                cnt--;
                fill_database(database, cnt);
                break;
            case 4:
                search_furniture(database, cnt);
                break;
            case 5:
                return ;
        }
    }
}

int main()
{
    furniture database[100];
    menu(database);
    return (0);
}