/*
 * File: core.h
 * Project: include
 * File Created: Monday, 29th June 2020 12:20:45 am
 * Author: Neklic (nieaowei@gmail.com)
 * -----
 * Last Modified: Monday, 29th June 2020 12:48:37 am
 * Modified By: Neklic (nieaowei@gmail.com>)
 * -----
 * Copyright 2020 Nekilc
 * -----
 * HISTORY:
 * Date      			By		Comments
 * --------------------	------	---------------------------------------------------------
 * 
 * 2020-06-29 3:53:07	Neklic	add Border,Size,Position,Block model.
 * 
 * 2020-06-29 5:01:58	Neklic	rename all models.
 */

#ifndef _CORE_H
#define _CORE_H

#define true    1
#define false   0

typedef int px;
typedef __UINT32_TYPE__ Color;
typedef int bool;

typedef enum{
    SOLID=0,
    DOTTED
}BORDER_TYPE;

typedef struct
{
    px top;
    px bottom;
    px left;
    px right;

}paddingInfo, *Padding;

Padding newPadding(px top,px bottom,px left,px right);

typedef struct 
{
    BORDER_TYPE type;
    px spacing;

}BorderTypeInfo,*BorderType;

BorderType newBorderType(BORDER_TYPE type,px spacing);

typedef struct 
{
    BorderType borderType;
    Color color;
    Padding padding;

}boderInfo,*Border;

Border newBorder(BorderType borderType,Color color,Padding padding);


typedef struct 
{
    px width;
    px height;

}sizeInfo,*Size;

Size newSize(px width,px height);

typedef struct 
{
    Border border;
    Color color;
    Size size;

}blockInfo,  *Block;

Block newBlock(Border border,Color color,Size size);

typedef struct 
{
    int x;
    int y;

} positionInfo,  *Position;

Position newPosition(int x,int y);


extern Color red;
extern Color blue;
extern Color green;
extern Color yellow;
extern Color gray;
extern Color brown;
extern Color orange;
extern Color white;
extern Color black;
extern Color purple;
extern Color clear;

#endif
