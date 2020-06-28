
/*
 * File: main.c
 * Project: src
 * File Created: Sunday, 28th June 2020 10:20:17 pm
 * Author: Neklic (nieaowei@gmail.com)
 * -----
 * Last Modified: Sunday, 28th June 2020 11:39:47 pm
 * Modified By: Neklic (nieaowei@gmail.com>)
 * -----
 * Copyright 2020 Nekilc
 * -----
 * HISTORY:
 * Date      			By		Comments
 * --------------------	------	---------------------------------------------------------
 * 
 * 2020-06-28 11:39:50	Neklic	
 * 
 * 2020-06-29 7:09:01	Neklic	test
 */


#include <stddef.h>
#include "lcd.h"


 int main(void)
 {	
	Color red = 0x00ff0000;
	Color blue = 0x000000ff;

	Size size = newSize(800,480);
	LCD lcd = newLCD(blue,size);
	Block block = newBlock(newBorder(blue,5,newPadding(2,2,2,2)),red,size);
	drawBlock(lcd,newPosition(0,0),block);

	return 0;
 }

