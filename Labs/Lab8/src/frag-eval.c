/*
 * Test some basic memory allocatino functions.
 * CSCI 315
 * For lab checks.
 */
#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"
#include "dlist.h"



int main(int argc, char*argv[]) {

  int r = allocator_init(1024);
  if (r == -1) {
    printf("allocate init failed\n");
    exit(1);
  }

  printf("attempting to allocate memory blocks ...\n");

  int algorithm;
  unsigned int seed;
  int requests;

  if(argc == 4){

      algorithm = atoi(argv[1]);
      char *ptr;
      seed = (unsigned int)strtoul(argv[2], &ptr, 10);
      requests = atoi(argv[3]);

  }else{

      printf("You need 3 arguements: algorithm, seed, and requests");
      return -1;
  }
  
  srandom(seed);

  for (int i = 0; i < requests; i ++)  { // try allocation operations
    
      int operation_type = rand() %2;

      if(operation_type == 0){

          //allocates 
          ssize_t size = (rand() % (1000 -100 +1))+100;
          void *ptr = allocate(algorithm, size);
      }else{

          //deallocates
          struct Allocator *allocator_instance = get_allocator_instance();
          if(allocator_instance->allocated_list->front !=NULL){

              struct dnode *node = allocator_instance->allocated_list->front;
              Block *block = (Block *)node ->data;

              deallocate((void *)(block+1));
          }
      }
    }

  printf("Average fragmentation: %f\n", average_frag()/requests);




  return 0;
}
