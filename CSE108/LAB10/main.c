#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct student
{
    int ID;
    int age;
    float gpa;

}Student;

//PART1 FUNCTION
int *funct(int size)
{
    int *arr = (int *)malloc(size * sizeof(int));
    int i = 0;
    
    printf("Please enter %d integer: ", size);
    while (i < size)
    {
        scanf("%d", &arr[i]);
        i++;
    }
    return (arr);
}

int find_min(int *arr, int size)
{
    int i = 0;
    int min = arr[0];
    while (i < size)
    {
        if (arr[i] < min)
            min = arr[i];
        i++;
    }
    return (min);
}//PART1 FUNCTION END

//PART2 FUNCTION
void cumulative_sum(int *arr1, int *arr2, int size2)
{
    int i = 0, j = 0;
    int sum = 0;

    while (i < size2)
    {
        j = 0;
        while (j <= i)
        {
            arr2[i] += arr1[j];
            j++;
        }
        i++;
    }
}//PART2 FUNCTION END

//part3 FUNCTION
float part3(Student *students)
{
    int i = 0;
    float avrg = 0;
    students = (Student *)malloc(sizeof(Student)*10000);
    while (i < 10000)
    {
        students[i].age = rand() % 20 + 5;
        students[i].ID = rand() % 10000;
        students[i].gpa = (float)(rand() % 401) / 100;
        avrg += students[i].gpa;
        i++;
    }
    return (avrg/10000);
}

int main()
{
    srand(time(NULL));
    int size;//PART1
    int *arr;//PART1

    int size2;//PART2
    int *arr2;//PART2

    int min = 0;
    int i = -1;
    float avrg = 0;//PART3


    Student *students;

    printf("Please enter the size of the array: ");
    scanf("%d", &size);
    printf("\n");
    arr = funct(size);
    min = find_min(arr,size);
    printf("Min of the array elements: %d\n\n", min);

    printf("Please enter the number of the integers: ");
    scanf("%d", &size2);
    arr2 = calloc(size2, sizeof(int));
    cumulative_sum(arr, arr2, size2);
    printf("\nFirst array: ");
    while (++i < size)//printing first array
        printf("%d ", arr[i]);
    i = -1;
    printf("\n");
    printf("\nSecond array: ");
    while (++i < size)//printing second array
        printf("%d ", arr2[i]);
    free(arr); //deallocating memory
    free(arr2); //deallocating memory
    i = -1;
    while (++i < 10000)
    {
        avrg += part3(students);
        free(students);
    }
    avrg /= 10000;
    printf("\n\nAverage GPA of 10.000 x 10.000 students: %.4f\n", avrg);
    return (0);
}