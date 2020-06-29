
/*
 * File: role.c
 * Project: game
 * File Created: Monday, 29th June 2020 9:10:37 pm
 * Author: Neklic (nieaowei@gmail.com)
 * -----
 * Last Modified: Monday, 29th June 2020 9:10:53 pm
 * Modified By: Neklic (nieaowei@gmail.com>)
 * -----
 * Copyright 2020 Nekilc
 * -----
 * HISTORY:
 * Date      			By		Comments
 * --------------------	------	---------------------------------------------------------
 */

#include "role.h"
#include <stdlib.h>

Snake newSnake(Block head,Block body,Position position){
    Snake s = (Snake)malloc(sizeof(snakeInfo));
    s->head = head;
    s->body = body;
    s->position = position;
    return s;
}

Food newFood(Block block,int life){
    Food f = (Food)malloc(sizeof(foodInfo));
    f->block = block;
    f->life = life;
    return f;
}