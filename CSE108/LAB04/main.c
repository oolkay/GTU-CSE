#include <stdio.h>

void    draw_square(int size)
{
    int i;
    int j;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            if (i == 0 || i == size-1
                || j == 0 || j == size -1)
                printf("* ");
            else if (j != 0 && j != size - 1)
                printf("  ");
            j++;
        }
        printf("\n");
        i++;
    }
}

void    draw_triangle(int size)
{
    int i;
    int j;

    i = 1;
    while (i <= size - 1)
    {
        for (j = 1; j <= 2 * size - 2 * i; j++)
        {
            printf(" ");
        }
        printf("*");
        for (j = 1; j <= (2 * (i - 1) - 1); j++)
        {
            printf(" ");
        }
        for (j = 1; j <= 2*i - 3; j++)
            printf(" ");
        if (i != 1)
            printf(" *");
        for (j = 1; j <= 2 * size - 2 * i; j++)
        {
            printf(" ");
        }
        printf("\n");
        i++;
    }
    if (i == size)
    {
        for (j = 0; j < 2* size - 1; j++)
            printf("* ");
    }
    printf("\n");
}

void    sequence_to_file()
{
    FILE *fd;
    char ch;
    int size;

    fd = fopen("shape.txt", "w");
    printf("Enter format of the shape (s or t): ");
    scanf(" %c", &ch);
    while (ch != 'e')
    {
        printf("Enter size of the shape: ");
        scanf("%d", &size);
        fprintf(fd, "%c,%d\n", ch, size);
        printf("\nEnter format of the shape (s or t): \n");
        scanf(" %c", &ch);
    }
    fclose(fd);
}

void    read_draw_shape()
{
    FILE *fd;
    char ch;
    int size;

    fd = fopen("shape.txt", "r");
    while (fscanf(fd, "%c,%d\n", &ch, &size) != -1)
    {
        if (ch == 's')
            draw_square(size);
        else if (ch == 't')
            draw_triangle(size);
    }
    fclose(fd);
}

int main()
{
    int n;
    char ch;
    int size;

    n = 0;
    while (n != 3)
    {
        printf("Welcome to Shape Reader! Please make your choice to continue: \n");
        printf("1-) Generate a shape file \n");
        printf("2-) Read and draw a shape file \n");
        printf("3-) Terminate the program \n");
        scanf("%d", &n);
        switch (n)
        {
            case 1:
                sequence_to_file();
                break;
            case 2:
                read_draw_shape();
                break;
            case 3:
                return (0);
                break;
        }
    }
}