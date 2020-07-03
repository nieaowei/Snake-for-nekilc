

#include "game.h"
#include "role.h"
#include <stdlib.h>
#include "core.h"
#include <unistd.h>
#include <stdio.h>
#include "random.h"

// draw game area.
void drawGameScreen(LCD lcd ,GameSetting gameSetting){
    char msg[256];
    sprintf(msg,"row: %d,col: %d,size: %d postion(%d,%d),size(%d,%d)",
        gameSetting->row,gameSetting->col,
        gameSetting->size,
        gameSetting->position->x,
        gameSetting->position->y,
        gameSetting->background->size->width,gameSetting->background->size->height
        );
    logD("GAME","drawGameScreen",msg,200);
    drawBlock(lcd,gameSetting->position,gameSetting->background);
}

// void addFoodForMap(Food *map,int row,int col){

// }

void drawGameMap(LCD lcd,GameSetting gameSetting){
    char msg[256];
    sprintf(msg,"game area: start(%d,%d),end(%d,%d)",
        gameSetting->range->start->x,gameSetting->range->start->y,
        gameSetting->range->end->x,gameSetting->range->end->y
        );
    logD("GAME","drawGameMap",msg,200);
    Border topBorder = newBorder(newBorderType(DOTTED,2),white,newPadding(2,0,0,0));
    Border bottomBorder = newBorder(newBorderType(DOTTED,2),white,newPadding(0,2,0,0));
    Border leftBorder = newBorder(newBorderType(DOTTED,3),white,newPadding(0,0,2,0));
    Border rightBorder = newBorder(newBorderType(DOTTED,3),white,newPadding(0,0,0,2));
    Position former = NULL;
    do 
    {
        if (former!=NULL)
        {
            gameSetting->map[former->x][former->y] = 0;
            // drawBlock(lcd,former,gameSetting->snake->head);
            // sprintf(msg,"foremer(%d,%d)",former->x,former->y);
            // logD("GAME","drawGameMap",msg,200);
            free(former);
            former = NULL;
        }
        gameSetting->map[gameSetting->snake->headP->x][gameSetting->snake->headP->y]=HEAD;
        gameSetting->map[gameSetting->snake->tailP->x][gameSetting->snake->tailP->y]=TAIL;
        
        for (int i = 0; i < gameSetting->snake->length-2; i++)
        {
            gameSetting->map[gameSetting->snake->bodyP[i]->x][gameSetting->snake->bodyP[i]->y]=BODY;
            
        }
        int tempFoodLen = gameSetting->foodLen;

        for (int i = 0; i < tempFoodLen; i++)
        {
            int kind = random_between(1,5);
            switch (kind)
            {
            case 1:
                gameSetting->map[gameSetting->foods[i]->x][gameSetting->foods[i]->y] = FOOD_1;
                break;
            case 2:
                gameSetting->map[gameSetting->foods[i]->x][gameSetting->foods[i]->y] = FOOD_2;
                break;
            case 3:
                gameSetting->map[gameSetting->foods[i]->x][gameSetting->foods[i]->y] = FOOD_3;
                break;
            case 4:
                gameSetting->map[gameSetting->foods[i]->x][gameSetting->foods[i]->y] = FOOD_4;
                break;
            case 5:
                gameSetting->map[gameSetting->foods[i]->x][gameSetting->foods[i]->y] = FOOD_5;
                break;
            default:
                break;
            }
        }
        
        for (int i = 0; i < gameSetting->row; i++)
        {
            for (int j = 0; j < gameSetting->col; j++)
            {
                Position h  =   NULL;
                switch (gameSetting->map[i][j])
                {
                case HEAD:
                    h = newPosition(j * gameSetting->size + gameSetting->range->start->x,i * gameSetting->size + gameSetting->range->start->x);
                    drawBlock(lcd,h,gameSetting->snake->head);
                    break;
                case TAIL:
                    h = newPosition(j * gameSetting->size + gameSetting->range->start->x,i * gameSetting->size + gameSetting->range->start->x);
                    drawBlock(lcd,h,gameSetting->snake->tail);
                    former = newPosition(i,j);
                    break;
                case BODY:
                    h = newPosition(j * gameSetting->size + gameSetting->range->start->x,i * gameSetting->size + gameSetting->range->start->x);
                    drawBlock(lcd,h,gameSetting->snake->body);
                    break;
                case FOOD_1:
                    h = newPosition(j * gameSetting->size + gameSetting->range->start->x,i * gameSetting->size + gameSetting->range->start->x);
                    drawBlock(lcd,h,food_1->block);
                    break;
                case FOOD_2:
                    h = newPosition(j * gameSetting->size + gameSetting->range->start->x,i * gameSetting->size + gameSetting->range->start->x);
                    drawBlock(lcd,h,food_2->block);
                    break;
                case FOOD_3:
                    h = newPosition(j * gameSetting->size + gameSetting->range->start->x,i * gameSetting->size + gameSetting->range->start->x);
                    drawBlock(lcd,h,food_3->block);
                    break;
                case FOOD_4:
                    h = newPosition(j * gameSetting->size + gameSetting->range->start->x,i * gameSetting->size + gameSetting->range->start->x);
                    drawBlock(lcd,h,food_4->block);
                    break;
                case FOOD_5:
                    h = newPosition(j * gameSetting->size + gameSetting->range->start->x,i * gameSetting->size + gameSetting->range->start->x);
                    drawBlock(lcd,h,food_5->block);
                    break;
                default:
                    h = newPosition(j * gameSetting->size + gameSetting->range->start->x,i * gameSetting->size + gameSetting->range->start->x);
                    drawBlock(lcd,h,gameSetting->object);
                    break;
                }
                // if (h!=NULL)
                {
                    free(h);
                    h=NULL;
                }
                
            }
            
        }
        switch (gameSetting->lcdInput->currentKey)
        {
        case KEY_DOWN:
            if (gameSetting->snake->direction!=BOTTOM_TO_TOP)
            {
                gameSetting->snake->head->border = bottomBorder;
                gameSetting->snake->direction = TOP_TO_BOTTOM;
            }
            break;
        case KEY_UP:
            if (gameSetting->snake->direction!=TOP_TO_BOTTOM)
            {
                gameSetting->snake->head->border = topBorder;
                gameSetting->snake->direction = BOTTOM_TO_TOP;
            }
            
            break;
        case KEY_LEFT:
            if (gameSetting->snake->direction!=LEFT_TO_RIGHT)
            {
                gameSetting->snake->head->border = leftBorder;
                gameSetting->snake->direction = RIGHT_TO_LEFT;
            }
            
            break;
        case KEY_RIGHT:
            if (gameSetting->snake->direction!=RIGHT_TO_LEFT)
            {
                gameSetting->snake->head->border = rightBorder;
                gameSetting->snake->direction = LEFT_TO_RIGHT;
            }
            
            break;
        case KEY_Q:
            exit(0);
            break;
        default:
            break;
        }
        usleep(1000);
    }while(1);
    
}


