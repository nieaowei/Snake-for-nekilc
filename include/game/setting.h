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
#include "role.h"
#include "input.h"

typedef struct
{
    Block background;//游戏背景
    PositionRange range;//游戏区域
    Position position;//屏幕位置
    Block object;
    int size;//物体大小
    int row;//行数
    int col;//列数
    int **map;//地图矩阵
    Snake snake;
    int scorce;
    int foodLen;
    pthread_mutex_t foodMux;
    Position foods[10];//max food number.foremer will be covered.
    int foodsIsFull;
    int foodKinds[10];
    LCDInput lcdInput;

}gameSettingInfo,*GameSetting;

GameSetting newGameSetting(Block background,Position position,int size,LCDInput lcdInput);

#endif
