#ifndef MENU_H
#define MENU_H
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#define   NR(x)   (sizeof(x)/sizeof(x[0]+0))
#define  TITLE  "GOLF GAME"
#define  AUTHOR "Y3865187"
int  choose_item(int *index , int sizea ) ;
enum
{
	UP = 72,
	DOWN = 80 ,
	LEFT = 75 ,
	RIGHT = 77 ,
	ENTER = 13 ,
	ESC = 27 ,
};
void showmenu(HANDLE hOut ,char **menu , int sizea , int index) ;
#endif
