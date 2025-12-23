#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

#define BUFFER_SIZE 100
#define READ_END 0
#define WRITE_END 1

int Pipe(int *pipefd);
pid_t Fork(void);
int Read(int fd,void *buf,size_t count);
int Write(int fd, const void *buf,size_t count);

int main(void)
{

    char write_msg_p_to_c[BUFFER_SIZE];
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

        
        //asks user for text
        char *text_entered = readline("Enter text: ");

        //copys userinput to msg_p_to_c
        strncpy(write_msg_p_to_c, text_entered, BUFFER_SIZE-1);

        int num_bytes_p_to_c = strlen(write_msg_p_to_c)+1;
        //write to child


        Write(p_to_c[WRITE_END], &num_bytes_p_to_c,sizeof(num_bytes_p_to_c));
        Write(p_to_c[WRITE_END], &write_msg_p_to_c,sizeof(write_msg_p_to_c));


        //close the write end of pipe
        close(p_to_c[WRITE_END]);


        //Read from child pipe
        char c_c_to_p[BUFFER_SIZE];
        int c_byte_size;

        Read(c_to_p[READ_END], &c_byte_size, sizeof(c_byte_size));
        printf("Byte_Size from child:%d\n",c_byte_size);
        Read(c_to_p[READ_END], c_c_to_p, c_byte_size);
        printf("Message from parent:%s\n",c_c_to_p);


        close(c_to_p[READ_END]);

        free(text_entered);
    }else{

        //child process
        //close the unsused pipe
        close(p_to_c[WRITE_END]);
        close(c_to_p[READ_END]);
        //read from parent pipe


        char c[BUFFER_SIZE];
        int p_byte_size;


        Read(p_to_c[READ_END], &p_byte_size, sizeof(p_byte_size));
        printf("Byte_Size from parent:%d\n", p_byte_size);
        Read(p_to_c[READ_END], c, sizeof(c));
        printf("Message from parent:%s\n",c);


        //formats string recieved from parent

        char c_formated[BUFFER_SIZE]="";

        char *tok;

        tok = strtok(c," \t");
        

        strcat(c_formated, tok);

        while((tok = strtok(NULL, " \t")) != NULL){

                strcat(c_formated," ");
                strcat(c_formated,tok);

        }


        close(p_to_c[READ_END]);

        //copys c_formated to msg_c_to_p
        strncpy(write_msg_c_to_p, c_formated, strlen(c_formated)+1);


        int num_bytes_c_to_p= strlen(write_msg_c_to_p)+1;
        //Write to parent
        
        Write(c_to_p[WRITE_END], &num_bytes_c_to_p,sizeof(num_bytes_c_to_p));
        Write(c_to_p[WRITE_END], &write_msg_c_to_p,sizeof(write_msg_c_to_p));
        

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

int Read(int fd,void *c,size_t count){


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
