#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_order
{
    char *customer_name;
    int order_id;
    char *order_time;
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

Order *dequeue(Order *list)
{
    Order *tmp;
    Order *prev;

    tmp = list;
    if (list == NULL)
        return (NULL);
    if (list->next == NULL)
    {
        free(list->customer_name);
        free(list->order_time);
        free(list->items);
        free(list);
        return (NULL);
    }
    while (tmp->next != NULL)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    prev->next = NULL;
    printf("Dequeued: Order ID: %d, Customer Name: %s, Items: %s, Order Time: %s\n\n", tmp->order_id, tmp->customer_name, tmp->items, tmp->order_time);
    free(tmp->customer_name);
    free(tmp->order_time);
    free(tmp->items);
    free(tmp);
    return (list);
}

void display(Order *list)
{
    Order *tmp;

    tmp = list;
    printf("ORDERS IN THE QUEUE:\n");
    if (tmp == NULL)
    {
        printf("No orders in the queue\n\n");
        return ;
    }
    while (tmp != NULL)
    {
        printf(" # Order id: %d, ", tmp->order_id);
        printf("Customer name: %s, ", tmp->customer_name);
        printf("Items: %s, ", tmp->items);
        printf("Order time: %s\n\n", tmp->order_time);
        tmp = tmp->next;
    }
}

Order *enqueue(Order *list, char *customer_name, int order_id, char *items, char *order_time)
{
    Order *new_order;
    Order *tmp;
    int len = my_strlen(customer_name);
    int len2 = my_strlen(items);
    int len3 = my_strlen(order_time);
    int i = 0;

    printf("Enqueud: Order ID: %d, Customer Name: %s, Items: %s, Order Time: %s\n\n", order_id, customer_name, items, order_time);
    new_order = (Order *)malloc(sizeof(Order));
    new_order->customer_name = (char *)malloc(sizeof(char) * my_strlen(customer_name) + 1);
    new_order->items = (char *)malloc(sizeof(char) * my_strlen(items) + 1);
    new_order->order_time = (char *)malloc(sizeof(char) * my_strlen(order_time) + 1);
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
    for (i = 0; i < len3; i++)
        new_order->order_time[i] = order_time[i];
    new_order->order_time[i] = '\0';

    new_order->order_id = order_id;
    new_order->next = NULL;
    if (list == NULL)
        return (new_order);
    tmp = new_order;
    tmp->next = list;
    list = tmp;
    return (list);
}

int main()
{
    Order *list = enqueue(list, "Omer", 1, "Burger", "12:00");
    list = enqueue(list, "Faruk", 2, "Pizza", "12:01");
    list = enqueue(list, "Olkay", 3, "Hotdog", "12:02");
    list = enqueue(list, "Burak", 4, "Sandwich, Fries, Water", "12:03");
    display(list);
    list = dequeue(list);
    display(list);
    list = dequeue(list);
    display(list);
    return (0);
}