#include <stdio.h>
#include <stdlib.h>
#include "hexdump.h"

//Used for UINT_MAX which is specific max for unsigned int in the system
#include <limits.h>


int main(int argc,char *argv[]){

    //check number of args
    if(argc != 4){
        printf("ERROR: Not enough arguements.\nProper input filename(char array), offset(unsigned int), and size(unsigned integer)\n");
        return 1;
    }

    //check arguement 1: filename char array
    char *filename=argv[1];

    //check arguement 2: offset unsigned int
    unsigned int offset = (unsigned int)strtoul(argv[2],NULL,0);
    if(strtol(argv[2],NULL,0) < 0){
        printf("ERROR: arguement 2 offset(unsigned int) is less than min value 0.\n");
        return 1;
    }
    if(offset > UINT_MAX){
        printf("ERROR: arguement 2 offset(unsigned int) exceeds the maximum value.\n");
        return 1;
    }

    //check arguement 3: size unsigned int
    unsigned int size = (unsigned int)strtoul(argv[3],NULL,0);
    if(strtol(argv[3],NULL,0) < 0){
        printf("ERROR: arguement 3 size(unsigned int) is less than min value 0.\n");
        return 1;
    }

    if(size > UINT_MAX){
        printf("ERROR: arguement 3 size(unsigned int) exceeds the maximum value.\n");
        return 1;
    }

    //Opens file
    FILE *file = fopen(filename,"r");
    if(file == NULL){
        perror("ERROR: opening file");
        fclose(file);
        return 1;
    }

    //Moves to offset
    if(fseek(file, offset, SEEK_SET) !=0){
        perror("ERROR: seeking file");
        fclose(file);
        return 1;
    }

    //Creates buffer
    char *buffer=malloc(size);
    if(buffer == NULL){
        printf("ERROR: memory allocation\n");
        fclose(file);
        return 1;
    }

    fread(buffer, 1, size, file);


    hexdump(buffer, size);

    free(buffer);
    fclose(file);
    return 0;
}
