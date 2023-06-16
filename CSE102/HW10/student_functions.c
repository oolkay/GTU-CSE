#include "utils.h"

//freeing the student struct
void freeStudent(Student **student)
{
    Student *tmp = NULL;
    while ((*student) != NULL)
    {
        tmp = *student;
        *student = (*student)->next;
        free(tmp->name);
        free(tmp->borrowedbooks);
        free(tmp);
    }
}

//printing the student struct
void printStudents(Student *student)
{
    if (!student)
        return ;
    while (student != NULL)
    {
        printf("%s, %d, %s\n", student->name, student->id, student->borrowedbooks);
        student = student->next;
    }
}

//printing the given student's borrowed books
void studentBorrowedBooks(Student *student, int id)
{
    int flag = 0;
    int len = 0;
    int i = 0;
    // if there is no student
    if (!student)
    {
        printf(RED);// RED is defined in utils.h, it is a macro for red color
        printf("---->No borrowed books\n\n");
        return ;
    }
    while (student != NULL)
    {
        // if the student is found
        if (student->id == id)
        {
            if (flag == 0)
            {
                printf(CYN); // CYN is defined in utils.h, it is a macro for cyan color
                printf("┌──────────────────%s's BORROWED BOOKS──────────────────┐\n", student->name);
                len = strlen(student->name);
            }
            printf(WHT); // WHT is defined in utils.h, it is a macro for white color  
            for (i = 0; i < (35 + len ) / 2; i++)
                printf(" ");
            printf("#  isbn: %s\n", student->borrowedbooks);
            flag = 1;
        }
        student = student->next;
    }
    // if the student is not found
    if (student == NULL && flag == 0)
    {
        printf(RED);// RED is defined in utils.h, it is a macro for red color
        printf("----->Student not found\n\n");
        return ;
    }
    printf(CYN); // CYN is defined in utils.h, it is a macro for cyan color //53
    printf("└");
    for (len = len + 53; len > 0; len--)
        printf("─");
    printf("┘\n\n");

}

//deleting the given student
void deleteStudent(Student **student, char *isbn)
{
    Student *tmp = *student;
    Student *prev = NULL;
    // if there is no student
    if (!*student)
        return ;
    // if the student is the first element
    if (strcmp((*student)->borrowedbooks, isbn) == 0)
    {
        *student = (*student)->next;
        free(tmp->name);
        free(tmp->borrowedbooks);
        free(tmp);
        return ;
    }
    // if the student is not the first element
    while (*student != NULL)
    {
        // if the student is found
        if (strcmp(tmp->borrowedbooks, isbn) == 0)
        {
            prev->next = tmp->next;
            free(tmp->name);
            free(tmp->borrowedbooks);
            free(tmp);
            return ;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    // if the student is not found
    if (!*student)
    {
        printf(RED);// RED is defined in utils.h, it is a macro for red color
        printf("----->Student not found\n\n");
    }
}

//adding the given student
void addSudent(Student **student, char *name, int id, char *borrowedbook)
{
    Student *new = (Student *)malloc(sizeof(Student));
    new->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    new->borrowedbooks = malloc(sizeof(char *) * strlen(borrowedbook) + 1);
    new->id = id;
    strcpy(new->name, name);
    strcpy(new->borrowedbooks, borrowedbook);
    new->next = NULL;
    if (*student == NULL)
        *student = new;
    else
    {
        Student *tmp = *student;
        while (tmp->next != NULL && tmp->id != id)
            tmp = tmp->next;
        tmp->next = new;
    }
}