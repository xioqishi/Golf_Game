#include <stdio.h>
#include <math.h>
#include "Start.h"
#include <windows.h>
#include "Menu.h"
#include <conio.h>
#include <stdlib.h>
#include "select_level.h"
#include "Score.h"
#include <amio_lib.h>
#define start_music "\\golf_dennis\\start.wav"
#define fail_music "\\golf_dennis\\fail.wav"
//定义要显示的菜单
char *menu[] =
{
    "  EASY MODE  ",
    "  NORMAL MODE",
    "   RANKING   ",
    // "   SETTING",
    "    EXIT     ",
};
//定义结构体
CONSOLE_CURSOR_INFO cci;
int main(void)
{
    int Flag = 0; //Window resolution variables and flag for if exit has been clicked
    //int fgColor = 0; //foreground colour variable. 0 1 2 3, white, red, cyan, yellow respectively
    //int bgColor = 0; //background colour variable. 0 1 2 3, black, blue, lightgray, magenta respectively
    //int difficulty = 0; // difficulty determines how gameplay works. 0 is easy, 1 is medium, 2 is hard
    //Easy - hole with no wind; Medium - hole with wind; Hard - target with wind
//    int button_y = 160;
//    int button_x = 360;
    // midi_start();

    printf("Welcome to Golf world!\n");
    system("pause");
    //loop until exit game is pressed
//    int i;

    //int keyinput;
    //midi_start();
//    char get_char;
    int index = 0 ;
    HANDLE hOut;
    SetConsoleTitleA(TITLE);
    //获取当前的句柄---设置为标准输出句柄
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //获取光标信息
    GetConsoleCursorInfo(hOut, &cci);
    //设置光标大小
    cci.dwSize = 1;
    //设置光标不可见 FALSE
    cci.bVisible =  0;
    //设置(应用)光标信息
    SetConsoleCursorInfo(hOut, &cci);
    while(Flag == 0 )
    {
        int exit_flag = false;
        int stick_man_centerX = 100;
        int stick_man_centerY = 450;
        int hand_point_X = 120;
        int hand_point_Y = 510;  ///原本为470
//    float stop_speed;
        int play_holes ;
        int shoot_x = 0, shoot_y = 0;
        int speed = 0;
        bool forceflag = false;
        int ret ;
        char display_score[50];
//    bool gameflag;
        Return_flag receive_flag;
        shoot_again_flag receive_shoot_flag;
        //int play_holes ;
//
        showmenu(hOut, menu, NR(menu), index);
        ret = choose_item(&index, NR(menu));
        if(ret == ESC)
            break ;
        if(ret == ENTER)
        {
            switch(index)
            {
            case 0:     //easy mode
                hand_point_X = 120;
                while (exit_flag == false )
                {
                    midi_start();
                    /*midi_note(60,1,100);
                    pause(2000);
                     midi_note(60, 2, 100);
                            pause(2000);
                            midi_note(60, 2, 0);
                            //midi_close();*/
                    int score = 0;
                    initwindow(800,600);
                    update_display();
                    to_initial_mouse();
                    int sleep_speed;
                    int wind_number;
                    int shoot_times = 0;
                    int a[10]= {0};
                    backGRD();
                    theGoal(760,510);
                    sitck_man(stick_man_centerX, stick_man_centerY,10) ;
                    display_level_score(shoot_times, score, play_holes );
                    update_display();
                    PlaySound(start_music, NULL,SND_FILENAME | SND_ASYNC);
                    pause(1500);
                    for (play_holes = 1; play_holes <= 9 ; play_holes++)   //玩10次场景
                    {
                        for (wind_number =5; wind_number <= 9; wind_number++)
                        {
                            a[wind_number] = random_wind();
                            // printf("the wind number is %d\n", a[wind_number]);
                        }
//                        float X_stop_point = 0;
                        sitck_man(stick_man_centerX, stick_man_centerY,10) ;
                        stick_man_centerX = hand_point_X - 20;
                        if (hand_point_X > 800 || hand_point_X < 120 )
                        {
                            hand_point_X = 120;
                            outtextxy(250,250,"The ball is out of left window");
                            // update_display();
                        }
                        int i =50;
                        bool gameflag = true;
                        int change_Y =0;
                        sleep_speed = 30 ;
                        while (gameflag == true)              /**********选角度*****************/
                        {
                            i--;
                            backGRD();
                            theGoal(760,510);
                            sitck_man(stick_man_centerX, stick_man_centerY,10) ;
                            display_level_score(shoot_times, score, play_holes );
                            outtextxy(250,250,"Click left mouse to confirm shoot angle");
                            change_Y = (-sqrt((2500-pow((i), 2))))+ hand_point_Y;  // 角度y的公式
                            double draw_arrow_angle = (double) atan2(-change_Y+510.0, i);  ///很重要算角度
                            // printf(" *******%f\n", draw_arrow_angle);
                            //setcolor(BLUE);
                            /// filled_circle(hand_point_X+i, change_Y,5, CYAN);    //变换的轨迹
                            line( hand_point_X+i, change_Y,(hand_point_X + i - (int)(15 * sin(draw_arrow_angle + M_PI/3))), (change_Y - (int)(15 * cos(draw_arrow_angle + M_PI/3))),2);  ///test
                            line( hand_point_X+i, change_Y,(hand_point_X + i + (int)(15 * sin(draw_arrow_angle - M_PI/3))), (change_Y + (int)(15 * cos(draw_arrow_angle - M_PI/3))),2);  ///test
                            moveto(hand_point_X+i, change_Y);
                            setcolor(WHITE);
                            lineto(hand_point_X, hand_point_Y, 4);   //把轨迹画出来
                            switch_level(play_holes, a[play_holes]);
                            update_display();
                            cleardevice();
                            Sleep(sleep_speed);
                            if (i==0)
                            {
                                i = 50;
                            }
                            if (check_if_event())     //检查是否有事件
                            {
                                wait_for_event();
                                if(event_close_display())
                                {
                                    play_holes = 15;
                                    //printf("want to break");
                                    exit_flag = true;
                                    break;
                                }
                                else if (event_mouse_button_down())
                                {
                                    if (event_mouse_left_button_down())
                                    {
                                        shoot_x = hand_point_X+i;
                                        //shoot_x = i;
                                        shoot_y = change_Y;
                                        // printf("%d %d\n",shoot_x, shoot_y);
                                        gameflag = false;
                                        forceflag = true;
                                    }
                                }
                            }
                        }
                        int j = 0;
                        /* allow mouse operations */
                        backGRD();
                        theGoal(760,510);
                        al_draw_line(0, 0, 100, 0, al_map_rgb(255,255,0), 20);
                        sitck_man(stick_man_centerX, stick_man_centerY,10);
                        line(hand_point_X, hand_point_Y, shoot_x, shoot_y, 4);
                        double draw_arrow_angle_c = (double) atan2(-shoot_y + hand_point_Y, shoot_x - hand_point_X);  ///很重要算角度
//                        printf("copy draw_arrow_angle is %lf\n", draw_arrow_angle_c);
                        line( hand_point_X+i, change_Y,(hand_point_X + i - (int)(15 * sin(draw_arrow_angle_c + M_PI/3))), (change_Y - (int)(15 * cos(draw_arrow_angle_c + M_PI/3))),2);  ///test
                        line( hand_point_X+i, change_Y,(hand_point_X + i + (int)(15 * sin(draw_arrow_angle_c - M_PI/3))), (change_Y + (int)(15 * cos(draw_arrow_angle_c - M_PI/3))),2);  ///test
                        while (forceflag ==true)                  /**********选力度*****************/
                        {
                            al_draw_line(0, 0, j, 0, al_map_rgb(255,0,0),20);
                            display_level_score(shoot_times, score, play_holes );
                            outtextxy(250,250,"Click left mouse to confirm shoot speed.");
                            update_display();
                            pausefor(sleep_speed);
                            j++;
                            if (j==100)
                            {
                                j=0;
                                al_draw_line(0, 0, 100, 0, al_map_rgb(255,255,0),20);
                            }
                            switch_level(play_holes, a[play_holes]);
                            if (check_if_event())     //检查是否有事件
                            {
                                wait_for_event();
                                if(event_close_display())
                                {
                                    play_holes = 15;
                                    // printf("want to break");
                                    exit_flag = true;
                                    break;
                                }
                                else  if (event_mouse_button_down())
                                {
                                    if (event_mouse_left_button_down())
                                    {
                                        speed = j;
                                        forceflag = false;
                                    }
                                }
                            }
                        }
                        receive_shoot_flag= fun_shoot( shoot_x,  shoot_y,  speed, play_holes, a[play_holes]);
                        bool score_flag = receive_shoot_flag.confirmgoal_flag;
                        //printf("the X is %d and the Y is %d", receive_shoot_flag.ret_cur_x, receive_shoot_flag.ret_cur_y);
                        hand_point_X = receive_shoot_flag.ret_cur_x;
                        // stick_man_centerY = hand_point_Y - 60;
//hand_point_Y = receive_shoot_flag.ret_cur_y;
                        if (hand_point_X > 800 || hand_point_X < 120)
                        {
                            hand_point_X = 120;
                            outtextxy(250,250,"The ball is missing!");
                            // update_display();
                        }
                        if ((score_flag) != true)
                        {
                            play_holes--;
                            shoot_times++;
//                            printf("shoot_times is %d\n", shoot_times);
                        }
                        else if (score_flag == true && shoot_times <= 3)
                        {
                            midi_note(60,8,100);
                            pause(1500);
                            //midi_note(60,2,100);
                            //pause(2000);
                            midi_note(60,2,0);
                            score += final_point_fun(shoot_times, score_flag);
                            shoot_times = 0;
                        }
                        else if (score_flag == true && shoot_times > 3)
                        {
                            midi_note(60,8,100);

                            midi_note(60,2,0);
                            pause(1500);
                            shoot_times = 0;
                        }
                        display_level_score(shoot_times, score, play_holes+1 );
                        update_display();
//                        printf("zui zhong de fen %d\n", score);
                        if (play_holes == 9)
                        {
                            compare_point(score);
                            cleardevice();
                            sprintf(display_score,"Your Point is %d. Click to show Top 5!",score);
                            midi_note(8,1,30);
                            pause(500);
                            outtextxy(250,250,display_score);
                            update_display();
                            ClickToNext(exit_flag,play_holes);
                            cleardevice();
                            display_name();
                            initmouse();
                            /* create an event queue */
                            create_event_queue();
                            /* register display and mouse as event sources */
                            reg_display_events();
                            reg_mouse_events();
                            while (true)
                            {
                                if (check_if_event())
                                {
                                    /* wait for event  */
                                    wait_for_event();
                                    if (event_close_display())
                                    {
                                        midi_close();
                                        closegraph();
//                                        printf("579 line");
                                        break;
                                    }
                                }
                            }
                            exit_flag = true;
                        }
                        if (play_holes < 9)
                        {
                            receive_flag = ClickToNext(exit_flag,play_holes);
                            play_holes =  receive_flag.holes;
                            exit_flag = receive_flag.flag;
                            system("cls");
                        }
                    }
                    midi_close();
                    closegraph();
                    /*while (get_char != ESC);
                            {
                                system("cls");
                                printf("please use arrow to control game\n");
                                fflush(stdin);
                                get_char = getch();
                                //system("pause");
                            } */
                    //closegraph();
                }
                break ;
            case 1://normal mode

                while (exit_flag == false )
                {
                    midi_start();
                    hand_point_X = 120;
                    int score = 0;
                    initwindow(800,600);
                    update_display();
                    to_initial_mouse();
                    int sleep_speed;
                    int wind_number;
                    int shoot_times = 0;
                    int a[10]= {0};
                    backGRD();
                    theGoal(760,510);
                    sitck_man(stick_man_centerX, stick_man_centerY,10) ;
                    display_level_score(shoot_times, score, play_holes );
                    update_display();
                    PlaySound(start_music, NULL,SND_FILENAME | SND_ASYNC);
                    pause(1500);
                    for (play_holes = 1; play_holes <= 9 ; play_holes++)   //玩10次场景
                    {
                        for (wind_number =5; wind_number <= 9; wind_number++)
                        {
                            a[wind_number] = random_wind();
//                            printf("the wind number is %d\n", a[wind_number]);
                        }
                        //float X_stop_point = 0;
                        sitck_man(stick_man_centerX, stick_man_centerY,10) ;
                        stick_man_centerX = hand_point_X - 20;
                        if (hand_point_X > 800 || hand_point_X < 120 )
                        {
                            hand_point_X = 120;
                            outtextxy(250,250,"The ball is out of left window");
                            // update_display();
                        }
                        int i =50;
                        bool gameflag = true;
                        int change_Y =0;
                        sleep_speed = 40 - play_holes*5;
                        if (sleep_speed < 10)
                        {
                            sleep_speed = 10;
                        }
                        while (gameflag == true)              /**********选角度*****************/
                        {
                            i--;
                            backGRD();
                            theGoal(760,510);
                            sitck_man(stick_man_centerX, stick_man_centerY,10) ;
                            display_level_score(shoot_times, score, play_holes );
                            outtextxy(250,250,"Click left mouse to confirm shoot angle");
                            change_Y = (-sqrt((2500-pow((i), 2))))+ hand_point_Y;  // 角度y的公式
                            double draw_arrow_angle = (double) atan2(-change_Y+510.0, i);  ///很重要算角度
                            /// filled_circle(hand_point_X+i, change_Y,5, CYAN);    //变换的轨迹
                            ///al_draw_filled_triangle(hand_point_X+i, change_Y,)
                            line( hand_point_X+i, change_Y,(hand_point_X + i - (int)(15 * sin(draw_arrow_angle + M_PI/3))), (change_Y - (int)(15 * cos(draw_arrow_angle + M_PI/3))),2);  ///test
                            line( hand_point_X+i, change_Y,(hand_point_X + i + (int)(15 * sin(draw_arrow_angle - M_PI/3))), (change_Y + (int)(15 * cos(draw_arrow_angle - M_PI/3))),2);  ///test
                            moveto(hand_point_X+i, change_Y);
                            setcolor(WHITE);
                            lineto(hand_point_X, hand_point_Y, 4);   //把轨迹画出来
                            switch_level(play_holes, a[play_holes]);
                            update_display();
                            cleardevice();
                            Sleep(sleep_speed);
                            if (i==0)
                            {
                                i = 50;
                            }
                            if (check_if_event())     //检查是否有事件
                            {
                                wait_for_event();
                                if(event_close_display())
                                {
                                    play_holes = 15;
//                                    printf("want to break");
                                    exit_flag = true;
                                    break;
                                }
                                else if (event_mouse_button_down())
                                {
                                    if (event_mouse_left_button_down())
                                    {
                                        shoot_x = hand_point_X+i;
                                        shoot_y = change_Y;
//                                        printf("%d %d\n",shoot_x, shoot_y);
                                        gameflag = false;
                                        forceflag = true;
                                    }
                                }
                            }
                        }
                        int j = 0;
                        /* allow mouse operations */
                        backGRD();
                        theGoal(760,510);
                        al_draw_line(0, 0, 100, 0, al_map_rgb(255,255,0), 20);
                        sitck_man(stick_man_centerX, stick_man_centerY,10);
                        line(hand_point_X, hand_point_Y, shoot_x, shoot_y, 4);
                        double draw_arrow_angle_c = (double) atan2(-shoot_y + hand_point_Y, shoot_x - hand_point_X);  ///很重要算角度
//                        printf("copy draw_arrow_angle is %lf\n", draw_arrow_angle_c);
                        line( hand_point_X+i, change_Y,(hand_point_X + i - (int)(15 * sin(draw_arrow_angle_c + M_PI/3))), (change_Y - (int)(15 * cos(draw_arrow_angle_c + M_PI/3))),2);  ///test
                        line( hand_point_X+i, change_Y,(hand_point_X + i + (int)(15 * sin(draw_arrow_angle_c - M_PI/3))), (change_Y + (int)(15 * cos(draw_arrow_angle_c - M_PI/3))),2);  ///test
                        while (forceflag ==true)                  /**********选力度*****************/
                        {
                            al_draw_line(0, 0, j, 0, al_map_rgb(255,0,0),20);
                            display_level_score(shoot_times, score, play_holes );
                            outtextxy(250,250,"Click left mouse to confirm shoot speed.");
                            update_display();
                            pausefor(sleep_speed);
                            j++;
                            if (j==100)
                            {
                                j=0;
                                al_draw_line(0, 0, 100, 0, al_map_rgb(255,255,0),20);
                            }
                            switch_level(play_holes, a[play_holes]);
                            if (check_if_event())     //检查是否有事件
                            {
                                wait_for_event();
                                if(event_close_display())
                                {
                                    play_holes = 15;
//                                    printf("want to break");
                                    exit_flag = true;
                                    break;
                                }
                                else  if (event_mouse_button_down())
                                {
                                    if (event_mouse_left_button_down())
                                    {
                                        speed = j;
                                        forceflag = false;
                                    }
                                }
                            }
                        }
                        receive_shoot_flag= fun_shoot( shoot_x,  shoot_y,  speed, play_holes, a[play_holes]);
                        bool score_flag = receive_shoot_flag.confirmgoal_flag;
                        // printf("the X is %d and the Y is %d", receive_shoot_flag.ret_cur_x, receive_shoot_flag.ret_cur_y);
                        hand_point_X = receive_shoot_flag.ret_cur_x;
                        if (hand_point_X > 800 || hand_point_X < 120)
                        {
                            hand_point_X = 120;
                            outtextxy(250,250,"The ball is missing!");
                            // update_display();
                        }
                        if ((score_flag) == false)
                        {
                            play_holes--;
                            shoot_times++;
//                            printf("shoot_times is %d\n", shoot_times);
                            if (shoot_times >= 3)
                            {
                                outtextxy(200,150, "You failed and play next level!");
                                PlaySound(fail_music, NULL,SND_FILENAME | SND_ASYNC);
                                pause(1000);
                                update_display();
                                play_holes++;
                                shoot_times = 0;
                                hand_point_X = 120;
                            }
                        }
                        else if ( (score_flag) == true)
                        {
                            midi_note(60,8,100);

                            midi_note(60,2,0);
                            //play_holes++;
                            pause(1500);
                            score += final_point_fun(shoot_times, score_flag);
                            shoot_times = 0;
                        }
                        display_level_score(shoot_times, score, play_holes+1 );
                        update_display();
                        //printf("zui zhong de fen %d\n", score);
                        if (play_holes == 9)
                        {
                            compare_point(score);
                            cleardevice();
                            sprintf(display_score,"Your Point is %d. Click to show Top 5!",score);
                            midi_note(8,1,30);
                            pause(500);
                            outtextxy(250,250,display_score);
                            update_display();
                            ClickToNext(exit_flag,play_holes);
                            cleardevice();
                            display_name();
                            initmouse();
                            /* create an event queue */
                            create_event_queue();
                            /* register display and mouse as event sources */
                            reg_display_events();
                            reg_mouse_events();
                            while (true)
                            {
                                if (check_if_event())
                                {
                                    /* wait for event  */
                                    wait_for_event();
                                    if (event_close_display())
                                    {
                                        midi_close();
                                        closegraph();
                                        break;
                                    }
                                }
                            }
                            exit_flag = true;
                        }
                        if (play_holes < 9)
                        {
                            receive_flag = ClickToNext(exit_flag,play_holes);
                            play_holes =  receive_flag.holes;
                            exit_flag = receive_flag.flag;
                            system("cls");
                        }
                    }
                    midi_close();
                    closegraph();
                }
                break ;
            case 2:
            {
                initwindow(800,600);
                //  compare_point(110);
                display_name();
                initmouse();
                /* create an event queue */
                create_event_queue();
                /* register display and mouse as event sources */
                reg_display_events();
                reg_mouse_events();
                while (true)
                {
                    if (check_if_event())
                    {
                        /* wait for event  */
                        wait_for_event();
                        if (event_close_display())
                        {
                            closegraph();
//                            printf("579 line");
                            break;
                        }
                    }
                }
            }
            break ;  	//ranking
            //case 3:
            //  break ;  // setting
            case 3:                      //exit
            {
                Flag = 1;
                system("cls");
                printf("Game over");
                break;
            }
            }
        }
    }
    return 0;
}
