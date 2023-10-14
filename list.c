#include "list.h"
#include "stdbool.h"
#include "stddef.h"
#include <stdlib.h>
#include <string.h>



typedef struct list_info {
    struct list *point;
    size_t offset;
    size_t size;
    size_t length;

    struct list *index;
    void *condition_func;
    size_t allowance;
}list_info;

static inline bool __list_add(void *dest, void *node);

void *list_create_(size_t offset, size_t size)
{
    struct list_info * ptr = calloc(1, sizeof(struct list_info));
    if (!ptr)
    {
        return NULL;
    }

    ptr->index = NULL;
    ptr->length = 0;
    ptr->offset = offset;
    ptr->point = NULL;
    ptr->size = size;
    ptr->condition_func = NULL;
    
    return ptr;
}
bool list_destroy(void *list, void (*destroy)(void *))
{
    list_info *info = list;
    long long int i = info->length;
    struct list **ptr = &(info->point);
    struct list *temp = NULL;

    while (i > 0)
    {
        temp = (*ptr)->next;
        destroy(get_node_addr(*ptr, info->offset));
        free(get_node_addr(*ptr, info->offset));
        *ptr = temp;
        i--;
    } 
    free(list);
    return true;
}

size_t list_length(void *ptr)
{
    return ((list_info *)ptr)->length;
}

static inline bool __list_add(void *dest, void *node)
{
    struct list *d = dest;
    struct list *s = node;
    s->next = d->next;
    d->next->prev = s;
    s->prev = d;
    d->next = s;

    return true;
}

// bool list_append(void *node, void *list, void *dest)
// {
    
// }
bool list_insert(void *node, void *list, void *dest)
{
    list_info *info = (list_info *)list;

    void *obj = malloc(info->size);
    if (!obj)
    {
        return false;
    }
    memcpy(obj, node, info->size);

    if (info->length == 0)
    {
        info->point = (struct list *)(obj + info->offset);
        info->point->next = info->point;
        info->point->prev = info->point;
        
        goto result; 
    }

    if (dest != NULL)
    {
        __list_add(dest + info->offset, obj + info->offset);

        goto result;
    }

    __list_add(info->point, obj + info->offset);

 result:
    info->length++;
    return true;
}
bool list_delete(void *node, void *list, void (*delete)(void *))
{
    list_info *info = list;
    struct list *ptr = node + info->offset;

    if (info->length == 0) return false;

    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;
    info->length --;
    delete(node);
    
    free(node);
    return true;
}
void *list_search(void *list, bool (*condition)(void *, void *), void *dest)
{
    list_info *info = list;
    long long int i = info->length;
    struct list **ptr = &(info->point);

    if ((void *)condition == info->condition_func)
    {
        i = info->allowance;
        i && (ptr = &(info->index));
    }

    while (i > 0)
    {
        if (condition(dest, get_node_addr(*ptr, info->offset)) == true) break;

        ptr = &((*ptr)->next);
        i--;
    } 

    if (i <= 0) return NULL;
    
    info->index = (info->length != 1) ? (get_node_addr((*ptr)->next, info->offset)) : NULL;
    info->allowance = i - 1;
    
    return get_node_addr(*ptr, info->offset);
}
void list_print(void *list, void (*print)(void *))
{
    list_info *info = list;
    long long int i = info->length;
    struct list **ptr = &(info->point);

    while (i > 0)
    {
        print(get_node_addr((*ptr), info->offset));
        ptr = &((*ptr)->next);
        i--;
    }    
}

