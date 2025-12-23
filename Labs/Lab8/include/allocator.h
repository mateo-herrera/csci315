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

struct Allocator* get_allocator_instance();
int allocator_init(size_t size);
void *allocate(int algorithm, size_t size);
int deallocate(void *ptr);
void *first_fit(size_t size);
void *worst_fit(size_t size);
void *best_fit(size_t size);
/*
 * average_frag simulates allocation and dellocation using a randnumber and if its odd then it deallocated a block and if even it allocates a random size. It then traverses through the memory and adds the amount of freesspace and finds the largest freeblock, it also calculates the total fragmention in order to return total fragmentation/ number of calls to deallocate and allocate.
 */
double average_frag();

#endif
