#pragma once

#include<stdio.h>
#include "../types.h"

typedef struct arraylist {
    size_t len;
    size_t capacity;
    size_t item_size;
    void *items;
} Arraylist;

Arraylist *arraylist_create(size_t item_size, size_t initial_capacity);
size_t arraylist_append(Arraylist *list, void *item);
void *arraylist_get(Arraylist *list, size_t index);
u8 arraylist_remove(Arraylist *list, size_t index);
