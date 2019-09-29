#include "Menu.h"
int  choose_item(int *index , int sizea)
{
	int ch ;
	ch = getch();
	switch(ch)
	{
		//上
		//如果选择上，那么光标向上移动
		case UP : if(*index > 0)  *index -= 1 ;  break;
		//下
		//如果选择下，那么光标向下移动
		case DOWN :if(*index < sizea -1)  *index += 1 ;  break;
		//左
		case LEFT:
		case 97:return 0 ;
		//右
		case RIGHT:return 0 ;
		//回车
		case ENTER: return ENTER ;
		//ESC
		case ESC: return ESC ;
	}
    return 0;
}
void showmenu(HANDLE hOut ,char **menu , int sizea , int index)
{
	int i ;
    COORD pos = {0,0};
	system("cls");
	//设置显示的文本的颜色
	SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | 0x8);
	//初始化控制台显示的X,Y轴的坐标
	pos.X =32;
	pos.Y = 2 ;
	//设置显示到控制台终端的具体位置
	SetConsoleCursorPosition(hOut,pos);
	//调用printf在控制台对应的位置上输出
	printf("%s",TITLE);
	pos.X = 0;
	pos.Y = 20 ;
	SetConsoleCursorPosition(hOut,pos);
	printf("%s",AUTHOR);
	for(i = 0 ; i < sizea ; i++)
	{
		//如果i==index表示在当前选项的位置，默认初始化显示是第一项，显示为红色，
		//当按下上下按键选择的时候，光标会移动，也就看到了列表选择的现象
		if(i == index)
		{
			//红色
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | 0x8);
			pos.X = 30;
    		pos.Y = 5+i;
    		//设置光标坐标
    		SetConsoleCursorPosition(hOut,pos);
    		printf("%s",menu[i]);
		}
		//否则显示为白色
		else
		{
			//白色
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			pos.X = 30;
    		pos.Y = 5+i;
    		//设置光标坐标
    		SetConsoleCursorPosition(hOut,pos);    //设置光标坐标
    		printf("%s",menu[i]);
		}
	}
	//刷新标准输出缓冲区
	fflush(stdout);
}
