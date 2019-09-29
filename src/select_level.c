#include "select_level.h"
void select_level(int resX, int resY)
{
    initwindow(resX, resY);
    update_display();
}
void backGRD()
{
    al_draw_filled_rectangle(0,0,800,500, al_map_rgb(135,206,235));  //sky
    //filled_rectangle(0,0,800,500, al_map_rgb(151,255,255));
    al_draw_filled_rectangle(0, 500, 800, 600, al_map_rgb(155,205,155));  //grass
    //filled_rectangle(0, 500, 800, 600, al_map_rgb(155,205,155));
    //update_display();
}
void sitck_man(int x_position, int y_position, int r )
{
    al_draw_circle(x_position, y_position, 12, al_map_rgb(255, 228,225),3);
    // filled_circle(x_position + 2 , y_position - 5,2,BLACK);
    //al_draw_line(x_position + 2,  y_position - 5, x_position + 8, y_position+3, al_map_rgb(0,0,0), 2);
    //setcolor(WHITE);
    al_draw_line(x_position-2*r, y_position+2*r, x_position+2*r, y_position+2*r, al_map_rgb(255,255,255), 4); // two hand
    al_draw_line(x_position, y_position+r, x_position, y_position+4*r,al_map_rgb(255,255,255), 4); //body
    al_draw_line(x_position, y_position+4*r, x_position-2*r, y_position+6*r,  al_map_rgb(255,255,255),4); //right foot
    al_draw_line(x_position, y_position+4*r, x_position+2*r, y_position+6*r, al_map_rgb(255,255,255), 4); //left foot
    // line(0, y_position+6*r, 800, y_position+6*r, 4);
    //update_display();
}
/*int choose_angle(int hand_point_X, int hand_point_Y, int i)
{
    int change_Y = 0;
    change_Y = (-sqrt((2500-pow((i), 2))))+ hand_point_Y;
    setcolor(BLUE);
    filled_circle(hand_point_X+i, change_Y , 4 ,-1);
    moveto(hand_point_X+i, change_Y);
    lineto(hand_point_X, hand_point_Y, 2);
    update_display();
}*/
shoot_again_flag fun_shoot(int shoot_x, int shoot_y, int speed, int play_holes, int wind)   /******************返回一个数组 **********************/
{
    shoot_again_flag return_data;
    return_data.ret_cur_x = 120;

    //stick_man_centerX = 100 + cur_posX;

    float cur_x_and_y[2];
    while(play_holes != 15)  // moveto(shoot_x, shoot_y);
    {
        int cur_posX = shoot_x;

        int cur_posY;

        int stick_man_centerX = cur_posX - 40;

        /****************测试用************************/
        /*int temp_cur_posy;
        int temp_cur_posx = shoot_x;
        double temp_speed_angle = (double) atan2(-shoot_y+470.0,shoot_x-120.0);
         double temp_speed_ground = speed * cos(speed_angle);
        double temp_speed_sky = speed * sin(speed_angle);*/
        /****************************************/
        double speed_angle;
        ///////// double speed_shoot[2];
        //speed_angle = 49/50.5;
        // double pppp =  ()/(shoot_x-120.0);
        speed_angle =(double) atan2(-shoot_y+510.0,shoot_x-120.0);
        // printf("%lf\n",pppp);
        //printf("%lf\n",speed_angle);
        if (play_holes >= 5)
        {
            speed = speed *((100.0+wind)/100.0);
//            printf("speed with wind %d\n", speed);
        }
        // display_wind();
        double speed_ground = speed * cos(speed_angle);
        double speed_sky = speed * sin(speed_angle);
        moveto(shoot_x, shoot_y);

        int stick_man_centerY = 450;
        bool ConfirmGoalFlag = false;
        return_data.confirmgoal_flag = ConfirmGoalFlag;
        bool air_wallFlag = false;
        ////  speed_shoot[0] = speed_ground;
        ////  speed_shoot[1] = speed_sky;
        /// sitck_man(stick_man_centerX, stick_man_centerY,10);
        do     /*******第一次抛物线*************/
        {
            float Time;
            Time = (cur_posX - shoot_x) / speed_ground;
            cur_posY = (int)(shoot_y - speed_sky*Time + 9.81*pow(Time, 2)/2);
            cleardevice();
            if(cur_posY > 510)
                (cur_posY =510);
            backGRD();
            theGoal(760,510);

            sitck_man( stick_man_centerX, stick_man_centerY,10);
            al_draw_filled_circle(cur_posX, cur_posY, 5, al_map_rgb(255,255,255));
            cur_posX++;
            if (toConfirmGoal(cur_posX,cur_posY) == 2)
            {
                ConfirmGoalFlag = 1;
                al_draw_filled_circle(cur_posX-1,cur_posY-1, 5,al_map_rgb(155,205,155));
                al_draw_filled_circle(cur_posX,cur_posY, 5,al_map_rgb(155,205,155));
                al_draw_filled_circle(750,510, 5, al_map_rgb(255, 255, 255));
                update_display();
                break;
            }
            /*  else if (toConfirmGoal(cur_posX, cur_posY) !=2 )
              {
                  play_holes = play_holes
              }
              */
            //switch_avoid_level(play_holes);
            switch (play_holes)
            {
            case 1:
                break;
            case 2:
            {
                draw_a_hill(300,510,150);
                if (avoid_hill(cur_posX, cur_posY) == 2)
                {
                    //  ConfirmGoalFlag = 1;
                    air_wallFlag = true;
                    al_draw_filled_circle(cur_posX,cur_posY, 5,al_map_rgb(255,255,255));
                    return_data.ret_cur_x = 801;
                }
                break;
            }
            case 3:
            {
                draw_water();
                if (avoid_water(cur_posX, cur_posY) == 3)
                {
                    // air_wallFlag = true;
                    //   ConfirmGoalFlag = 1;
                    al_draw_filled_circle(cur_posX,cur_posY, 5,al_map_rgb(255,255,255));
                }
                break;
            }
            case 4:
            {
                draw_sand();
                if (avoid_sand(cur_posX, cur_posY) == 4)
                {
                    air_wallFlag = true;
                    //  ConfirmGoalFlag = 1;
                    al_draw_filled_circle(cur_posX,cur_posY, 5,al_map_rgb(255,255,255));
                }
                break;
            }
            case 5:
                //  display_wind();
                break;
            case 6:
            {
                draw_a_hill(300,510,150);
                if (avoid_hill(cur_posX, cur_posY) == 2)
                {
                    air_wallFlag = true;
                    al_draw_filled_circle(cur_posX,cur_posY, 5,al_map_rgb(255,255,255));
                    // ConfirmGoalFlag = 1;
                }
                break;
            }
            case 7:
            {
                draw_water();
                if (avoid_water(cur_posX, cur_posY) == 3)
                {
                    //air_wallFlag = true;
                    //ConfirmGoalFlag = 1;
                    al_draw_filled_circle(cur_posX,cur_posY, 5,al_map_rgb(255,255,255));
                    // ConfirmGoalFlag = 1;
                }
                break;
            }
            case 8:
            {
                draw_sand();
                if (avoid_sand(cur_posX, cur_posY) == 4)
                {
                    air_wallFlag = true;
                    al_draw_filled_circle(cur_posX,cur_posY, 5,al_map_rgb(255,255,255));
                    //ConfirmGoalFlag = 1;
                }
                break;
            }
            case 9:
            {
                draw_obstacles_sky(250,300);
                draw_obstacles_sky(460,320);
                if(avoid_obstacles_sky(cur_posX, cur_posY, 250,300) == 9)
                {
                    air_wallFlag = true;
                    al_draw_filled_circle(cur_posX,cur_posY, 5,al_map_rgb(255,255,255));
                    // ConfirmGoalFlag = 1;
                }
                else if (avoid_obstacles_sky(cur_posX, cur_posY, 460,320) == 9)
                {
                    air_wallFlag = true;
                    al_draw_filled_circle(cur_posX,cur_posY, 5,al_map_rgb(255,255,255));
                    //ConfirmGoalFlag = 1;
                }
                break;
            }
            default:
                break;
            }
            update_display();
            //pausefor(5);
            Sleep(2);
        }
        while (cur_posY <510 && air_wallFlag == false && ConfirmGoalFlag == false);
//   printf("the the  x is %d  and the Y is %d\n", cur_posX, cur_posY);
        int shoot_x2 = cur_posX--;
        int shoot_y2 = cur_posY;
        int cur_posX2 = cur_posX--, cur_posY2;
        double speed_ground2 = speed_ground/2;
        double speed_sky2 = speed_sky/2;
        int groundtimes = 70;
        do          /*******第二次抛物线*************/
        {
            float Time2;
            Time2 = (cur_posX2 - shoot_x2) / speed_ground2;
            cur_posY2 = (int)(shoot_y2 - speed_sky2 * Time2 + 9.81*pow(Time2, 2)/2);
            cleardevice();
            if(cur_posY2 > 510)
            {
                cur_posY2 = 510;
                groundtimes--;
            }
            backGRD();
            theGoal(760,510);
            sitck_man(stick_man_centerX, stick_man_centerY,10);
            al_draw_filled_circle(cur_posX2, cur_posY2, 5, al_map_rgb(255, 255, 255));
            cur_posX2++;
            switch (play_holes)  /**********************play_holes******************************/
            {
            case 1:
                break;
            case 2:
            {
                draw_a_hill(300,510,150);
                if (avoid_hill(cur_posX2, cur_posY2) == 2)
                {
                    al_draw_filled_circle(cur_posX2,cur_posY2, 5,al_map_rgb(255,255,255));
                    air_wallFlag = true;

                }
                break;
            }
            case 3:
            {
                draw_water();
                if (avoid_water(cur_posX2, cur_posY2) == 3)
                {
                    //ConfirmGoalFlag = 1;
                    al_draw_filled_circle(cur_posX2,cur_posY2, 5,al_map_rgb(255,255,255));
                    air_wallFlag = true;
                }
                break;
            }
            case 4:
            {
                draw_sand();
                if (avoid_sand(cur_posX2, cur_posY2) == 4)
                {
                    al_draw_filled_circle(cur_posX2,cur_posY2, 5,al_map_rgb(255,255,255));
                    air_wallFlag = true;
                }
                break;
            }
            case 5:
                break;
            case 6:
            {
                draw_a_hill(300,510,150);
                if (avoid_hill(cur_posX2, cur_posY2) == 2)
                {
                    al_draw_filled_circle(cur_posX2,cur_posY2, 5,al_map_rgb(255,255,255));
                    air_wallFlag = true;
                }
                break;
            }
            case 7:
            {
                draw_water();
                if (avoid_water(cur_posX2, cur_posY2) == 3)
                {
                    //ConfirmGoalFlag = 1;
                    al_draw_filled_circle(cur_posX2,cur_posY2, 5,al_map_rgb(255,255,255));
                    air_wallFlag = true;
                }
                break;
            }
            case 8:
            {
                draw_sand();
                if (avoid_sand(cur_posX2, cur_posY2) == 4)
                {
                    al_draw_filled_circle(cur_posX2,cur_posY2, 5,al_map_rgb(255,255,255));
                    air_wallFlag = true;
                }
                break;
            }
            case 9:
            {
                draw_obstacles_sky(250,300);
                draw_obstacles_sky(460,320);
                if(avoid_obstacles_sky(cur_posX, cur_posY, 250,300) == 9)
                {
                    air_wallFlag = true;
                    al_draw_filled_circle(cur_posX,cur_posY, 5,al_map_rgb(255,255,255));
                    //ConfirmGoalFlag = 1;
                }
                else if (avoid_obstacles_sky(cur_posX, cur_posY, 460,320) == 9)
                {
                    air_wallFlag = true;
                    al_draw_filled_circle(cur_posX,cur_posY, 5,al_map_rgb(255,255,255));
                    // ConfirmGoalFlag = 1;
                }
                break;
            }
            default:
                break;
            }
            update_display();
            pausefor(2);
            //toConfirmGoal(cur_posX2,cur_posY2);
            if (toConfirmGoal(cur_posX2,cur_posY2) == 2)
            {
                ConfirmGoalFlag = 1;
                return_data.confirmgoal_flag = ConfirmGoalFlag;
              //  printf("jin qiu le ");
                al_draw_filled_circle(cur_posX2-1,cur_posY2-1, 5,al_map_rgb(155,205,155));
                al_draw_filled_circle(cur_posX2,cur_posY2, 5,al_map_rgb(155,205,155));
                al_draw_filled_circle(760,510, 4, al_map_rgb(255, 255, 255));
                update_display();
                break;
            }

            //  printf("the second  x is %d  and the Y is %d\n", cur_posX2, cur_posY2);
        }
        while (cur_posY2 <= 510 && groundtimes != 0 && air_wallFlag == false && ConfirmGoalFlag == false);
        //printf("the second  x is %d  and the Y is %d\n", cur_posX2, cur_posY2);

        if (toConfirmGoal(cur_posX2,cur_posY2) != 2 && air_wallFlag == false)
        {
            return_data.ret_cur_x = cur_posX2;
            return_data.ret_cur_y = cur_posY2;
            return return_data;
        }

        if (air_wallFlag == true)
        {
            return_data.ret_cur_x = 801;
        }
        return return_data;
    }
}
/*void switch_avoid_level(int play_holes, intcur_posX, int cur_posY )
{
    switch (play_holes)
        {
        case 1:
            break;
        case 2:
        {
            draw_a_hill(300,510,150);
            if (avoid_hill(cur_posX, cur_posY) == 2)
            {
                ConfirmGoalFlag = 1;
                al_draw_filled_circle(cur_posX,cur_posY, 5,al_map_rgb(255,255,255));
                air_wallFlag = true;
            }
            break;
        }
        case 3:
        {
            draw_water();
            if (avoid_water(cur_posX, cur_posY) == 3)
            {
                ConfirmGoalFlag = 1;
                al_draw_filled_circle(cur_posX,cur_posY, 5,al_map_rgb(255,255,255));
            }
            break;
        }
        case 4:
        {
            draw_sand();
            if (avoid_sand(cur_posX, cur_posY) == 4)
            {
                ConfirmGoalFlag = 1;
                al_draw_filled_circle(cur_posX,cur_posY, 5,al_map_rgb(255,255,255));
            }
            break;
        }
        case 5:
            //  display_wind();
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        default:
            break;
        }
}
*/
void to_initial_mouse ()
{
    initkeyboard();
    initmouse();
    create_event_queue();  //create an event queue
    reg_display_events();  // register display and mouse as event sources
    reg_mouse_events();
    reg_keyboard_events();
    hide_mouse_cursor();
    initfont();
}
void to_close_window()
{
    initkeyboard();
    initmouse();
    create_event_queue();  //create an event queue
    reg_display_events();  // register display and mouse as event sources
    reg_mouse_events();
    reg_keyboard_events();
    hide_mouse_cursor();
    initfont();
    wait_for_event();
    if (check_if_event())
    {
        if (event_mouse_right_button_down())
        {
            cleardevice();
            outtextxy( 300, 400, "Restart");
            update_display();
            wait_for_event();
            closegraph();
        }
    }
}
void theGoal(int hole_x, int hole_y)
{
    al_draw_filled_rectangle(hole_x-30, hole_y, hole_x+30, hole_y+10, al_map_rgb(155,205,155));
    al_draw_filled_circle(hole_x, hole_y, 6, al_map_rgb(124,124,124));
    al_draw_line(hole_x, hole_y, hole_x, hole_y-90, al_map_rgb(225,255,255), 4);  ///旗杆
    al_draw_filled_triangle(hole_x,hole_y-90,  hole_x-50,hole_y-50,  hole_x,hole_y-50, al_map_rgb(255,255,0) );
}
int toConfirmGoal(int final_x, int final_y)
{
    if (final_x >750 && final_x < 770 && final_y <515 && final_y >505)
    {
        printf("Goal\n");
        return 2;
    }
}
void draw_a_hill(int hill_left_x, int hill_left_y, int hill_height)
{
    al_draw_filled_triangle(hill_left_x,hill_left_y,  hill_left_x+40,hill_left_y-hill_height,  hill_left_x+80,hill_left_y, al_map_rgb(139,126, 102));
}
void draw_water()
{
    al_draw_filled_ellipse(400,510,120,60, al_map_rgb(175,238, 238));
    al_draw_filled_rectangle(280,450,520,500,al_map_rgb(135,206,235));  ///覆盖椭圆
}
void draw_obstacles_sky(int start_x, int start_y)
{
    al_draw_filled_rectangle(start_x,start_y, start_x+50, start_y+100, al_map_rgb(139,129,76));
}
int avoid_obstacles_sky(int X, int Y, int start_x, int start_y)
{
    if (X > start_x && X < (start_x + 50) && Y > start_y && Y < (start_y + 100) )
    {
//        printf("in sky\n");
        return 9;
    }
}
void draw_sand()
{
    al_draw_filled_ellipse(300,510,120,60, al_map_rgb(205, 173,0));
    al_draw_filled_rectangle(180,420,520,500,al_map_rgb(135,206,235));   ///覆盖椭圆
}
Return_flag ClickToNext(int exit_flag, int play_holes )
{
    Return_flag r;
    r.holes = play_holes;
    r.flag = exit_flag;
    fflush(stdin);
    while(true)
    {
        //initmouse();
        // reg_mouse_events();
        wait_for_event();
        if (event_close_display())
        {
            //exit_flag = true;
            r.flag = true;
            r.holes = 15;
//            printf("guan bu diao a ");
            return r;
        }
        else if(event_mouse_button_down())
        {
            if (event_mouse_left_button_down())
                return r;
            break;
        }
    }
}
/*int toAvoid_obstacles(int air_wall_startX, int air_wall_startY, int air_wall_endX, int air_wall_endY)
{
     if (final_x >690 && final_x < 710 && final_y <515 && final_y >505)
       {
           printf("Goal\n");
           return 2;
       }
}*/
/*void display_level_number(int text_x, int text_y)
{
    outtextxy(resX/2 - 200, resY / 3 - 30, "Careful, there is now an obstacle in your way.");
    outtextxy(resX/2 - 160, resY / 3, "You'll have to aim to chip over it.");
    outtextxy(resX/2 - 100, resY / 3 + 30, "Click to continue...");
    update_display();
} */
int avoid_hill(int X, int Y)
{
    float tempY = -3.75 * X + 1635;
    if ((X > 300 && X < 340) && Y >= tempY)
    {
//        printf("in hill\n");
        return 2;
    }
}
int avoid_water(int X, int Y)
{
    if ((X > 280 && X < 520) && Y >= 500)
    {
//        printf("in water\n");
        return 3;
    }
}
int avoid_sand(int x, int y)
{
    if (x > 180 && x <420 && y >=500)
    {
//        printf("in sand\n");
        return 4;
    }
}
int switch_level(int play_holes, int wind_number)
{
    switch (play_holes)         /***********play_holes********************/
    {
    case 1:                                 /**********空******************/
        break;
    case 2:                                 /**********山******************/
        draw_a_hill(300,510,150);
        // update_display();
        break;
    case 3:                                  /**********水*****************/
        draw_water();
        // update_display();
        break;
    case 4:                                   /**********沙*****************/
        draw_sand();
        update_display();
        break;
    case 5:                                  /********************空+风*****/
        display_wind(wind_number);
        // update_display();
        break;
    case 6:                                  /**********************山+风*****/
        draw_a_hill(300,510,150);
        display_wind(wind_number);
        // update_display();
        break;
    case 7:                                   /**********水+++风****************/
        display_wind(wind_number);
        draw_water();
        //  update_display();
        break;
    case 8:                                    /**********沙+++风****************/
        display_wind(wind_number);
        draw_sand(300,510,150);
        //  update_display();
        break;
    case 9:                                      /**********空中障碍+++风****************/
        display_wind(wind_number);
        draw_obstacles_sky(250,300);
        draw_obstacles_sky(460,320);
        //  update_display();
        break;
    default:
        break;
    }
}
int random_wind()
{
    int ran_wind;
    //srand(time(NULL));  //初始化随机数
    ran_wind = (rand()%101-50); // 生成-50 到 50 随机数
//    printf("wind is %d \n", ran_wind);
    return ran_wind;
}
/*int wind(int play_holes)
{
    int wind;
    switch (play_holes)
    {
    case 5: wind = random_wind();
            break;
    case 6:
    case 7:
    case 8:
    case 9:
    default:break;
    }
    return wind;
}*/
int draw_star()  ///留着有空写
{
}
void display_wind(int wind_number )
{
    char outtext[20];
    if (wind_number>0)
    {
        sprintf(outtext, "wind is -----> %d", wind_number  );
        outtextxy(300, 100, outtext);
        //update_display();
    }
    else if (wind_number <0)
    {
        sprintf(outtext, "wind is <----- %d", abs(wind_number)  );
        outtextxy(300, 100, outtext);
        //update_display();
    }
    //printf("wind_num is %d\n", wind_number);
}
//int score(int s)
bool quit_in_game()
{
    int quit_flag;
    if (check_if_event())     //检查是否有事件
    {
        wait_for_event();
        if(event_key_down())
        {
            wait_for_event();
            quit_flag = event.keyboard.keycode;
            if (quit_flag == 84)
            {
                //fflush(stdin);
                //gameflag = true;
                // printf("play_holse!!!!!");
                return true;
                //closegraph();
            }
        }
    }
}


void display_level_score(int shoot_times, int score, int play_holes )
{
    char char_shoot_times[20];
    char char_final_score[20];
    char char_play_holes[20];
    sprintf(char_shoot_times,"Shoot Times: %d", shoot_times+1);
    outtextxy(650,20, char_shoot_times);
    sprintf(char_final_score,"Your Score : %d", score);
    outtextxy(650,35, char_final_score);
    sprintf(char_play_holes,"Level 9 of %d", play_holes);
    outtextxy(650,5, char_play_holes);
    // update_display();
}


void shoot_again()
{

}
