
#include "wrappers.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stddef.h>

pid_t Fork(void){
 
     int pid;
 
     pid = fork();
 
     if(pid == -1){
 
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


 ssize_t Write(int fd, const void *buf, size_t count){

     ssize_t byte = write(fd, buf, count);

     if(byte == -1){

         perror("Write failed");
         exit(-1);
     }
     return byte;
 }


pid_t Wait(int *status){

    pid_t Wait = wait(status);

    if(Wait == -1){
        perror("Wait failed");

        exit(-1);
    }

    return Wait;
}


pid_t Waitpid(pid_t pid, int *status, int option){

    pid_t Waitpid = waitpid(pid, status, option);

    if(Waitpid == -1){
    
        perror("Waitpid failed");

        exit(-1);
    }

    return Waitpid;

} 


int Open(const char *pathname, int flags, mode_t mode){

    int Open = open(pathname, flags, mode);

    if (Open == -1){

        perror("Open failed");

        exit(-1);
    }

    return Open;
}


int Close(int fd){

    int Close = close(fd);

    if(Close == -1){

        perror("Close failed");

        exit(-1);
    }

    return Close;
}


int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen){

    int Connect = connect(sockfd, addr, addrlen);

    if(Connect == -1){

        perror("Connect failed");

        exit(-1);
    }

    return Connect;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){

    int Bind = bind(sockfd, addr, addrlen);

    if(Bind == -1){

        perror("Bind failed");

        exit(-1);
    }

    return Bind;
}


int Listen(int sockfd, int backlog){

    int Listen = listen(sockfd, backlog);


    if(Listen == -1){

        perror("Listen failed");

        exit(-1);
    }

    return Listen;
}


int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){

    int Accept = accept(sockfd, addr, addrlen);

    if(Accept == -1){

        perror("Accept failed");

        exit(-1);
    }

    return Accept;
}


