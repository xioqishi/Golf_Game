
#ifndef SELECT_LEVEL_H
#define SELECT_LEVEL_H
#include <stdio.h>
#include "Start.h"
#include <time.h>
#include <math.h>



//#define always_plays
//#include <graphics_lib.h>

//#define stick_man_centerX 100
//#define stick_man_centerY 450
typedef struct
    {
        bool flag;
        int holes;
    } Return_flag;


typedef struct
{
    bool confirmgoal_flag;
    int ret_cur_x;
    int ret_cur_y;
}  shoot_again_flag;

void select_level(int resX, int resY);


void sitck_man(int x_position, int y_position, int r );

//int choose_angle(int hand_point_X, int hand_point_Y);

shoot_again_flag fun_shoot(int shoot_x, int shoot_y, int speed, int play_holes,int wind);

void to_initial_mouse ();

void to_close_window();

void backGRD();

void theGoal();

int toConfirmGoal(int final_x, int final_y);

void theGoal(int hole_x, int hole_y);

void draw_a_hill(int hill_left_x, int hill_left_y, int hill_height);

void draw_water();

void draw_obstacles_sky(int start_x, int start_y);

Return_flag ClickToNext(int exit__flag, int play_holes);

int toAvoid_obstacles();

int avoid_water(int X, int Y);

//int switch_level(int play_holes);

int switch_level(int play_holes, int wind_number);

int avoid_sand(int x, int y);

int random_wind();

int avoid_hill(int X, int Y);

int avoid_obstacles_sky(int X, int Y, int start_x, int start_y);

int draw_star();

//void switch_avoid_level(int play_holes);

//void switch_avoid_level(int play_holes_c, int cur_posX_c, int cur_posY_c, bool air_wallFlag_c, bool ConfirmGoalFlag_c );
//void display_wind();

void display_wind(int wind_number );

bool quit_in_game();

void display_level_score(int shoot_times, int score, int play_holes );

void shoot_again();
#endif // SELECT_LEVEL_H
