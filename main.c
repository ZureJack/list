#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define LIST_DEBUG
#include "list.h"
typedef struct type {
    char *str;
    int i;
    struct list l;
} type;

#define MAX 10
void print(void *node)
{
    type *n = node;
    printf("%d: %s\n", n->i, n->str);
}
bool condition(void *dest, void *src)
{
    type *d = dest;
    type *s = src;
    if (s->i == d->i)
    {
        return true;
    }
    return false;
}
void destroy(void *node)
{
    
}
int main(int argc, char *argv[])
{
    type *list = list_create(type, l);
    type node = {.str = "hello", .i = 0};
    list_instert(&node, list, NULL);
    for (int i = 0; i < MAX; i++)
    {
        node.str = "dd";
        node.i = i + 1;
        list_instert(&node, list, NULL);
    }
    list_print(list, &print);
    node.i = 1;
    void *temp = list_search(list, &condition, &node);
    printf("debug\n");
    list_delete(temp, list);
    printf("############################################\n");
    list_print(list, &print);
    node.i = 1;
    temp = list_search(list, &condition, &node);
    if (temp != NULL)
    {
        list_delete(temp, list);
    }
    
    node.i = 100;
    list_instert(&node, list, NULL);
    list_print(list, &print);
    list_destroy(list, &destroy);
    

    return 0;
}