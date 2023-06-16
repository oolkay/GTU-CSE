#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NORMAL 1
#define VETERAN 2
#define OD 3
#define VIP 4

typedef struct customer
{
    char *name;
    int age;
    char *p_group_name;
    int p_level;
    struct customer *next;
    struct customer *prev;
}Customer;

void search_customer(Customer *pqueue, char *name)
{
    if (pqueue == NULL)
    {
        printf("Customer not found\n");
        return ;
    }
    if (strcmp(pqueue->name, name) == 0)
    {
        printf("Name: %s Age: %d Group: %s Level: %d\n", pqueue->name, pqueue->age, pqueue->p_group_name, pqueue->p_level);
        return ;
    }
    else
        search_customer(pqueue->next, name);
}


void queue_to_file(Customer *pqueue)
{
    FILE *fp;
    fp = fopen("customers.txt", "r+");
    if (!fp)
        return;
    while (pqueue)
    {
        fprintf(fp, "%s %d %s %d", pqueue->name, pqueue->age, pqueue->p_group_name, pqueue->p_level);
        if (pqueue->next)
            fprintf(fp, "\n");
        pqueue = pqueue->next;
    }
    fclose(fp);
}

void display_customer(Customer *pqueue)
{
    if (!pqueue)
        printf("No customers\n");
    while (pqueue)
    {
        printf("Name: %s Age: %d Group: %s Level: %d\n", pqueue->name, pqueue->age, pqueue->p_group_name, pqueue->p_level);
        pqueue = pqueue->next;
    }
}

Customer *remove_customer(Customer *pqueue, char *name)
{
    Customer *tmp;
    Customer *head = pqueue;
    while (pqueue)
    {
        if (strcmp(pqueue->name, name) == 0)
        {
            if (pqueue->prev == NULL && pqueue->next == NULL)
            {
                free(pqueue);
                return (NULL);
            }
            else if (pqueue->prev && pqueue->next)
            {
                tmp = pqueue;
                pqueue->prev->next = pqueue->next;
                pqueue->next->prev = pqueue->prev;
                free (tmp);
                return (head);
            }
            else if (pqueue->prev == NULL)
            {
                tmp = pqueue;
                pqueue = pqueue->next;
                pqueue->prev = NULL;
                free(tmp);
                return (pqueue);
            }
            else if (pqueue->next == NULL)
            {
                tmp = pqueue;
                pqueue = pqueue->prev;
                pqueue->next = NULL;
                free(tmp);
                return (head);
            }
        }
        else
            pqueue = pqueue->next;
    }
    return (pqueue);
}

Customer *insert_customer(Customer *pqueue, char *name, int age, char *p_group_name, int p_level)
{
    Customer *new = (Customer *)malloc(sizeof(Customer));
    new->name = strdup(name);
    new->age = age;
    new->p_group_name = strdup(p_group_name);
    new->p_level = p_level;
    new->next = NULL;
    new->prev = NULL;
    if (!pqueue)
        return new;
    else
    {
        Customer *tmp;
        Customer *head = pqueue;
        while (p_level <= pqueue->p_level && pqueue->next != NULL)
            pqueue = pqueue->next;
        if (pqueue->prev == NULL)
        {
            pqueue->prev = new;
            new->next = pqueue;
            return (new);
        }
        else if (pqueue->next == NULL && p_level <= pqueue->p_level)
        {
            pqueue->next = new;
            new->prev = pqueue;
            return (head);
        }
        else if (pqueue->next == NULL && p_level > pqueue->p_level)
        {
            tmp = pqueue;
            pqueue->prev->next = new;
            new->prev = pqueue->prev;
            new->next = pqueue;
            tmp->prev = new;
            return (head);
        }
    }
}

Customer *change_priority(Customer *pqueue, char *name, int new_level)
{
    Customer *tmp;
    Customer *head = pqueue;
    while (pqueue)
    {
        if (strcmp(pqueue->name, name) == 0)
        {
            if (pqueue->p_level == new_level)
                return (head);
            if (pqueue->prev)
                pqueue->prev->next = pqueue->next;
            if (pqueue->next)
                pqueue->next->prev = pqueue->prev;
            tmp = pqueue;
            switch (new_level)
            {
                case 1:
                    pqueue = insert_customer(pqueue, tmp->name, tmp->age, "NORMAL", new_level);
                    break;
                case 2:
                    pqueue = insert_customer(pqueue, tmp->name, tmp->age, "VETERAN", new_level);
                    break;
                case 3:
                    pqueue = insert_customer(pqueue, tmp->name, tmp->age, "OD", new_level);
                    break;
                case 4:
                    pqueue = insert_customer(pqueue, tmp->name, tmp->age, "VIP", new_level);
                    break;
            }
            free(tmp);
            return (pqueue);
        }
        else
            pqueue = pqueue->next;
    }
    return (pqueue);

}

Customer *read_from_file(Customer *pqueue)
{
    FILE *fp = fopen("customers.txt", "r");
    char name[20];
    int j = 0;
    int age;
    int level;
    char group[20];
    while (fscanf(fp, "%s %d %s %d", name, &age, group, &level) > 0)
    {
        pqueue = insert_customer(pqueue, name, age, group, level);
    }
    return (pqueue);
    fclose(fp);
}

int main()
{
    Customer *pqueue = NULL;
    int option = 1;
    int i = 0;
    pqueue = read_from_file(pqueue);
    while (option == 1 || option == 2 || option == 3 || option == 4 || option == 5)
    {
        char name[20];
        int age;
        char p_group[20];
        int p_level;
        printf("\n********************\n");
        printf("Welcome the ABC Bank\n\n");
        printf("1. Insert a customer\n");
        printf("2. Remove a customer\n");
        printf("3. Display customers in order\n");
        printf("4. Search a customer\n");
        printf("5. Search priority settings\n");
        printf("6. Exit\n\n");
        printf("Please select an option: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                printf("Plesae enter the customer's name: ");
                scanf(" %[^\n]", name);
                printf("Please enter the customer's age: ");
                scanf("%d", &age);
                printf("Please enter the customer's priority group: ");
                scanf("%s", p_group);
                for (i = 0; i < 4; i++)
                {
                    if (strcmp(p_group, "NORMAL") == 0)
                        p_level = NORMAL;
                    else if (strcmp(p_group, "VETERAN") == 0)
                        p_level = VETERAN;
                    else if (strcmp(p_group, "OD") == 0)
                        p_level = OD;
                    else if (strcmp(p_group, "VIP") == 0)
                        p_level = VIP;
                    else
                    {
                        printf("Invalid input\n");
                        break;
                    }
                }
                pqueue = insert_customer(pqueue, name, age, p_group, p_level);
                printf("Customer Added Succesfully\n");
                queue_to_file(pqueue);
                break; 
            case 2:
                printf("Plesae enter the customer's name: ");
                scanf(" %[^\n]", name);
                pqueue = remove_customer(pqueue, name);
                printf("Customer Removed Succesfully\n");
                queue_to_file(pqueue);
                break;
            case 3:
                display_customer(pqueue);
                break;
            case 4:
                printf("Please enter the customer's name: ");
                scanf(" %[^\n]", name);
                search_customer(pqueue, name);
                break;
            case 5:
                printf("Please enter the customer's name: ");
                scanf(" %[^\n]", name);
                printf("Please enter the customer's new level: ");
                scanf("%d", &p_level);


        }
    }


}