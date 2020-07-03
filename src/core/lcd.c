/*
 * File: lcd.c
 * Project: core
 * File Created: Monday, 29th June 2020 3:56:24 am
 * Author: Neklic (nieaowei@gmail.com)
 * -----
 * Last Modified: Monday, 29th June 2020 3:56:31 am
 * Modified By: Neklic (nieaowei@gmail.com>)
 * -----
 * Copyright 2020 Nekilc
 * -----
 * HISTORY:
 * Date      			By		Comments
 * --------------------	------	---------------------------------------------------------
 * 
 * 2020-06-29 4:15:24	Neklic	add newLCD function.
 * 
 * 2020-06-29 6:54:26	Neklic	add drawBlock function.
 * 
 * 2020-06-29 7:09:12	Neklic	add newPadding function.
 * 
 * 2020-06-29 7:47:07	Neklic	modify newBorder function.
 */
#include "lcd.h"
#include <stdlib.h>
#include <poll.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include "core.h"

// internal function.
void drawPoint(LCD lcd,int x,int y,Color color){
    memcpy(lcd->address+(x+800*y),&color,4);
}

void drawBlock(LCD lcd,Position position,Block block){
    Position start = newPosition(position->x,position->y);
    Position end = newPosition(position->x+block->size->width,position->y+block->size->height);
    int top=1;
    int topCount=0;
    int bottom=1;
    int bottomCount=0;
    int left=1;
    int leftCount=__INT32_MAX__;
    bool leftFlag = false;
    int right=1;
    int rightCount=__INT32_MAX__;
    bool rightFlag = false;

    char msg[256];

    // memset(msg,0,256);

    // sprintf(msg,"end Position(%d,%d),LCD->size(%d,%d),BlockSize(%d,%d)",end->x,end->y,lcd->size->width,lcd->size->height,block->size->width,block->size->height);
    // logD("LCD","drawBlock",msg,200);

    if (end->x> lcd->size->width || end->y > lcd->size->height || start->x <0 || start->y<0)
    {
        sprintf(msg,"faild,cause by size beyond lcd size. end Position(%d,%d),LCD->size(%d,%d)",end->x,end->y,lcd->size->width,lcd->size->height);
        logD("LCD","drawBlock",msg,400);
        return ;
    }
    

    for (; start->y < end->y; start->y++)
    {
        if (block->border!=NULL && block->border->borderType->type==DOTTED)
        {
            top = 1;
            topCount=__INT32_MAX__;
            bottom = 1;
            bottomCount=__INT32_MAX__;
        }
        
        
        for (start->x = position->x ;start->x < end->x; start->x++)
        {
            if (block->border!=NULL)
            {
                    if (start->y < position->y+block->border->padding->top)
                    {
                        if (block->border->borderType->type==DOTTED)
                        {
                            if ((start->x+1)%(block->border->padding->top+block->border->borderType->spacing+1)==0)
                            {
                                top+=2;
                                topCount = 1;
                                drawPoint(lcd,start->x,start->y,block->color);
                                continue;
                            }else if (topCount < block->border->borderType->spacing)
                            {
                                topCount++;
                                drawPoint(lcd,start->x,start->y,block->color);
                                continue;
                            }
                        
                        }
                        drawPoint(lcd,start->x,start->y,block->border->color);
                        continue;
                    }
                    
                    if (start->y > end->y - block->border->padding->bottom - 1)
                    {
                        if (block->border->borderType->type==DOTTED)
                        {
                            if ((start->x+1)%(block->border->padding->bottom+block->border->borderType->spacing+1)==0)
                            {
                                bottom+=2;
                                bottomCount = 1;
                                drawPoint(lcd,start->x,start->y,block->color);
                                continue;
                            }else if (bottomCount < block->border->borderType->spacing)
                            {
                                bottomCount++;
                                drawPoint(lcd,start->x,start->y,block->color);
                                continue;
                            }
                        
                        }
                        drawPoint(lcd,start->x,start->y,block->border->color);
                        continue;
                    }
                    
                
                    if (start->x < position->x + block->border->padding->left)
                    {
                        if (block->border->borderType->type==DOTTED)
                        {
                            
                            if ((start->y+1)%(block->border->borderType->spacing+block->border->padding->left+1)==0)
                            {
                                leftFlag = true;
                                leftCount = 0;
                                drawPoint(lcd,start->x,start->y,block->color);
                                continue;
                            }else if (leftFlag)
                            {
                                drawPoint(lcd,start->x,start->y,block->color);
                                continue;
                            }
                            
                        }
                        drawPoint(lcd,start->x,start->y,block->border->color);
                        continue;
                    }
                    
                
                    if (start->x > end->x - block->border->padding->right - 1)
                    {
                        if (block->border->borderType->type==DOTTED)
                        {
                            
                            if ((start->y+1)%(block->border->borderType->spacing+block->border->padding->right+1)==0)
                            {
                                rightFlag = true;
                                rightCount = 0;
                                drawPoint(lcd,start->x,start->y,block->color);
                                continue;
                            }else if (rightFlag)
                            {
                                drawPoint(lcd,start->x,start->y,block->color);
                                continue;
                            }
                            
                        }
                        drawPoint(lcd,start->x,start->y,block->border->color);
                        continue;
                    }
                    
            }
            drawPoint(lcd,start->x,start->y,block->color);
    
            
        }
        if (leftFlag)
        {
            leftCount++;
            if (leftCount==block->border->borderType->spacing)
            {
                left+=2;        
                leftFlag=false;
            }
            
        }
        if (rightFlag)
        {
            rightCount++;
            if (rightCount==block->border->borderType->spacing)
            {
                right+=2;        
                rightFlag=false;
            }
            
        }
        

    }
    free(start);
    free(end);
    start =NULL;
    end =NULL;
}

LCD newLCD(Color color,Size size){
    LCD lcd = (LCD) malloc(sizeof(lcd));

    lcd->size = size;

    int fd = open("/dev/ubuntu_lcd", O_RDWR);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}
    logD("LCD","newLCD","open lcd ok.",200);

	lcd->address = (unsigned int *)mmap(NULL, lcd->size->width*lcd->size->height*4, PROT_READ|PROT_WRITE, MAP_SHARED, fd,  0);
	if(MAP_FAILED == lcd->address)
	{
		perror("mmap");
		exit(1);
	}
    logD("LCD","newLCD","mmap lcd ok.",200);
    
    drawBlock(lcd,newPosition(0,0),newBlock(NULL,color,newSize(lcd->size->width,lcd->size->height)));
    
    return lcd;
}

