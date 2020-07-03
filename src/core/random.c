#include "random.h"
#include <sys/time.h>
#include <stdlib.h>

int random_between(int a,int b){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    srand(tv.tv_sec*1000000+tv.tv_usec);
    return (rand()%(b-a+1))+a;
}