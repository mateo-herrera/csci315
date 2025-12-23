#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int Pipe(int *pipefd);
pid_t Fork(void);
int Read(int fd,char *buf,size_t count);
int Write(int fd, const void *buf,size_t count);

int main(void)
{

    char write_msg[BUFFER_SIZE] = "Greetings";
   // char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    Pipe((int *)fd);

    //fork a child process
    pid = Fork();

    if (pid<0){

        //error occured
        fprintf(stderr, "Fork Failed");
        return 1; 

    }

    if (pid > 0){

        //parent proccess
        //close unused end of the pipe
        close(fd[READ_END]);

        //write to pipe

        int i=0;

        while(write_msg[i] != '\0'){

            Write(fd[WRITE_END], &write_msg[i], 1);
        
            i++;
        }

        //close the write end of pipe
        close(fd[WRITE_END]);
    }else{

        //child process
        //close the unsused pipe
        close(fd[WRITE_END]);

        //read from pipe

        char c;
    
        while((Read(fd[READ_END], &c, 1)) >0){

            Write(STDOUT_FILENO, &c, 1);
        }



        close(fd[READ_END]);
    }

    return 0;

}

pid_t Fork(void){

    int pid;
    pid= fork();

    if(pid ==-1){

        perror("Error forking");
        exit(-1);
    }
    return pid;
}

int Pipe(int *pipefd){

    int Pipe;

    Pipe = pipe(pipefd);

    if(Pipe == -1){

        perror("Error creating pipe");
        exit(-1);
    }
    return Pipe;
}

int Read(int fd,char *c,size_t count){


   int byte;

    byte = read(fd, c,count);

    if(byte == -1){
        perror("read_pipe_error");
        exit(-1);
    }else if(byte <0){

        return -1;
    }
    return byte;

}

int Write(int fd, const void *c, size_t count){

    int byte = write(fd, c, count);

    if(byte == -1){

        perror("Write_pipe_error");
        exit(-1);
    }
    return byte;
}
