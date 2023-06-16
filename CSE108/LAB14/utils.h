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