#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "dlist.h"
#include "dnode.h"


typedef struct Block{

    size_t size;
    bool free;
}Block;

typedef struct Allocator{

    struct dlist *free_list;
    struct dlist *allocated_list;
}Allocator;

int allocator_init(size_t size);
void *allocate(size_t size);
int deallocate(void *ptr);
void *first_fit(size_t size);
void *worst_fit(size_t size);
void *best_fit(size_t size);


#endif
