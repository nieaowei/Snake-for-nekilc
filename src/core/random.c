#include "random.h"
#include <time.h>
#include <stdlib.h>

int random_between(int a,int b){
    srand(time(0));
    return (rand()%(b-a+1))+a;
}