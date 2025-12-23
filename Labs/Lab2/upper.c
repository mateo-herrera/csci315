#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int Pipe(int *pipefd);
pid_t Fork(void);
int Read(int fd,char *buf,size_t count);
int Write(int fd, const void *buf,size_t count);

int main(void)
{

    char write_msg_p_to_c[BUFFER_SIZE] = "Greetings";
    char write_msg_c_to_p[BUFFER_SIZE];
    int p_to_c[2];
    int c_to_p[2];
    pid_t pid;

    Pipe((int *)p_to_c);

    Pipe((int *)c_to_p);

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
        close(p_to_c[READ_END]);
        close(c_to_p[WRITE_END]);
        //write to pipe

        int i=0;

        while(write_msg_p_to_c[i] != '\0'){

            Write(p_to_c[WRITE_END], &write_msg_p_to_c[i], 1);
        
            i++;
        }

        //close the write end of pipe
        close(p_to_c[WRITE_END]);

        char c_c_to_p;
        while((Read(c_to_p[READ_END], &c_c_to_p,1))>0){

            Write(STDOUT_FILENO,&c_c_to_p,1);
        }


        close(c_to_p[READ_END]);
    }else{

        //child process
        //close the unsused pipe
        close(p_to_c[WRITE_END]);
        close(c_to_p[READ_END]);
        //read from pipe

        char c;
        int index_p_to_c=0;

        while((Read(p_to_c[READ_END], &c, 1)) >0){

            Write(STDOUT_FILENO, &c, 1);
            write_msg_c_to_p[index_p_to_c] = toupper(c);
            index_p_to_c++;

        }
        write_msg_c_to_p[index_p_to_c] = '\0';


        close(p_to_c[READ_END]);

        int index_c_to_p=0;
        //Write to parent
        while(write_msg_c_to_p[index_c_to_p] != '\0'){

            Write(c_to_p[WRITE_END], &write_msg_c_to_p[index_c_to_p],1);
        
            index_c_to_p++;
        }


        close(c_to_p[WRITE_END]);
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
