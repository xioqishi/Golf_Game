#include "Menu.h"
int  choose_item(int *index , int sizea)
{
	int ch ;
	ch = getch();
	switch(ch)
	{
		//��
		//���ѡ���ϣ���ô��������ƶ�
		case UP : if(*index > 0)  *index -= 1 ;  break;
		//��
		//���ѡ���£���ô��������ƶ�
		case DOWN :if(*index < sizea -1)  *index += 1 ;  break;
		//��
		case LEFT:
		case 97:return 0 ;
		//��
		case RIGHT:return 0 ;
		//�س�
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
	//������ʾ���ı�����ɫ
	SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | 0x8);
	//��ʼ������̨��ʾ��X,Y�������
	pos.X =32;
	pos.Y = 2 ;
	//������ʾ������̨�ն˵ľ���λ��
	SetConsoleCursorPosition(hOut,pos);
	//����printf�ڿ���̨��Ӧ��λ�������
	printf("%s",TITLE);
	pos.X = 0;
	pos.Y = 20 ;
	SetConsoleCursorPosition(hOut,pos);
	printf("%s",AUTHOR);
	for(i = 0 ; i < sizea ; i++)
	{
		//���i==index��ʾ�ڵ�ǰѡ���λ�ã�Ĭ�ϳ�ʼ����ʾ�ǵ�һ���ʾΪ��ɫ��
		//���������°���ѡ���ʱ�򣬹����ƶ���Ҳ�Ϳ������б�ѡ�������
		if(i == index)
		{
			//��ɫ
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | 0x8);
			pos.X = 30;
    		pos.Y = 5+i;
    		//���ù������
    		SetConsoleCursorPosition(hOut,pos);
    		printf("%s",menu[i]);
		}
		//������ʾΪ��ɫ
		else
		{
			//��ɫ
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			pos.X = 30;
    		pos.Y = 5+i;
    		//���ù������
    		SetConsoleCursorPosition(hOut,pos);    //���ù������
    		printf("%s",menu[i]);
		}
	}
	//ˢ�±�׼���������
	fflush(stdout);
}
