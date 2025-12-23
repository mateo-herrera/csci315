#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reverse_string(int argc, char *argv[]);

int main(int argc, char *argv[]){

    reverse_string(argc, argv);
    return 0;
}


int reverse_string(int argc, char *argv[]){

    if(argc == 2){

        char *str = argv[1];

        int length = strlen(str);
        int i =0;
        int j = length -1;
        while (i< j){
            
            char temp = str[i];
            str[i] = str[j];
            str[j] = temp;
            i++;
            j--;
        }

        printf("%s",str);
    }
    else{
        printf("Error: must have 1 arguement of type string.");
        return 1;
    }

    return 0;
}
