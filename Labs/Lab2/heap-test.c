#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

pid_t Fork(void);

int main()
{

    int *ptr = (int*)malloc(1 * sizeof(int));

    int num=5;
    ptr = &num;


    pid_t pid;

    if((pid = Fork()) == 0){

        //child proccess
        printf("Child printing: %d\n",*ptr);
    
        exit(0);
    }else{

        //parent proccess

        printf("Parent printing: %d\n",*ptr);
    
        exit(0);
    }




    return 0;

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
