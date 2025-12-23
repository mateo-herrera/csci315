#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SEM_NAME "/mh065"
#define FILE_NAME "Channel.txt"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){

    //open semaphore
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if(sem == SEM_FAILED){
        perror("Semaphore");
        exit(1);
    }

    //open file
    int fd = open(FILE_NAME, O_RDWR | O_CREAT, 0666);
    if(fd == -1){
        perror("open");
        sem_post(sem);
        sem_close(sem);
        sem_unlink(SEM_NAME);
        exit(1);
    }


    char buffer[BUFFER_SIZE];

    printf("Reciever started:\n");

    while(1){

        sem_wait(sem);

        //moves fd to beggining of file
        lseek(fd, 0, SEEK_SET);


        //reads from file
        ssize_t byte_read = read(fd, buffer, sizeof(buffer)-1);
        if(byte_read > 0){
        
            buffer[byte_read] = '\0';
            printf("reciever [msg arrival]: \"%s\"\n",buffer);
        }
    
        //clears the txt file
        if(ftruncate(fd, 0) == -1){

            perror("ftruncate");
            close(fd);
            sem_post(sem);
            sem_close(sem);
            sem_unlink(SEM_NAME);
            exit(1);
        }

        //closes semaphore and waits 0.5 seconds
        sem_post(sem);
        usleep(500000);
    }

    //closes file and semaphores
    close(fd);
    sem_close(sem);
    sem_unlink(SEM_NAME);



    return 0;
}
