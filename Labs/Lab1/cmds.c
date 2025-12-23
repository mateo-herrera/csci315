
#include <stdlib.h>
#include <stdio.h>

int check_args(int argc, char *argv[]);

int main(int argc, char *argv[])
{

    check_args(argc, argv);

    return 0;
}

int check_args(int argc, char *argv[]){

    
    if(argc == 5){

        char c= argv[1][0];
        int i= atoi(argv[2]);
        float f= atof(argv[3]);
        char *str= argv[4];


        printf("Char: %c\n",c);
        printf("Int: %d\n",i);
        printf("Float: %.2f\n", f);
        printf("String : %s\n", str);

        return 0;
    }else{
        printf("Error: must have 4 arguements: char, int, float, string");
        return 1;
    }

}
