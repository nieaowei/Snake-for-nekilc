#ifndef __MOVE_H
#define __MOVE_H

#include "setting.h"
#include <pthread.h>


typedef struct
{
    pthread_t id;
}MoveInfo, *MoveThread;


MoveThread createMoveThread(void *run(),GameSetting g);

#endif