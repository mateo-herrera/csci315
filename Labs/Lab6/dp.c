#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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
        printf("Philosopher %lld is starting to eat.\n", philosopher_id);
        //eats for random time 0-1 seconds
        napping(1, &seed);

        printf("Philosopher %lld is done eating.\n", philosopher_id);
    }

    return NULL;
}

int main() {
    //philosopher threads
    pthread_t philosophers[5];
    int i;

    //create philospher threads
    for (i = 0; i < 5; i++) {
        //use philosopher ID as arg
        if (pthread_create(&philosophers[i], NULL, Philosopher, (void *)(long long)i) != 0) {
            perror("Error creating thread");
            return 1;
        }
    }

    //joins philosopher threads
    for (i = 0; i < 5; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

