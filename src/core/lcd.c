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

// internal function.
void drawPoint(LCD lcd,int x,int y,Color color){
    memcpy(lcd->address+(x+800*y),&color,4);
}

void drawBlock(LCD lcd,Position position,Block block){
    Position start = newPosition(position->x,position->y);
    Position end = newPosition(position->x+block->size->width,position->y+block->size->height);
    for (; start->y < end->y; start->y++)
    {
        for (start->x = position->x ;start->x < end->x; start->x++)
        {
            if (block->border!=NULL)
            {
                    if (start->y < position->y+block->border->padding->top)
                    {
                        drawPoint(lcd,start->x,start->y,block->border->color);
                        continue;
                    }
                    
                    if (start->y > end->y - block->border->padding->bottom - 1)
                    {
                        drawPoint(lcd,start->x,start->y,block->border->color);
                        continue;
                    }
                    
                
                    if (start->x < position->x + block->border->padding->left)
                    {
                        drawPoint(lcd,start->x,start->y,block->border->color);
                        continue;
                    }
                    
                
                    if (start->x > end->x - block->border->padding->right - 1)
                    {
                        drawPoint(lcd,start->x,start->y,block->border->color);
                        continue;
                    }
                    
            }
            drawPoint(lcd,start->x,start->y,block->color);
    
            
        }
    }
    
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

	lcd->address = (unsigned int *)mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, fd,  0);
	if(MAP_FAILED == lcd->address)
	{
		perror("mmap");
		exit(1);
	}
    
    drawBlock(lcd,newPosition(0,0),newBlock(NULL,color,newSize(lcd->size->width,lcd->size->height)));
    
    return lcd;
}

