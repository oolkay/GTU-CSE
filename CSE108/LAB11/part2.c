#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct exam
{
    char *student_name;
    int student_id;
    int score;
    struct exam *next;
}ExamPaper;


int my_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void display(ExamPaper *stack)
{
    ExamPaper *tmp;

    tmp = stack;
    printf("EXAM PAPERS IN THE STACK:\n");
    if (stack == NULL)
    {
        printf("No exam papers in the stack\n");
        return ;
    }
    while (tmp != NULL)
    {
        printf("- Student name: %s, ", tmp->student_name);
        printf("Student id: %d, ", tmp->student_id);
        printf("Score: %d\n\n", tmp->score);
        tmp = tmp->next;
    }
}

int isEmpty(ExamPaper *stack)
{
    ExamPaper *tmp;

    tmp = stack;
    if (tmp == NULL && tmp->next == NULL)
        return (1);
    return (0);
}

ExamPaper *pop(ExamPaper *stack)
{
    ExamPaper *tmp;
    ExamPaper *prev;

    printf("POPPED LAST ONE\n");
    tmp = stack;
    if (stack == NULL)
        return (NULL);
    if (stack->next == NULL)
    {
        free(stack->student_name);
        free(stack);
        return (NULL);
    }
    while (tmp->next != NULL)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    prev->next = NULL;
    free(tmp->student_name);
    free(tmp);
    return (stack);
}

ExamPaper *push(ExamPaper *stack, char *student_name, int student_id, int score)
{
    ExamPaper *new;
    ExamPaper *tmp = stack;
    int len = my_strlen(student_name);
    int i = 0;

    new = malloc(sizeof(ExamPaper));
    new->student_name = (char *)malloc(sizeof(char) * my_strlen(student_name) + 1);
    for (i = 0; i < len; i++)
        new->student_name[i] = student_name[i];
    new->student_name[i] = '\0';
    
    new->student_id = student_id;
    new->score = score;
    new->next = NULL;
    printf("Pushed: Student Name: %s, Student ID: %d, Score: %d\n\n", student_name, student_id, score);
    if (stack == NULL)
        return (new);
    else 
    {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new;
    }
    return (stack);
}


int main()
{
    ExamPaper *stack = NULL;
    //push and display
    stack = push(stack, "Omer", 123, 90);
    display(stack);

    //push and display
    stack = push(stack, "Faruk", 456, 80);
    display(stack);
    
    //push and display
    stack = push(stack, "Olkay", 789, 70);
    display(stack);

    //pop and display
    stack = pop(stack);
    display(stack);

    //pop and display
    stack = pop(stack);
    display(stack);

    //pop and display
    stack = pop(stack);
    display(stack);

    return (0);
}