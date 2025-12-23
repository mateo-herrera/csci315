#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>

#define SEM_NAME "/mh065"
#define FILE_NAME "Channel.txt"

int main(int argc, char *argv[]){


    //checks for right amount of args
    if(argc !=2){
        printf("Usage: %s \"[text]\"\n",argv[0]);
        exit(1);
    }

    //gets length of message
    ssize_t length = strlen(argv[1]);
    
    //initializes text with length of message
    char text[length];
    strncpy(text, argv[1],length);
    text[length]='\0';

    //create/open semaphore
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if(sem == SEM_FAILED){
        perror("Semaphore");
        exit(1);
    }

    sem_wait(sem);
    //critical section

    //opens file
    int fd = open(FILE_NAME, O_WRONLY | O_CREAT, 0644);
    
    if(fd == -1){
        perror("open");
        sem_post(sem);
        sem_close(sem);
        sem_unlink(SEM_NAME);
        exit(1);

    }

    //writes msg to txt file
    if(write(fd, text, length) == -1){
        perror("write");
        close(fd);
        sem_post(sem);
        sem_close(sem);
        sem_unlink(SEM_NAME);
        exit(1);
    }
    
    close(fd);
    //end of critical section
    sem_post(sem);
    sem_close(sem);


    return 0;
}
