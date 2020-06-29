

#include "game.h"
#include "role.h"
#include <stdlib.h>


FoodData newFoodData(){
    FoodData f = (FoodData)malloc(sizeof(foodDataInfo));
    f->lenth=0;
    return f;
}

void test(){
    
    FoodData f=newFoodData();
    for (int i = 0; i < f->lenth; i++)
    {
        /* code */
    }
    
}



