/*
 * File: lcd..h
 * Project: include
 * File Created: Monday, 29th June 2020 3:56:13 am
 * Author: Neklic (nieaowei@gmail.com)
 * -----
 * Last Modified: Monday, 29th June 2020 3:56:43 am
 * Modified By: Neklic (nieaowei@gmail.com>)
 * -----
 * Copyright 2020 Nekilc
 * -----
 * HISTORY:
 * Date      			By		Comments
 * --------------------	------	---------------------------------------------------------
 */

#ifndef _LCD_H
#define _LCD_H

#include "ui.h"

typedef struct 
{
    __UINT32_TYPE__ *address;
    Color color;
    Size size;
}lcd,*LCD;

LCD newLCD(Color color,Size size);
void drawBlock(LCD lcd,Position position,Block block);

#endif