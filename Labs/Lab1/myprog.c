#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){


    int parent_counter = 0;
    int child1_counter = 0;
    int child2_counter = 0;

    pid_t child1_pid = fork();

    if(child1_pid<0){

        perror("Child1: Fork Fail");
        return 1;
    }

    if (child1_pid ==0){

        while (1){

            printf("child1: %d\n", child1_counter);
            child1_counter ++;
            usleep(500000);
        }
    }else{

        pid_t child2_pid = fork();
        if(child2_pid < 0){

            perror ("Child2: Fork Fail");
            return 1;
        }

        if(child2_pid ==0){

            while(1){

                printf("child2: %d\n",child2_counter);
                child2_counter++;
                usleep(500000);
            }
        }else{

            while(1){

                printf("parent: %d\n",parent_counter);
                parent_counter++;
                usleep(500000);
            }
        }
    }
    return 0;
}
