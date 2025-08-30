#include "arraylist.h"
#include "../util.h"
#include <stdlib.h>
#include <string.h>

Arraylist *arraylist_create(size_t item_size, size_t initial_capacity){
    Arraylist *list = malloc(sizeof(Arraylist));
    if(list == NULL)
        ERROR_RETURN(NULL, "Could not allocate memory for Arraylist\n");

    list->item_size = item_size;
    list->capacity = initial_capacity;
    list->len = 0;
    list->items = malloc(item_size * initial_capacity);
    if(list->items==NULL)
        ERROR_RETURN(NULL, "Could not allocat memory for Arraylist-items\n");
    return list;
}

size_t arraylist_append(Arraylist *list, void *item){
    if(list->len == list->capacity){
        list->capacity = (list->capacity > 0) ? (list->capacity * 2) : 1;
        void *items = realloc(list->items, list->item_size * list->capacity);
        if(items==NULL)
            ERROR_RETURN(-1, "Could not append memory for Arraylist");

        list->items = items;
    }

    size_t index = list->len++;
    memcpy((u8*)list->items + index*list->item_size, item, list->item_size);
    return index;
}

void *arraylist_get(Arraylist *list, size_t index){
    if(index>=list->len)
        ERROR_RETURN(NULL, "Index out of bounds\n");

    return (u8*)list->items + index*list->item_size;
}

u8 arraylist_remove(Arraylist *list, size_t index){
    if(list->len==0)
        ERROR_RETURN(1, "list is empty\n");
    if(index>=list->len)
        ERROR_RETURN(1, "Index out of bounds\n");

    if(list->len==1){
        list->len =0;
        return 0;
    }
    
    --(list->len);
    
    u8 *item_ptr = (u8*)list->items + index*list->item_size;
    u8 *end_ptr = (u8*)list->items + list->len*list->item_size;
    memcpy(item_ptr, end_ptr, list->item_size);

    return 0;
}
