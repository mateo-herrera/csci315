
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
#include "circular_list.h" 
#include <semaphore.h>
#include <pthread.h>

int circular_list_create(struct circular_list *l, int size) {
  l->buffer = calloc(size, sizeof(item));
  l->start = -1;
  l->end = -1;
  l->elems = 0;
  l->size = size;

  //initialize mutex & semaphores
  sem_init(&l->empty_sem,0, size);
  sem_init(&l->full_sem,0,0);
  pthread_mutex_init(&l->lock, NULL);

  return 0;
}

int circular_list_insert(struct circular_list *l, item i) {

    //decrement empty sem
    sem_wait(&l->empty_sem);

    //lock mutex
    pthread_mutex_lock(&l->lock);

    //checks for full list
    if(l->elems == l->size){
        //unlock mutex
        pthread_mutex_unlock(&l->lock);
        //increment empty_sem
        sem_post(&l->empty_sem);
        return -1;
    }

    //checks if list is empty
    if(l->elems == 0){
        l->start = 0;
        l->end = 0;
    }else{
    
        l->end = (l->end +1)% l->size;
    }

    //insert item at end
    l->buffer[l->end] = i;
    l->elems++;

    //unlock mutex
    pthread_mutex_unlock(&l->lock);
    //increment full_sem
    sem_post(&l->full_sem);


    return 0;
}

int circular_list_remove(struct circular_list *l, item *i) {
  
    //decrement full semaphore
    sem_wait(&l->full_sem);

    //locks mutex
    pthread_mutex_lock(&l->lock);

    //checks if empty
    if(l->elems ==0){
        //unlocks mutex
        pthread_mutex_unlock(&l->lock);
        //increment full semaphore
        sem_post(&l->full_sem);
        return -1;
    }

    //get first item in list
    *i= l->buffer[l->start];

    //checks if one element in list
    
    if(l->elems == 1){
        l->start = -1;
        l->end = -1;
    }else{
    
        l->start = (l->start +1) % l->size;
    }

    //decrement element count
    l->elems--;

    //unlock mutex
    pthread_mutex_unlock(&l->lock);
    //increment empty semaphore
    sem_post(&l->empty_sem);

    return 0;
}
