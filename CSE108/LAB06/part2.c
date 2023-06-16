#include <stdio.h>

#define SIZE 50

//this function, read data from txt and assing the datas to the arrays
//returns the row
int    read_input(int age[], char occupation[], float salary[], char team[])
{
    int row;
    int i;
    FILE *fp;

    fp = fopen("table.txt", "r");
    fscanf(fp, "%d", &row);
    i = 0;
    while (i < row)
    {
        fscanf(fp, "%d %c %f %c", &age[i], &occupation[i], &salary[i], &team[i]);
        i++;
    }
    fclose(fp);
    return (row);
}

int main()
{
    //i didnt array[row] because assinging a variable into a array is not valid in some versions
    int age[SIZE];
    char occupation[SIZE];
    float salary[SIZE];
    char team[SIZE];
    char ch; //team choice of the user
    int row;
    int i = 0;
    float total_salary = 0;
    float avrg_salary;
    int cnt = 0; //it counts amount of the choice of the user in database

    row = read_input(age, occupation, salary, team);
    printf("Please select a team: ");
    scanf("%c", &ch);
    while (i < row)
    {
        if (team[i] == ch)
        {
            total_salary += salary[i];
            cnt++;
        }
        i++;
    }
    if (cnt == 0)
        printf("There are no fans of %c in the database", ch);
    else
    {
        avrg_salary = total_salary / cnt;
        printf("Average salaries of fans of %c: %.1f", ch, avrg_salary);
    }
}