

#include "game.h"
#include "role.h"
#include <stdlib.h>
#include "core.h"
#include <stdio.h>

// draw game area.
void drawGameScreen(LCD lcd ,GameSetting GameSetting){
    char msg[256];
    sprintf(msg,"row: %d,col: %d,size: %d postion(%d,%d),size(%d,%d)",
        GameSetting->row,GameSetting->col,
        GameSetting->size,
        GameSetting->position->x,
        GameSetting->position->y,
        GameSetting->background->size->width,GameSetting->background->size->height
        );
    logD("GAME","drawGameScreen",msg,200);
    drawBlock(lcd,GameSetting->position,GameSetting->background);
}

void addFoodForMap(Food *map,int row,int col){

}

void drawGameMap(LCD lcd,GameSetting GameSetting){
    while (1)
    {
        /* code */
    }
    
}


