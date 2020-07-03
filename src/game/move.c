#include "move.h"
#include <stdlib.h>

MoveThread createMoveThread(void *(*run)(void *),GameSetting g){
    MoveThread m = (MoveThread)malloc(sizeof(MoveInfo));
    pthread_create(&m->id,NULL,run,g);
    return m;
}