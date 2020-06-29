/*
 * File: setting.h
 * Project: include
 * File Created: Monday, 29th June 2020 6:47:42 pm
 * Author: Neklic (nieaowei@gmail.com)
 * -----
 * Last Modified: Monday, 29th June 2020 6:48:21 pm
 * Modified By: Neklic (nieaowei@gmail.com>)
 * -----
 * Copyright 2020 Nekilc
 * -----
 * HISTORY:
 * Date      			By		Comments
 * --------------------	------	---------------------------------------------------------
 */

#ifndef __SETTING_H
#define __SETTING_H

#include "ui.h"

typedef struct
{
    Block background;
    Position start;
    Position end;
}screenSetting,*ScreenSetting;

ScreenSetting newScreenSetting(Block background);

#endif
