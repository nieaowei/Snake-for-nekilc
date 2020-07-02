

#include "game.h"
#include "role.h"
#include <stdlib.h>
#include "core.h"
#include <unistd.h>
#include <stdio.h>
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

void addFoodForMap(Food *map,int row,int col){

}

void drawGameMap(LCD lcd,GameSetting gameSetting){
    char msg[256];
    sprintf(msg,"row: %d,col: %d,size: %d postion(%d,%d),size(%d,%d)",
        gameSetting->row,gameSetting->col,
        gameSetting->size,
        gameSetting->position->x,
        gameSetting->position->y,
        gameSetting->background->size->width,gameSetting->background->size->height
        );
    logD("GAME","drawGameMap",msg,200);
    Position former=NULL;
    do 
    {
        if (former!=NULL)
        {
            gameSetting->map[former->x][former->y] = 0;
            // drawBlock(lcd,former,gameSetting->snake->head);
            sprintf(msg,"foremer(%d,%d)",former->x,former->y);
            // logD("GAME","drawGameMap",msg,200);
            free(former);
            former = NULL;
        }
        gameSetting->map[gameSetting->snake->headP->x][gameSetting->snake->headP->y]=HEAD;
        gameSetting->map[gameSetting->snake->tailP->x][gameSetting->snake->tailP->y]=TAIL;
        // Position headp = newPosition(gameSetting->snake->headP->y * gameSetting->size + gameSetting->range->start->x,gameSetting->snake->headP->x*gameSetting->size+gameSetting->range->start->y);
        // Position tailp = newPosition(gameSetting->snake->tailP->y * gameSetting->size + gameSetting->range->start->x,gameSetting->snake->tailP->x*gameSetting->size+gameSetting->range->start->y);
        // printf("headp(%d,%d),tailp(%d,%d,)\n",headp->x,headp->y,tailp->x,tailp->y);
        // drawBlock(lcd,headp,gameSetting->snake->head);
        // drawBlock(lcd,tailp,gameSetting->snake->tail);
        for (int i = 0; i < gameSetting->snake->length-2; i++)
        {
            gameSetting->map[gameSetting->snake->bodyP[i]->x][gameSetting->snake->bodyP[i]->y]=BODY;
            // Position p = newPosition(gameSetting->snake->bodyP[i]->y*gameSetting->size+gameSetting->range->start->x,gameSetting->snake->bodyP[i]->x*gameSetting->size+gameSetting->range->start->y);
            // printf("bodyp(%d,%d)\n",p->x,p->y);
            // drawBlock(lcd,p,gameSetting->snake->body);
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
                default:
                    h = newPosition(j * gameSetting->size + gameSetting->range->start->x,i * gameSetting->size + gameSetting->range->start->x);
                    drawBlock(lcd,h,gameSetting->object);
                    break;
                }
                if (h!=NULL)
                {
                    free(h);
                }
                
            }
            
        }
        switch (gameSetting->lcdInput->currentKey)
        {
        case KEY_DOWN:
            gameSetting->snake->head->border = newBorder(newBorderType(DOTTED,2),white,newPadding(0,2,0,0));

            gameSetting->snake->direction = TOP_TO_BOTTOM;
            break;
        case KEY_UP:
            gameSetting->snake->head->border = newBorder(newBorderType(DOTTED,2),white,newPadding(2,0,0,0));

            gameSetting->snake->direction = BOTTOM_TO_TOP;
            break;
        case KEY_LEFT:
            gameSetting->snake->head->border = newBorder(newBorderType(DOTTED,3),white,newPadding(0,0,2,0));

            gameSetting->snake->direction = RIGHT_TO_LEFT;
            break;
        case KEY_RIGHT:
            gameSetting->snake->head->border = newBorder(newBorderType(DOTTED,3),white,newPadding(0,0,0,2));
            gameSetting->snake->direction = LEFT_TO_RIGHT;
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


