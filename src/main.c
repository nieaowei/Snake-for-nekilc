
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
#include <stdio.h>
#include "mainUI.h"



 int main(void)
 {	
	Color red = 0x00ff0000;
	Color blue = 0x000000ff;
	Color green = 0x0000ff00;

	Size size = newSize(800,480);
	LCD lcd = newLCD(red,size);
	Block SolidBlockEQ = newBlock(NULL,green,size);
	// Block SolidBlockNEQ = newBlock(newBorder(SOLID,blue,newPadding(10,30,10,20)),green,size);
	// Block DottedBlockEQ = newBlock(newBorder(DOTTED,blue,newPadding(10,10,10,10)),green,size);
	// Block DottedBlockNEQ = newBlock(newBorder(DOTTED,blue,newPadding(10,30,10,10)),green,size);
	// Block blocks[4]={SolidBlockEQ,SolidBlockNEQ,DottedBlockEQ,DottedBlockNEQ};
	drawBlock(lcd,newPosition(0,0),SolidBlockEQ);
	
	paintMainUI(lcd);

	int i = 0;

	while (1)
	{
		// drawBlock(lcd,newPosition(0,0),blocks[i++]);
		sleep(1);
		i=i%4;
	}
	
	return 0;
 }

