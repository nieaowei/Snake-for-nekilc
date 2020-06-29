/*
 * File: mainUI.c
 * Project: mainUI
 * File Created: Monday, 29th June 2020 2:46:21 pm
 * Author: Neklic (nieaowei@gmail.com)
 * -----
 * Last Modified: Monday, 29th June 2020 2:47:25 pm
 * Modified By: Neklic (nieaowei@gmail.com>)
 * -----
 * Copyright 2020 Nekilc
 * -----
 * HISTORY:
 * Date      			By		Comments
 * --------------------	------	---------------------------------------------------------
 */

#include "mainUI.h"

void paintMainUI(LCD lcd){
    Block block = newBlock(newBorder(newBorderType(SOLID,0),orange,newPadding(1,5,1,5)),yellow,newSize(50,50));
    for (int i = 0; i < 3; i++)
    {
        drawBlock(lcd,newPosition(i*50+10,i*50+10),block);

    }
    
}


