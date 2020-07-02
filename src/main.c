
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
#include "home.h"
#include "game.h"
#include "input.h"
#include "core.h"
#include <pthread.h>


 int main(void)
 {	

	Size size = newSize(800,480);
	LCD lcd = newLCD(red,size);
	LCDInput lcdInput = createLCDInput("/dev/input/event2");
	Block DottedBlockEQ = newBlock(newBorder(newBorderType(DOTTED,4),blue,newPadding(10,10,10,10)),purple,size);
	Block gameScreen = newBlock(newBorder(newBorderType(SOLID,3),red,newPadding(10,10,10,10)),green,newSize(600,450));
	
	GameSetting GameSetting = newGameSetting(gameScreen,newPosition(15,15),10);

	drawBlock(lcd,newPosition(0,0),DottedBlockEQ);
	
	drawGameScreen(lcd,GameSetting);



	int i = 0;

	while (1)
	{
		char msg[256];
		sprintf(msg,"current key code: %d",lcdInput->currentKey);
		logD("MAIN","main",msg,200);
		sleep(1);
	}
	
	return 0;
 }

