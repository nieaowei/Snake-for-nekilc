

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
    Position h = newPosition(0,0);
    do 
    {
        if (former!=NULL)
        {
            gameSetting->map[former->x][former->y] = 0;
            free(former);
            former = NULL;
        }
        gameSetting->map[gameSetting->snake->headP->x][gameSetting->snake->headP->y]=HEAD;
        gameSetting->map[gameSetting->snake->tailP->x][gameSetting->snake->tailP->y]=TAIL;
        //avoid competition
        int length = gameSetting->snake->length;
        for (int i = 0; i < length-2; i++)
        {
            // sprintf(msg,"body: %d,",i);
            // logD("GAME","drawGameMap",msg,200);
            gameSetting->map[gameSetting->snake->bodyP[i]->x][gameSetting->snake->bodyP[i]->y]=BODY;
        }
        //avoid competition
        pthread_mutex_lock(&gameSetting->foodMux);

        int tempFoodLen = gameSetting->foodLen;
        if (gameSetting->foodsIsFull)
        {
            /* code */
            tempFoodLen = 10;
        }
        // printf("%d\n",tempFoodLen);
        
        for (int i = 0; i < tempFoodLen; i++)
        {
            // int kind = random_between(1,5);
            // sprintf(msg,"food: %d,%d,%d",i,gameSetting->foods[i]->x,gameSetting->foods[i]->y);
            // logD("GAME","drawGameMap",msg,200);
            // printf("%d,%d\n",gameSetting->foods[i]->x,gameSetting->foods[i]->y);
            if (gameSetting->foods[i]->x >=0 && gameSetting->foods[i]->y >=0)
            {
                switch (gameSetting->foodKinds[i])
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
                    gameSetting->map[gameSetting->foods[i]->x][gameSetting->foods[i]->y] = 0;;
                    break;
                }
            }
            
            

        }
            pthread_mutex_unlock(&gameSetting->foodMux);

        
        for (int i = 0; i < gameSetting->row; i++)
        {
            for (int j = 0; j < gameSetting->col; j++)
            {
                // Position h  =   NULL;
                h->x = j * gameSetting->size + gameSetting->range->start->x;
                h->y = i * gameSetting->size + gameSetting->range->start->x;
                // sprintf(msg,"map : (%d,%d)",h->x,h->y);
                // logD("GAME","drawGameMap",msg,200);
                switch (gameSetting->map[i][j])
                {
                case HEAD:
                    
                    drawBlock(lcd,h,gameSetting->snake->head);
                    break;
                case TAIL:
                    drawBlock(lcd,h,gameSetting->snake->tail);
                    former = newPosition(i,j);
                    break;
                case BODY:
                    drawBlock(lcd,h,gameSetting->snake->body);
                    break;
                case FOOD_1:
                    drawBlock(lcd,h,food_1->block);
                    break;
                case FOOD_2:
                    drawBlock(lcd,h,food_2->block);
                    break;
                case FOOD_3:
                    drawBlock(lcd,h,food_3->block);
                    break;
                case FOOD_4:
                    drawBlock(lcd,h,food_4->block);
                    break;
                case FOOD_5:
                    drawBlock(lcd,h,food_5->block);
                    break;
                default:
                    drawBlock(lcd,h,gameSetting->object);
                    break;
                }
                // if (h!=NULL)
                // {
                //     free(h);
                //     h=NULL;
                // }
                
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


