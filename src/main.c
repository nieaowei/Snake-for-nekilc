
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
#include "move.h"

void *getInuptKey(LCDInput lcdInput){
    struct input_event ev;
    char msg[256];
    while (1)
    {
        int re = read(lcdInput->file_pointer,&ev,sizeof(ev));
        sprintf(msg,"get key status: %d",re);
        if (ev.type==EV_KEY)
        {
            if (ev.value==1)
            {
                sprintf(msg,"key code: %d",ev.code);
                logD("INPUT","getInuptKey",msg,200);
                lcdInput->currentKey = ev.code;
            }
            
        }
    }
}

void *moveRun(GameSetting gameSetting){
	while (1)
	{
		// gameSetting->snake->tailP->x = gameSetting->snake->bodyP[gameSetting->snake->length-2-1]->x;
        // gameSetting->snake->tailP->y = gameSetting->snake->bodyP[gameSetting->snake->length-2-1]->y;
        // gameSetting->snake->bodyP[gameSetting->snake->length-2-1]->x = gameSetting->snake->headP->x;
        // gameSetting->snake->bodyP[gameSetting->snake->length-2-1]->y = gameSetting->snake->headP->y;
        for (int i = gameSetting->snake->length-2-1; i > -1 ; i--)
        {
            // if end
            if (i==gameSetting->snake->length-2-1)
            {
                gameSetting->snake->tailP->x = gameSetting->snake->bodyP[i]->x;
                gameSetting->snake->tailP->y = gameSetting->snake->bodyP[i]->y;
                // continue;
                /* code */
            }
            // if first
            if (i==0)
            {
                gameSetting->snake->bodyP[i]->x = gameSetting->snake->headP->x;
                gameSetting->snake->bodyP[i]->y = gameSetting->snake->headP->y;
                continue;
            }
            gameSetting->snake->bodyP[i]->x = gameSetting->snake->bodyP[i-1]->x;
            gameSetting->snake->bodyP[i]->y = gameSetting->snake->bodyP[i-1]->y;

        }
        
        switch (gameSetting->snake->direction)
        {
        case LEFT_TO_RIGHT:
            
            gameSetting->snake->headP->y+=1;
            break;
        case TOP_TO_BOTTOM:
            gameSetting->snake->headP->x+=1;
            break;
        case RIGHT_TO_LEFT:
            gameSetting->snake->headP->y-=1;
            break;
        case BOTTOM_TO_TOP:
            gameSetting->snake->headP->x-=1;
            break;
        default:
            break;
        }
       
        
		usleep(1000*500);
	}
		
}

 int main(void)
 {	

	Size size = newSize(800,480);
	//initialize the screen and set its size.
	LCD lcd = newLCD(red,size);
	// Keyboard listener.
	// the child thread.
	// lcdInput->currentKey
	LCDInput lcdInput = createLCDInput("/dev/input/event2",getInuptKey);
    lcdInput->currentKey = KEY_RIGHT;
	Block DottedBlockEQ = newBlock(newBorder(newBorderType(DOTTED,4),blue,newPadding(10,10,10,10)),purple,size);
	Block gameScreen = newBlock(newBorder(newBorderType(SOLID,3),red,newPadding(10,10,10,10)),green,newSize(600,450));
	// initialize the game setting.
	GameSetting gameSetting = newGameSetting(gameScreen,newPosition(15,15),10,lcdInput);
	// initialize the screen backgroud.
	drawBlock(lcd,newPosition(0,0),DottedBlockEQ);
	// initialize the game area.
	drawGameScreen(lcd,gameSetting);
	// start move thread
	MoveThread move = createMoveThread(moveRun,gameSetting);
	// Draw the user interface in the main thread.
	drawGameMap(lcd,gameSetting);

	return 0;
 }

