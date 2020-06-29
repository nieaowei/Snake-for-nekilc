/*
 * File: core.c
 * Project: core
 * File Created: Monday, 29th June 2020 3:04:14 pm
 * Author: Neklic (nieaowei@gmail.com)
 * -----
 * Last Modified: Monday, 29th June 2020 3:07:28 pm
 * Modified By: Neklic (nieaowei@gmail.com>)
 * -----
 * Copyright 2020 Nekilc
 * -----
 * HISTORY:
 * Date      			By		Comments
 * --------------------	------	---------------------------------------------------------
 */

#include "core.h"
#include <stdio.h>
void logD(const char *tag,const char *funcName,const char *msg,const int code){
    char str[256];
    sprintf(str,"[%s][%s][%d]\t%s\t",tag,funcName,code,msg);
    perror(str);
}