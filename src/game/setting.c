/*
 * File: setting.c
 * Project: game
 * File Created: Monday, 29th June 2020 6:47:50 pm
 * Author: Neklic (nieaowei@gmail.com)
 * -----
 * Last Modified: Monday, 29th June 2020 6:48:36 pm
 * Modified By: Neklic (nieaowei@gmail.com>)
 * -----
 * Copyright 2020 Nekilc
 * -----
 * HISTORY:
 * Date      			By		Comments
 * --------------------	------	---------------------------------------------------------
 */
#include "setting.h"
#include <stddef.h>
#include <stdlib.h>

ScreenSetting newScreenSetting(Block background,Position position,int size){
    ScreenSetting s = (ScreenSetting)malloc(sizeof(screenSetting));
    //如果没有边框
    Position start = newPosition(position->x,position->y);
    Position end = newPosition(background->size->width+position->x,background->size->height+position->y);
    int temp = 0;
    //如果有边框，去除边框
    if (background->border!=NULL)
    {
        start->x = start->x + background->border->padding->left;
        start->y = start->y + background->border->padding->top;
        end->x = end->x - background->border->padding->right;
        end->y = end->y - background->border->padding->bottom;
    }
    
    s->position = position;
    s->range = newPositionRange(start,end);
    s->size = size;
    s->row = (end->x-start->x)/size;
    s->col = (end->y-start->y)/size;

    s->map = (Food *)malloc(sizeof(Food)*s->row);
    for ( temp = 0; temp < s->row; temp++)
    {
        s->map[temp] = (Food)malloc(sizeof(foodInfo)*s->col);
    }


    return s;
}