#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_PHILOSPHERS 5
#define NUM_CHOPSTICKS 5

//Chopstick mutexs
pthread_mutex_t chopstick_mutexs[NUM_CHOPSTICKS];

void napping(int t, unsigned int *seed) {
    //generates randomtime in microseconds
    int sleep_time = rand_r(seed) % (t * 1000000);
    
    usleep(sleep_time);
}

void *Philosopher(void *id) {
    unsigned int seed = time(NULL);
    //convert void* to long long for ID
    long long philosopher_id = (long long)id;


    while (1) {
        printf("Philosopher %lld is thinking.\n", philosopher_id);
        //thinks for randomtime 0-2 seconds
        napping(2, &seed);

        printf("Philosopher %lld is hungry.\n", philosopher_id);


        //even id left chopstick first then right
        if(philosopher_id%2==0){
            //locks first chopstick
            pthread_mutex_lock(&chopstick_mutexs[philosopher_id]);
            printf("Philosopher %lld picking up chopstick %lld.\n",philosopher_id,philosopher_id);
            //Naps to cause deadlock
            napping(2,&seed);
            //locks second chopstick
            pthread_mutex_lock(&chopstick_mutexs[(philosopher_id+1)%5]);
            printf("Philosopher %lld picking up chopstick %lld.\n",philosopher_id,(philosopher_id+1)%5);
        //Odd Id right chopstick first then left
        }else{

            //locks secod chopstick
            pthread_mutex_lock(&chopstick_mutexs[(philosopher_id+1)%5]);
            printf("Philosopher %lld picking up chopstick %lld.\n",philosopher_id,(philosopher_id+1)%5);

            //Naps to cause deadlock
            napping(2,&seed);
            
            //locks first chopstick
            pthread_mutex_lock(&chopstick_mutexs[philosopher_id]);
            printf("Philosopher %lld picking up chopstick %lld.\n",philosopher_id,philosopher_id);

        }

        printf("Philosopher %lld is starting to eat.\n", philosopher_id);
        //eats for random time 0-1 seconds
        napping(1, &seed);
        printf("Philosopher %lld is done eating.\n", philosopher_id);

        //unlock chopsticks
        pthread_mutex_unlock(&chopstick_mutexs[philosopher_id]);
        printf("Philosopher %lld putting down chopstick %lld.\n",philosopher_id,philosopher_id);
        pthread_mutex_unlock(&chopstick_mutexs[(philosopher_id+1)%5]);
        printf("Philosopher %lld putting down chopstick %lld.\n",philosopher_id, (philosopher_id+1)%5);

    }

    return NULL;
}

int main() {
    //philosopher threads
    pthread_t philosophers[NUM_PHILOSPHERS];


    //initialize mutexs to default
    for(int i=0;i<NUM_CHOPSTICKS;i++){
        if(pthread_mutex_init(&chopstick_mutexs[i],NULL) !=0){
            perror("Error initializing mutex");
        }
    }

    //create philospher threads
    for (int i = 0; i < NUM_PHILOSPHERS; i++) {
        //use philosopher ID as arg
        if (pthread_create(&philosophers[i], NULL, Philosopher, (void *)(long long)i) != 0) {
            perror("Error creating thread");
            return 1;
        }
    }

    //joins philosopher threads
    for (int i = 0; i < NUM_PHILOSPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    //destroy mutexs
    for(int i=0; i<NUM_CHOPSTICKS;i++){
        if(pthread_mutex_destroy(&chopstick_mutexs[i]) !=0){
            perror("Mutex destruction failed");
        }
    }

    return 0;
}

