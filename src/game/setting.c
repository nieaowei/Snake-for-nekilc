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

ScreenSetting newScreenSetting(Block background){
    ScreenSetting s = (ScreenSetting)malloc(sizeof(screenSetting));
    if (background->border!=NULL)
    {
        s->start = newPosition(background->border->padding->left,background->border->padding->top);
        s->end = newPosition(background->border->padding->left,background->border->padding->top);
    }
    
}