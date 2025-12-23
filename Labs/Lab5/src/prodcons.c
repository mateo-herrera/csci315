/*
 * Copyright (c) 2013 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <unistd.h>
#include <pthread.h>

#include "circular_list.h" 

/* SCALE_FACTOR is a constant for you to experiment with:
 * if you choose a very large SCALE_FACTOR, your threads
 * might spend a long time sleeping. If you choose it to be
 * too small, your threads will not sleep at all. Note
 * that in the producer and consumer functions, the sleep
 * time is computed as the INTEGER DIVISION below:
 *
 *  usleep(SCALE_FACTOR * rand_r(&seed) / RAND_MAX)
 *
 *  where RAND_MAX is the largest random number returned
 *  by rand_r. There are potential problems here in this computation,
 *  for example, it is possible that the value computed will be out 
 *  of range or will become zero.
 *
 *  Please make sure you think through this issue and revise
 *  the code so that a correct and meaningful value can be
 *  generated for the desired effect.
 *  
 *  You are responsible to come up with a correct solution.
 */
#define SCALE_FACTOR 1000
#define MAX_SLEEP_TIME 1000000
#define MIN_SLEEP_TIME 1

// global variables -----------------------

struct circular_list mylist;

typedef struct{
    unsigned int seed_id;
    int thread_id;
 } thread_args;


// end of global variables ----------------

void *producer (void *param) {
  item i;
  thread_args *args = (thread_args *)param;

  int n=0;
  //for (;;) {
  while(n<100){
    n++;
    /* The following solution to compute the amount of time to sleep
	 * is incorrect. You MUST fix it. See the "SCALE_FACTOR ..." comment
	 * section above.
	 */ 
 
    unsigned int random_num;
    


    random_num = rand_r(&args->seed_id);

    unsigned int sleep_time = SCALE_FACTOR * random_num / RAND_MAX;
    //Ensures sleep_time isn't too small or too big
    if(sleep_time < MIN_SLEEP_TIME){
        sleep_time = MIN_SLEEP_TIME;
    }else if( sleep_time > MAX_SLEEP_TIME){
        sleep_time = MAX_SLEEP_TIME;
    }

    // sleep for random period of time
    usleep(sleep_time); 

    random_num = rand_r(&args->seed_id);
    // generate a random number
    i = (item) (((double) random_num) / RAND_MAX);
    printf("Random number generated: %d\n",random_num);

    if (circular_list_insert(&mylist, i) == -1) {
      printf("PRODUCER: error condition\n");
    } else {
      printf("PRODUCER(%d): produced value %lf\n",args->thread_id, i);
    }
    fflush(stdout);
  }

  return NULL;
}

void *consumer (void *param) {
  item i;
  thread_args *args = (thread_args *)param;
  
  //for (;;) {
  int n=0;
  while(n<100){
    n++;
    unsigned int random_num = rand_r(&args->seed_id);
    unsigned int sleep_time = SCALE_FACTOR * random_num / RAND_MAX;
    
    if(sleep_time < MIN_SLEEP_TIME){
        sleep_time = MIN_SLEEP_TIME;
    }else if (sleep_time > MAX_SLEEP_TIME){
        sleep_time = MAX_SLEEP_TIME;
    }

    // sleep for random period of time
    usleep(sleep_time);

    if (circular_list_remove(&mylist, &i) == -1) {
      printf("CONSUMER: error condition\n");
    } else {
      printf("CONSUMER(%d): consumed value %lf\n",args->thread_id, i);
    }
    fflush(stdout);
  }

  return NULL;
}

int main (int argc, char *argv[]) {

  // get command line arguments
  
  // if error in command line argument usage, terminate with helpful
  // message

    
    if(argc != 4){
    
        fprintf(stderr,"prodocons [num_prod][num_cons][sleep_time]");
        return -1;
    }

    int num_prod = atoi(argv[1]);
    int num_cons = atoi(argv[2]);
    int sleep_time = atoi(argv[3]);

    if(num_prod <=0 || num_cons <=0 || sleep_time <=0){
        fprintf(stderr, "Error, parameters must be positive");
        return -1;
    }



  // initialize buffer
  circular_list_create(&mylist, 20);
  
  // create producer thread(s)
  pthread_t producers[num_prod];


  for(int i=0; i<num_prod; i++){

      thread_args *arg1 = malloc(sizeof(thread_args));
      arg1->seed_id = i;
      arg1->thread_id = i;
      pthread_create(&producers[i],NULL, producer,(void *)arg1);
  }

  // create consumer thread(s)
  pthread_t consumers[num_cons];

  for(int i=0; i<num_cons;i++){

      thread_args *arg2 = malloc(sizeof(thread_args));
      arg2->seed_id = i;
      arg2->thread_id = i;
      pthread_create(&consumers[i], NULL, consumer,(void *)arg2);
  }

  // sleep to give time for threads to run
  sleep(sleep_time);

  for(int i=0;i<num_prod;i++){
    pthread_join(producers[i], NULL);
  }

  for(int i=0;i<num_cons;i++){
    pthread_join(consumers[i], NULL);
  }

  // exit
  return (0);
}
