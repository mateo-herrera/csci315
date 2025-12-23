/*
 * Problem 5: Added feature
 *
 * exit- to exit out of the ishell one simply types exit in the prompt.
 * ex.
 *  ishell>exit
 *
 * cd- changes directory to the path described in the arguements following cd.
 * ex.
 *  ishell>cd ..
 *  (changes current directory to parent)
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "wrappers.h"

#define PROMPT "ishell>"
#define MAX_SIZE 64


void show_directory();
int run_command(char **args);
void tokenize_input(char *input, char** args);

//tokenizes the input into args
void tokenize_input(char *input, char** args){

    int i =0;
    char *token= strtok(input, " \t\r\n\a");
    while(token != NULL && i<MAX_SIZE-1){

        args[i++] = token;
        token= strtok(NULL, " \t\r\n\a");

    }
    args[i] = NULL;
}

int main(int argc, char* argv[]){


    char* input = NULL;
    ssize_t input_size=0;
    char *args[MAX_SIZE];
    bool shell_running = true;

    int enter_times =0;


    while (shell_running){

        //Print prompt and collect user input
        printf("%s",PROMPT);
        fflush(stdout);
        ssize_t read = getline(&input, &input_size, stdin);
        //checks for error in reading
        if(read == -1){

            perror("Couldn't get line");
            break;
        }


        //checks if "\n" was only input to count towards double [enter]
        if(strcmp(input, "\n")==0){

            enter_times++;
            if(enter_times==2){
                show_directory();
                enter_times =0;
            }
        }

        //removes newline
        input[strcspn(input, "\n")] = 0;


        //splits string
        char *command1 =strtok(input, ";");
        char *command2 =strtok(NULL, ";");

        //tokenizes command1
        if(command1 != NULL){

            tokenize_input(command1, args);
            //resets enter_times
            enter_times =0;
            //Checks if exit
            if(args[0] != NULL && run_command(args) == 1){
                shell_running=false;
                break;
            }
        }

        //tokenizes command2
        if(command2 != NULL){

            tokenize_input(command2, args);
            //resets enter_times
            enter_times=0;
            //check if exit
            if(args[0] != NULL && run_command(args) == 1){
                shell_running = false;
                break;
            }
        }

    }

    free(input);
    return 0;
}


int run_command(char **args){


    //returns exit value
    if(strcmp(args[0], "exit")==0){
        return 1;
    //Checks if cd command
    }else if (strcmp(args[0], "cd") ==0){
        if(args[1] == NULL){
            fprintf(stderr,"[cd: expected directory]\n");
        }else{
            if(chdir(args[1]) != 0 ){
                perror("cd error");
            }
        }
        return 0;
    }

    //Other command than exit & cd so forks
    pid_t pid_id = Fork();

    //child process
    if(pid_id == 0){
        execvp(args[0],args);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }else{
    //Parent process waits for child
        int status;
        waitpid(pid_id, &status, 0);

    //prints whether exec was successful or failed
        int exit = WEXITSTATUS(status);
        if(exit ==0){
            printf("[ishell: program terminated successfully]\n");
        }else{
            printf("[ishell: program terminated abnormally[%d]\n", exit);
        }
        return 0;
    }
}


//shows currenty working directory
void show_directory(){

    pid_t pid_id = Fork();

    //creates child process to run ls
    if(pid_id ==0){
        char *args[]={"ls",".",NULL};
        execvp(args[0],args);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }else{
        //parent process which waits for ls to execute
        int status;
        waitpid(pid_id, &status, 0);

    }
}
