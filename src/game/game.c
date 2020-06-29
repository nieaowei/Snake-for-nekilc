

#include "game.h"
#include "role.h"
#include <stdlib.h>
#include "core.h"
#include <stdio.h>

void drawGameScreen(LCD lcd ,ScreenSetting screenSetting){

    char msg[256];
    sprintf(msg,"row: %d,col: %d,size: %d postion(%d,%d),size(%d,%d)",
        screenSetting->row,screenSetting->col,
        screenSetting->size,
        screenSetting->position->x,
        screenSetting->position->y,
        screenSetting->background->size->width,screenSetting->background->size->height
        );
    logD("GAME","drawGameScreen",msg,200);
    drawBlock(lcd,screenSetting->position,screenSetting->background);
    drawBlock(lcd,screenSetting->range->start,newBlock(newBorder(newBorderType(SOLID,0),brown,newPadding(0,2,0,2)),orange,newSize(screenSetting->size,screenSetting->size)));
}

void addFoodForMap(Food *map,int row,int col){

}

void paintMap(Food food){
    
}


