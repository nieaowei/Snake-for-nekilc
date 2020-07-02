
#include "input.h"
#include "core.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>



void *getInuptKey(void *arg){
    struct input_event ev;
    char msg[256];
    LCDInput lcdInput = (LCDInput)arg;
    while (1)
    {
        int re = read(lcdInput->file_pointer,&ev,sizeof(ev));
        sprintf(msg,"get key status: %d",re);
        // logD("INPUT","getInuptKey",msg,200);
        if (ev.type==EV_KEY)
        {
            if (ev.value==1)
            {
                sprintf(msg,"key code: %d",ev.code);
                logD("INPUT","getInuptKey",msg,200);
                // return ev.code;
                lcdInput->currentKey = ev.code;
            }
            
        }
    }
    // return -1;
}

LCDInput createLCDInput(const char *addr){
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
    pthread_create(&l->threadId,NULL,getInuptKey,l);

    return l;
}