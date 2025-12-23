#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>



pid_t Fork(void);
pid_t waitpid(pid_t, int *status, int options);

void print_environment(void);

extern char **environ;



int main(int argc, char *argv[]){
    
    char *file = argv[1];
    
    print_environment();

    pid_t pid1 = Fork();

    if(pid1 == 0){

        printf("Child 1 starting:\n");
        execlp("cat","cat",file, (char *)NULL);
        perror("execlpm failed");
        printf("Child 1 terminating.\n");

    }else{

        waitpid(pid1,0,0);
        
    }
    
    pid_t pid2 = Fork();
    if(pid2 == 0){
        printf("Child 2 starting:\n");
        execlp("wc","wc",file, (char *)NULL);
        perror("execlp failed");
        printf("Child 2 terminating.\n");

    }else{
        waitpid(pid2,0,0);
    }

    printf("Parent Terminating\n");
    exit(0);
    return 0;
}

void print_environment(void){

    for(int i=0;i<sizeof(environ);i++){

        printf("%s\n",environ[i]);
    }

}

pid_t Fork(void){

    int pid;
    pid = fork();

    if (pid == -1){

        perror("Error forking");
        exit(-1);

    }
    return pid;

}
