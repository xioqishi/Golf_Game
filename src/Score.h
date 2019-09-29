#ifndef __START_H__
#define __START_H__
#include <stdio.h>
#include <string.h>
#include "select_level.h"
//#include <graphics_lib.h>
int final_point_fun(int shoot_times, bool score_flag );
typedef struct
{
    int score;
    char name[20];
} Name;
Name  RankName[5];
void Fun_rank();
void  display_name();
void compare_point(int point);
#endif