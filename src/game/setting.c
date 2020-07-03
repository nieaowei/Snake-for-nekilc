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
#include <stdio.h>
#include <stdlib.h>

extern  Food food_1;
extern  Food food_2;
extern  Food food_3;
extern  Food food_4;
extern  Food food_5;

GameSetting newGameSetting(Block background,Position position,int size,LCDInput lcdInput){
    GameSetting s = (GameSetting)malloc(sizeof(gameSettingInfo));
    //如果没有边框
    Position start = newPosition(position->x,position->y);
    Position end = newPosition(background->size->width+position->x,background->size->height+position->y);
    int temp = 0;
    //如果有边框，去除边框
    s->background=background;
    if (background->border!=NULL)
    {
        start->x = start->x + background->border->padding->left;
        start->y = start->y + background->border->padding->top;
        end->x = end->x - background->border->padding->right;
        end->y = end->y - background->border->padding->bottom;
    }
    s->lcdInput = lcdInput;
    s->position = position;
    s->range = newPositionRange(start,end);
    s->size = size;
    s->row = (end->y-start->y)/size;
    s->col = (end->x-start->x)/size;

    s->object = newBlock(NULL,background->color,newSize(size,size));

    s->map = (int **)malloc(sizeof(int*)*s->row);
    for ( temp = 0; temp < s->row; temp++)
    {
        s->map[temp] = (int*)malloc(sizeof(int)*s->col);
    }

    s->snake = newSnake(newBlock(NULL,orange,newSize(size,size)),newBlock(NULL,blue,newSize(size,size)),newBlock(newBorder(newBorderType(SOLID,0),orange,newPadding(1,1,1,1)),yellow,newSize(size,size)),newPosition(s->row/2,s->col/2));

    pthread_mutex_init(&s->foodMux,NULL);

    s->foodsIsFull=0;
    s->scorce = 0;
    s->foodLen = 0;


    food_1 = newFood(newBlock(newBorder(newBorderType(SOLID,0),red,newPadding(2,2,2,2)),white,newSize(size,size)),1);
    food_2 = newFood(newBlock(newBorder(newBorderType(SOLID,0),red,newPadding(2,2,2,2)),orange,newSize(size,size)),2);
    food_3 = newFood(newBlock(newBorder(newBorderType(SOLID,0),red,newPadding(2,2,2,2)),yellow,newSize(size,size)),3);
    food_4 = newFood(newBlock(newBorder(newBorderType(SOLID,0),red,newPadding(2,2,2,2)),purple,newSize(size,size)),4);
    food_5 = newFood(newBlock(newBorder(newBorderType(SOLID,0),red,newPadding(2,2,2,2)),black,newSize(size,size)),5);

    return s;
}