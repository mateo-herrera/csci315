#include <stdio.h>
#include <sys/time.h>
#include <time.h>


int main(){

    struct timeval t;
    struct tm *tm_information;

    if(gettimeofday(&t, NULL) != 0){

        perror("gettimeofday failed");

        return 1;
    }

    time_t t_seconds = t.tv_sec;

    tm_information = localtime(&t_seconds);

    if(tm_information == NULL){

        perror("localtime failed");

        return 1;
    }

    char *tm_string = ctime(&t_seconds);

    if(tm_string == NULL){

        perror("ctime failed");

        return 1;
    }

    printf("Time: %s",tm_string);

    return 0;
}
