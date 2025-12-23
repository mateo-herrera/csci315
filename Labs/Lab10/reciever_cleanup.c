#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>

#define SEM_NAME "/mh065"

/*
 * File to run after use of sender and reciever files to ensure semaphore was unlinked properly
 */

int main(int argc, char *argv[]){

    sem_unlink(SEM_NAME);

    printf("Semaphore removed\n");

    return 0;
}
