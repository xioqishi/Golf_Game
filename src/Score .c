#include "Score.h"
int final_point_fun(int shoot_times, bool score_flag )
{
    if (shoot_times == 0 && score_flag)
    {
//        printf("50 fen\n");
        return 50;
    }
    else if (shoot_times == 1 && score_flag)
    {
//        printf("30 fen\n");
        return 30;
    }
    else if (shoot_times == 2 && score_flag)
    {
//        printf("10 fen\n");
        return 10;
    }
    else
    {
//        printf("0 fen\n");
        return 0;
    }
}
void Fun_rank()
{
    FILE *Rank_file;
    int i;
    Rank_file = fopen("Name.txt", "r");
    if (!(Rank_file))
    {
        // fclose(Rank_file);
        // creat_a_file();
        Rank_file = fopen("Name.txt", "w");
        strcpy(RankName[0].name, "AA");
        strcpy(RankName[1].name, "BB");
        strcpy(RankName[2].name, "CC");
        strcpy(RankName[3].name, "DD");
        strcpy(RankName[4].name, "EE");
        for (i = 0; i <5; i++)
        {
            RankName[i].score = 250 - 50*i;
            fprintf(Rank_file, "%d%s\n", RankName[i].score, RankName[i].name);
//            printf("score is %d\n", RankName[i]);
        }
        fclose(Rank_file);
    }
    else if(Rank_file)
    {
        //fclose(Rank_file);
        //Rank_file = fopen("Name.txt", "r");
        while (!feof(Rank_file))
        {
            for (i = 0; i<=4; i++)
            {
                fscanf(Rank_file, "%d%s\n", &RankName[i].score, RankName[i].name);
                update_display();
            }
        }
        /* for (i = 0; i<=4; i++)
               {
                 fscanf(Rank_file, "%d %s", &RankName[i].score, &RankName[i].name);
               }*/
        fclose(Rank_file);
    }
}
void display_name()
{
    Fun_rank();
    initfont();
    int i;
    char show_score[20];
    char ichar[2];
    int display_x = 300, display_y = 100;
    outtextxy(display_x, display_y, "rank");
    outtextxy(display_x + 50, display_y,"name");
    outtextxy(display_x + 110, display_y,"score");
    for (i = 0; i <=4; i++ )
    {
        sprintf(show_score,"%d", RankName[i].score);
        outtextxy(410,60+80*(i+1),show_score);
        outtextxy(350,60+80*(i+1), RankName[i].name);
        sprintf(ichar,"%d.", i+1);
        outtextxy(300,60+80*(i+1), ichar);
    }
    update_display();
}
void compare_point(int point)
{
    int i;
    Fun_rank();
    FILE *Rank_file = fopen("Name.txt", "r");
    for (i = 0; i <= 4; i++ )
    {
        if(point > RankName[i].score)
            break;
    }
    int top5;
    top5 = i;
    FILE *Rank_file_w = fopen("Name.txt", "w");
    if (i <= 4 )
    {
       outtextxy(300,200, "You are in top5!");
        update_display();
        closegraph();
        system("cls");
        printf("Your score is %d.\n", point);
        printf("Congratulations£¡You are in top5!\n");
        printf("Your Name:  ");
        for(i = 3 ; i >= top5; i--)
        {
            strcpy(RankName[i+1].name, RankName[i].name);
            RankName[i+1].score = RankName[i].score;
        }
        scanf("%s", RankName[top5].name);
        RankName[top5].score = point;
         initwindow(800,600);
   to_initial_mouse();
    }
    for(i = 0; i <=4; i++)
    {
        fprintf(Rank_file_w, "%d%s\n", RankName[i].score,RankName[i].name);
    }
    fclose(Rank_file_w);
}
