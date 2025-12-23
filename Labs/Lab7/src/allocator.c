#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "dlist.h"
#include "dnode.h"
#include "allocator.h"

#define SIZE_MAX 1000000

struct Allocator *allocator = NULL;


int allocator_init(size_t size){

    void* memory = malloc(size);
    //check for error in allocation
    if(memory == NULL){
        return -1;
    }

    //initialize allocator

    //create free & allocator list
    allocator->free_list = dlist_create();
    allocator->allocated_list = dlist_create();

    //initialize single node in free_list
    Block *free_block = (Block *)memory;
    free_block->size = size- sizeof(Block);
    free_block->free = true;
    dlist_add_front(allocator->free_list, free_block);

    return 0;
}

void *allocate(size_t size){


    /*
     *1 = first fit
     *2 = worst fit
     *3 = best fit
     */
    int type = 1;
    void * return_Val = NULL;

    if(type ==1){

        return_Val=first_fit(size);
    }else if(type ==2){
        return_Val=worst_fit(size);

    }else{
        return_Val=best_fit(size);
    }

    return return_Val;

}


void *first_fit(size_t size){

    struct dnode *current = allocator->free_list->front;
    while(current != NULL){

        Block *block = (Block *)current->data;
        if(block->free && block->size >= size){

            if(block->size > size+sizeof(Block)){

                Block *new_block = (Block *)((char *)block + size + sizeof(Block));
                new_block->size = block->size -size - sizeof(Block);
                new_block->free = true;
                dlist_add_back(allocator->free_list, new_block);
            }
            block ->size = size;
            block->free = false;

            dlist_find_remove(allocator->free_list, block);
            dlist_add_back(allocator->allocated_list, block);

            return (void *)(block +1);
        }
        current = current->next;
    }
    return NULL;

}

void *best_fit(size_t size){

    struct dnode *current = allocator->free_list->front;
    struct dnode *best_fit_node = NULL;
    size_t best_fit_size = SIZE_MAX;

    while(current != NULL){

        Block *block=(Block *)current->data;
        if(block->free && block->size >= size && block->size < best_fit_size){

            best_fit_size = block->size;
            best_fit_node = current;
        }
        current = current->next;
    }

    if(best_fit_node != NULL){

        Block *block = (Block *)best_fit_node->data;

        if(block->size > size+ sizeof(Block)){

            Block *new_block = (Block *)((char *)block + size +sizeof(Block));
            new_block->size = block->size - size - sizeof(Block);
            new_block->free = true;
            dlist_add_back(allocator->free_list, new_block);

        }

        block->size= size;
        block->free = false;

        dlist_find_remove(allocator->free_list, block);
        dlist_add_back(allocator->allocated_list, block);

        return (void *)(block +1);
    }
    return NULL;
}

void *worst_fit(size_t size){

    struct dnode *current = allocator->free_list->front;
    struct dnode *worst_fit_node = NULL;
    size_t worst_fit_size = 0;

    while(current != NULL){

        Block *block= (Block *)current->data;
        if (block->free && block->size >= size && block->size > worst_fit_size){

            worst_fit_size = block->size;
            worst_fit_node = current;
        }
        current = current->next;
    }

    if(worst_fit_node != NULL){

        Block *block = (Block *)worst_fit_node->data;

        if(block->size > size + sizeof(Block)){

            Block *new_block = (Block *)((char *)block +size+ sizeof(Block));
            new_block->size = block->size - size - sizeof(Block);
            new_block->free = true;
            dlist_add_back(allocator->free_list, new_block);
        }

        block->size = size;
        block->free = false;

        dlist_find_remove(allocator->free_list, block);
        dlist_add_back(allocator->allocated_list, block);

        return (void *)(block +1); 
    }
    return NULL;
}

int deallocate(void *ptr){

    struct dnode *current = allocator->allocated_list->front;

    while(current != NULL){

        Block *block = (Block *)current->data;

        if((void *)(block +1) == ptr){

            dlist_find_remove(allocator->allocated_list, block);
            block->free = true;

            dlist_add_back(allocator->free_list, block);

            return 0;
        }

        current = current->next;
    }

    return -1;
}
