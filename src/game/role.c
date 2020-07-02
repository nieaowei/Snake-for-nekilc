
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

Snake newSnake(Block head,Block tail,Block body,Position headP){
    Snake s = (Snake)malloc(sizeof(snakeInfo));
    s->head = head;
    s->tail = tail;
    s->body = body;
    s->length = 3;
    s->headP = headP;
    s->direction = LEFT_TO_RIGHT;
    s->speed = 1;
    s->tailP = newPosition(headP->x,headP->y-2);
    s->bodyP[0] =  newPosition(headP->x,headP->y-1);
    return s;
}

Food newFood(Block block,int life){
    Food f = (Food)malloc(sizeof(foodInfo));
    f->block = block;
    f->life = life;
    return f;
}