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
	Color red = 0x00ff0000;
	Color blue = 0x000000ff;
	Color green = 0x0000ff00;
    Block block = newBlock(newBorder(SOLID,red,newPadding(0,5,0,5)),blue,newSize(50,50));
    for (int i = 0; i < 3; i++)
    {
        drawBlock(lcd,newPosition(i*50,i*50),block);

    }
    
}


