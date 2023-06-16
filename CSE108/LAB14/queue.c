#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct s_order
{
    char *customer_name;
    int order_id;
    time_t order_time;
    char *items;
    struct s_order *next;
}Order;

int my_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void updateOrder(Order *list, int order_id, char *new_items)
{
    Order *tmp;
    int len = my_strlen(new_items);

    tmp = list;

    while (tmp != NULL)
    {
        if (tmp->order_id == order_id)
        {
            free(tmp->items);
            tmp->items = (char *)malloc(sizeof(char) * len + 1);
            for (int i = 0; i < len; i++)
                tmp->items[i] = new_items[i];
            tmp->items[len] = '\0';
            printf("Updated order: Order ID: %d, Customer Name: %s, Items: %s,\n\n", order_id, tmp->customer_name, new_items);
            return ;
        }
        tmp = tmp->next;
    }
    printf("Order id not found\n");
}

Order *dequeue(Order *list, time_t thresholdTime)
{
    Order *tmp;
    Order *prev;

    tmp = list;
    if (list == NULL)
        return (NULL);
    if (list->next == NULL)
    {
        free(list->customer_name);
        free(list->items);
        free(list);
        return (NULL);
    }
    while (tmp->next != NULL)
    {
        prev = tmp;
        if (prev->order_time < thresholdTime)
        {
            printf("Dequeued(OLD ORDER): Order ID: %d, Customer Name: %s, Items: %s, Order Time: %s\n\n", prev->order_id, prev->customer_name, prev->items, ctime(&prev->order_time));
            free(prev->customer_name);
            free(prev->items);
            free(prev);
        }
        tmp = tmp->next;
    }
    prev->next = NULL;
    printf("Dequeued: Order ID: %d, Customer Name: %s, Items: %s, Order Time: %s\n\n", tmp->order_id, tmp->customer_name, tmp->items, ctime(&tmp->order_time));
    free(tmp->customer_name);
    free(tmp->items);
    free(tmp);
    return (list);
}

void display(Order *list)
{
    Order *tmp;

    tmp = list;
    printf("ORDERS IN THE QUEUE:\n");
    if (list == NULL)
    {
        printf("No orders in the queue\n\n");
        return ;
    }
    while (tmp != NULL)
    {
        printf(" # Order id: %d, ", tmp->order_id);
        printf("Customer name: %s, ", tmp->customer_name);
        printf("Items: %s, ", tmp->items);
        printf("Order time: %s\n\n", ctime(&tmp->order_time));
        tmp = tmp->next;
    }
}

Order *enqueue(Order *list, char *customer_name, int order_id, char *items, time_t order_time)
{
    Order *new_order = NULL;
    Order *tmp = NULL;
    int len = my_strlen(customer_name);
    int len2 = my_strlen(items);
    int i = 0;

    printf("Enqueud: Order ID: %d, Customer Name: %s, Items: %s, Order Time: %s\n\n", order_id, customer_name, items, ctime(&order_time));
    new_order = (Order *)malloc(sizeof(Order));
    new_order->customer_name = (char *)malloc(sizeof(char) * my_strlen(customer_name) + 1);
    new_order->items = (char *)malloc(sizeof(char) * my_strlen(items) + 1);
    if (new_order == NULL)
        return (NULL);
    //strcopy
    for (i = 0; i < len; i++)
        new_order->customer_name[i] = customer_name[i];
    new_order->customer_name[i] = '\0';
    //strcopy
    for (i = 0; i < len2; i++)
        new_order->items[i] = items[i];
    new_order->items[i] = '\0';
    //strcopy

    new_order->order_time = order_time;
    new_order->order_id = order_id;
    new_order->next = NULL;
    tmp = list;
    if (list == NULL)
        return (new_order);
    else
    {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new_order;
    }
    return (list);
}

void serializeFIFO(Order *list, const char *filename)
{
    FILE *fp;

    fp = fopen(filename, "wb");
    if (!fp)
        return ;

    while (list)
    {
        fwrite(list, sizeof(Order), 1, fp);
        list = list->next;
    }
    printf("## Queue data structure serialized to binary file. ##\n\n");
    fclose(fp);
}

Order *deserializeFIFO(const char *filename)
{
    FILE *fp;

    fp = fopen(filename, "rb");
    if (!fp)
        return (NULL);
    
    Order *tmp = (Order *)malloc(sizeof(Order));
    Order *new_queue = NULL;
    while (fread(tmp, sizeof(Order), 1, fp))
    {
        new_queue = enqueue(new_queue, tmp->customer_name, tmp->order_id, tmp->items, tmp->order_time);
    }
    fclose(fp);
    if (tmp)
    {
        free(tmp->customer_name);
        free(tmp->items);
        free(tmp);
    }
    printf("## Queue data structure deserialized from binary file. ##\n\n");
    return (new_queue);
}

int main()
{
    Order *list = enqueue(list, "Omer", 1, "Burger", time(NULL));
    Order *tmp = NULL;
    list = enqueue(list, "Faruk", 2, "Pizza", time(NULL));
    list = enqueue(list, "Olkay", 3, "Hotdog", time(NULL));
    list = enqueue(list, "Burak", 4, "Sandwich, Fries, Water", time(NULL));
    display(list);
    serializeFIFO(list, "fifo_data.bin");
    printf("\n\nDESERIALIZING QUEUE\n\n");
    tmp = deserializeFIFO("fifo_data.bin");
    printf("DESERIALIZED NEW QUEUE:\n\n");
    display(tmp);
    printf("-------------------\n\n");
    dequeue(tmp, time(NULL));
    return (0);
}