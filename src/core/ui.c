
/*
 * File: ui.c
 * Project: core
 * File Created: Monday, 29th June 2020 3:17:50 am
 * Author: Neklic (nieaowei@gmail.com)
 * -----
 * Last Modified: Monday, 29th June 2020 3:52:19 am
 * Modified By: Neklic (nieaowei@gmail.com>)
 * -----
 * Copyright 2020 Nekilc
 * -----
 * HISTORY:
 * Date      			By		Comments
 * --------------------	------	---------------------------------------------------------
 * 
 * 2020-06-29 3:52:21	Neklic	add Border,Size,Position,Block constructor.
 * 
 * 2020-06-29 5:01:06	Neklic	modified * to *info.
 * 
 * 2020-06-29 7:09:25	Neklic	add Padding model.
 */

#include "ui.h"
#include <stdlib.h>

Padding newPadding(px top,px bottom,px left,px right){
    Padding p = (Padding)malloc(sizeof(paddingInfo));
    p->top=top;
    p->bottom=bottom;
    p->left=left;
    p->right=right;
    return p;
}

Border newBorder(BorderType type,Color color,Padding padding){
    Border b = (Border)malloc(sizeof(boderInfo));
    b->type = type;
    b->color = color;
    b->padding = padding;
    return b;
}


Size newSize(px width,px height){
    Size s = (Size)malloc(sizeof(sizeInfo));
    s->width=width;
    s->height=height;
    return s;
}

Block newBlock(Border border,Color color,Size size){
    Block b = (Block)malloc(sizeof(blockInfo));
    b->border = border;
    b->color = color;
    b->size = size;
    return b;
}

Position newPosition(int x,int y){
    Position p = (Position)malloc(sizeof(positionInfo));
    p->x = x;
    p->y = y;
    return p;
}