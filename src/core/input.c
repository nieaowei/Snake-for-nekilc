
#include "input.h"
#include "core.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>





LCDInput createLCDInput(const char *addr,void *(*run)(void *)){
    LCDInput l = (LCDInput)malloc(sizeof(LCDInputInfo));
    char msg[256];
    l->file_pointer = open(addr,O_RDONLY);
    if (l->file_pointer == -1)
    {
            logD("INPUT","createLCDInput","open file error.",400);
            free(l);
            return NULL;
    }
    sprintf(msg,"open file ok. file_p: %d",l->file_pointer);
    logD("INPUT","createLCDInput",msg,200);
    pthread_create(&l->threadId,NULL,run,l);

    return l;
}