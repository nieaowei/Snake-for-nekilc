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

typedef struct
{
    int length;
    int speed;
    Block head;
    Block body;
    Position position;

}snakeInfo,*Snake;

Snake newSnake(Block head,Block body,Position position);

typedef struct
{
    Block block;
    int life;

}foodInfo,*Food;

Food newFood(Block block);


#endif