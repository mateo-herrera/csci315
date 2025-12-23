#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3


void *thread1_Func(void *arg);

void *thread2_Func(void *arg);

void *thread3_Func(void *arg);



void *thread1_Func(void *arg){


    int num =0;
    while(1){

        printf("%d",num);
        if(num == 9){

            num = 0;
        }else{

            num ++;
        }
        int sum =0;
        for(int i=0;i<1000000;i++){

            sum +=i;
        }

    }
}

void *thread2_Func(void *arg){

    char letter = 'a';

    while(1){

        printf("%c",letter);

        if(letter == 'z'){

            letter = 'a';
        }else{

            letter ++;
        }
        
        int sum=0;
        for(int i=0;i<1000000;i++){

            sum +=i;
        }
    }
}



void *thread3_Func(void *arg){

    while(1){

        printf("#\n");
    
    
        int sum=0;

        for(int i=0;i<1000000;i++){

            sum += i;
        }
    }
}


int main(int argc, char *argv[])
{

    pthread_t threads[NUM_THREADS];



    //create first thread
    if(pthread_create(&threads[0], NULL, thread1_Func, NULL) != 0){

        perror("Thread 1 failed");
        return 1;
    }

    if (pthread_create(&threads[1], NULL, thread2_Func, NULL) != 0){

        perror("Thread 2 failed");
        return 1;
    }

    if(pthread_create(&threads[2], NULL, thread2_Func, NULL) != 0){

        perror("Thread 3 failed");
        return 1;
    }

    
    for(int i=0; i<NUM_THREADS;i++){
        pthread_join(threads[i], NULL);

    }

    return 0;
}



