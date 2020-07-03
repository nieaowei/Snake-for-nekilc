
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
#include <unistd.h>
#include "random.h"
#include "move.h"
#include <stdlib.h>

void setFoodFrom(GameSetting g,int x,int y){
    // int len = g->foodLen;
    // printf("f len :%d \n",len);
    // if (g->foodsIsFull)
    // {
    //     len = 10;
    // }
    // printf(" len :%d \n",len);
    
    // for (int i = 0; i < len; i++)
    // {
    //     if (g->foods[i]!=NULL)
    //     {
    //         if (g->foods[i]->x ==x && g->foods[i]->y==y)
    //         {
    //             printf("eat kill\n");
    //             g->foods[i]->x=-1;
    //             g->foods[i]->y=-1;
    //             g->foodKinds[i] = 0;
    //             break;
    //         }
    //     }
        
    // }
    
}

void *getInuptKey(void *arg){
    LCDInput lcdInput = (LCDInput)arg;
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

pthread_mutex_t lock;

void *moveRun(void *arg){
    GameSetting gameSetting = (GameSetting)arg;
    int addFlag=0;
	while (1)
	{
		// gameSetting->snake->tailP->x = gameSetting->snake->bodyP[gameSetting->snake->length-2-1]->x;
        // gameSetting->snake->tailP->y = gameSetting->snake->bodyP[gameSetting->snake->length-2-1]->y;
        // gameSetting->snake->bodyP[gameSetting->snake->length-2-1]->x = gameSetting->snake->headP->x;
        // gameSetting->snake->bodyP[gameSetting->snake->length-2-1]->y = gameSetting->snake->headP->y;
        if (addFlag)
        {
            gameSetting->snake->length++;
            gameSetting->snake->bodyP[gameSetting->snake->length-2-1] = newPosition(gameSetting->snake->tailP->x,gameSetting->snake->tailP->y);
            addFlag = 0;
        }
        
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
        int flag;
        switch (gameSetting->snake->direction)
        {
        case LEFT_TO_RIGHT:
            if (gameSetting->snake->headP->y+1 >= gameSetting->col)
            {
                logD("MAIN","*moveRun","game over ,Hit the right wall.",200);
                exit(0);
            }
            flag = gameSetting->map[gameSetting->snake->headP->x][gameSetting->snake->headP->y+1];
            if (flag==BODY || flag==TAIL)
            {
                logD("MAIN","*moveRun","game over ,head hit the tail or body.",200);
                exit(0);
            }
            
            gameSetting->snake->headP->y+=1;
            break;
        case TOP_TO_BOTTOM:
            if (gameSetting->snake->headP->x+1 >= gameSetting->row)
            {
                logD("MAIN","*moveRun","game over ,Hit the bottom wall.",200);
                exit(0);
            }
            flag = gameSetting->map[gameSetting->snake->headP->x+1][gameSetting->snake->headP->y];
            if (flag==BODY || flag==TAIL)
            {
                logD("MAIN","*moveRun","game over ,head hit the tail or body.",200);
                exit(0);
            }

            gameSetting->snake->headP->x+=1;
            break;
        case RIGHT_TO_LEFT:
            if (gameSetting->snake->headP->y-1 < 0)
            {
                logD("MAIN","*moveRun","game over ,Hit the left wall.",200);
                exit(0);
            }
            flag = gameSetting->map[gameSetting->snake->headP->x][gameSetting->snake->headP->y-1];
            if (flag==BODY || flag==TAIL)
            {
                logD("MAIN","*moveRun","game over ,head hit the tail or body.",200);
                exit(0);
            }
            gameSetting->snake->headP->y-=1;
            break;
        case BOTTOM_TO_TOP:
            if (gameSetting->snake->headP->x-1 < 0)
            {
                logD("MAIN","*moveRun","game over ,Hit the top wall.",200);
                exit(0);
            }
            flag = gameSetting->map[gameSetting->snake->headP->x-1][gameSetting->snake->headP->y];
            if (flag==BODY || flag==TAIL)
            {
                logD("MAIN","*moveRun","game over ,head hit the tail or body.",200);
                exit(0);
            }
            gameSetting->snake->headP->x-=1;
            break;
        default:
            flag = 0;
            break;
        }
        int tempS = gameSetting->scorce;
        switch (gameSetting->map[gameSetting->snake->headP->x][gameSetting->snake->headP->y])
        {
        case FOOD_1:
            gameSetting->map[gameSetting->snake->headP->x][gameSetting->snake->headP->y]=0;
            setFoodFrom(gameSetting,gameSetting->snake->headP->x,gameSetting->snake->headP->y);
            gameSetting->scorce+=food_1->life;
            break;
        case FOOD_2:
            gameSetting->map[gameSetting->snake->headP->x][gameSetting->snake->headP->y]=0;
            setFoodFrom(gameSetting,gameSetting->snake->headP->x,gameSetting->snake->headP->y);

            gameSetting->scorce+=food_2->life;
            break;
        case FOOD_3:
            gameSetting->map[gameSetting->snake->headP->x][gameSetting->snake->headP->y]=0;
            setFoodFrom(gameSetting,gameSetting->snake->headP->x,gameSetting->snake->headP->y);

            gameSetting->scorce+=food_3->life;
            break;
        case FOOD_4:
            gameSetting->map[gameSetting->snake->headP->x][gameSetting->snake->headP->y]=0;
            setFoodFrom(gameSetting,gameSetting->snake->headP->x,gameSetting->snake->headP->y);

            gameSetting->scorce+=food_4->life;
            break;
        case FOOD_5:
            gameSetting->map[gameSetting->snake->headP->x][gameSetting->snake->headP->y]=0;
            setFoodFrom(gameSetting,gameSetting->snake->headP->x,gameSetting->snake->headP->y);

            gameSetting->scorce+=food_5->life;
            break;
        default:
            break;
        }

        if (gameSetting->scorce/5 - gameSetting->snake->length + 4 > 0)
        {
            // if ((gameSetting->scorce - tempS)>=5)
            // {
                // gameSetting->snake->length++;
                // gameSetting->snake->bodyP[gameSetting->snake->length-2-1] = newPosition(gameSetting->snake->tailP->x,gameSetting->snake->tailP->y);
                // gameSetting->snake->bodyP[gameSetting->snake->length-2-1]->x=gameSetting->snake->tailP->x;
                // gameSetting->snake->bodyP[gameSetting->snake->length-2-1]->y=gameSetting->snake->tailP->y;
                addFlag=1;
            // }
            
        }
        

        

        // pthread_mutex_unlock(&gameSetting->foodMux);

        // pthread_mutex_unlock(&lock);
        
        char msg[200];
        sprintf(msg,"current scorce: %d .",gameSetting->scorce);

        // logD("MAIN","*moveRun",msg,200);
		// usleep(1000*500);
        // sleep(1);
        usleep(gameSetting->snake->speed-gameSetting->scorce*50);
	}
		
}

void *updatedFood(GameSetting gameSetting){
    while (1)
    {
        // create food.
        int x = random_between(0,gameSetting->row-1);
        int y = random_between(0,gameSetting->col-1);
        if (gameSetting->map[x][y]==0)
        {   
            int kind = random_between(1,5);
            pthread_mutex_lock(&gameSetting->foodMux);
            int tempLen = gameSetting->foodLen;
            if (gameSetting->foods[tempLen]!=NULL)
            {
                /* code */
                 gameSetting->map[gameSetting->foods[tempLen]->x][gameSetting->foods[tempLen]->y]=0;
                // free(gameSetting->foods[tempLen]);
                gameSetting->foods[tempLen]->x = x;
                gameSetting->foods[tempLen]->y = y;
            }else
            {
                gameSetting->foods[tempLen] = newPosition(x,y);
            }
            gameSetting->foodKinds[tempLen] = kind;
            
            if (gameSetting->foodLen+1 >= 10 && gameSetting->foodsIsFull == 0)
            {
                gameSetting->foodsIsFull = 1;
                gameSetting->foodLen = 0;
            }else
            {
                gameSetting->foodLen += 1;

            }
            pthread_mutex_unlock(&gameSetting->foodMux);
        }
        

        
        usleep(gameSetting->snake->speed*10);
    }
    
}

 int main(void)
 {	
    pthread_mutex_init(&lock,NULL);

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
	createMoveThread(moveRun,gameSetting);
    // food 
    pthread_t foodId;
    pthread_create(&foodId,NULL,updatedFood,gameSetting);
	// Draw the user interface in the main thread.
	drawGameMap(lcd,gameSetting);
    while (1)
    {
        /* code */
        sleep(1);
    }
    

	return 0;
 }

