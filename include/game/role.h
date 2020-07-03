/*
 * File: role.h
 * Project: include
 * File Created: Monday, 29th June 2020 6:00:15 pm
 * Author: Neklic (nieaowei@gmail.com)
 * -----
 * Last Modified: Monday, 29th June 2020 6:48:29 pm
 * Modified By: Neklic (nieaowei@gmail.com>)
 * -----
 * Copyright 2020 Nekilc
 * -----
 * HISTORY:
 * Date      			By		Comments
 * --------------------	------	---------------------------------------------------------
 */

#ifndef __ROLE_H
#define __ROLE_H

#include "ui.h"
// #include "move.h"

typedef enum{
    HEAD = 1,
    BODY,
    TAIL
}SnakePart;

typedef enum{
    FOOD_1=4,
    FOOD_2,
    FOOD_3,
    FOOD_4,
    FOOD_5,
}FoodType;

typedef enum{
    LEFT_TO_RIGHT=0,
    RIGHT_TO_LEFT,
    TOP_TO_BOTTOM,
    BOTTOM_TO_TOP
}MoveType;


typedef struct
{
    int length;
    long speed;
    Block head;
    Block body;
    Block tail;
    // Position position;
    Position headP;
    Position tailP;
    Position bodyP[256];
    MoveType direction;
}snakeInfo,*Snake;

Snake newSnake(Block head,Block tail,Block body,Position headP);

typedef struct
{
    Block block;
    int life;

}foodInfo,*Food;

 Food food_1;
 Food food_2;
 Food food_3;
 Food food_4;
 Food food_5;

Food newFood(Block block,int life);


#endif