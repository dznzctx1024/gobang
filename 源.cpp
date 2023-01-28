#define  _CRT_SECURE_NO_WARNINGS 1
#define boardWidth 850
#define boardHeight 850
#define boardMargins 20
#define rightLine 300

#include<stdio.h>
#include<graphics.h>
#include<windows.h>
//________________________ȫ�ֱ���___________________________

int num = 0; //0��ʾ���ӡ�1��ʾ����
int arr[20][20] = { -1 };
int win = -1; //0Ϊ����Ӯ��1Ϊ����Ӯ,ƽ������д��

//_______________________________________________________________

//_________________________��������______________________________
void setBackGround();
void drawLine();
void drawPoint();
void drawPiece(int x, int y);
void isWin();
void button(int x, int y, int w, int h, TCHAR* text);
void gameMode0();
void gameMode1();
void game();
int setGameMode();
void drawBotPiece(int x, int y);

//_______________________________________________________________
int main()
{
	if (setGameMode() == 1)  //ģʽѡ��1Ϊ��սģʽ��2Ϊ�˻�ģʽ��
	{
		gameMode0();
	}
	else if (setGameMode() == 2)
	{
		gameMode1();
	}
	return 0;
}
//________________________��������___________________________
void setBackGround()
{
	initgraph(boardHeight, boardHeight);//���ƻ���
	setorigin(boardMargins, boardHeight- boardMargins);//��������
	setaspectratio(1, -1); // x�᷽�򲻱䣬��y�ᷭת��
	// ���ñ���ɫ
	setbkcolor(RGB(247, 226, 201));
	// �ñ���ɫ�����Ļ
	cleardevice();
}

void drawLine()
{
	for (int y = 0; y <= boardHeight; y += (boardHeight - boardMargins*2)/15)
	{
		setcolor(RGB(0, 0, 0));
		line(0, y, boardHeight - boardMargins * 2, y);
	}
	for (int x = 0; x <= boardWidth; x += (boardWidth - boardMargins * 2) / 15)
	{
		setcolor(RGB(0, 0, 0));
		line(x, 0, x, boardWidth-boardMargins*2);
	}

}
void drawPoint()
{
	setcolor(RGB(0, 0, 0));
	setfillcolor(RGB(0, 0, 0));
	
	fillcircle(7 * ((boardWidth - boardMargins * 2) / 15), 7 * ((boardWidth - boardMargins * 2) / 15), ((boardWidth - boardMargins * 2) / 15) / 6);
	fillcircle(3 * ((boardWidth - boardMargins * 2) / 15), 3 * ((boardWidth - boardMargins * 2) / 15), ((boardWidth - boardMargins * 2) / 15) / 6);
	fillcircle(12 * ((boardWidth - boardMargins * 2) / 15), 12 * ((boardWidth - boardMargins * 2) / 15), ((boardWidth - boardMargins * 2) / 15) / 6);
	fillcircle(12 * ((boardWidth - boardMargins * 2) / 15), 3 * ((boardWidth - boardMargins * 2) / 15), ((boardWidth - boardMargins * 2) / 15) / 6);
	fillcircle(3 * ((boardWidth - boardMargins * 2) / 15), 12 * ((boardWidth - boardMargins * 2) / 15), ((boardWidth - boardMargins * 2) / 15) / 6);

}
void drawPiece(int x ,int y)
{
	x = x - boardMargins;
	y = boardWidth - boardMargins -y;
	if (x < 0)
	{
		x = -x;
	}
	if (y < 0)
	{
		y = -y;
	}
	if (x % 54 < 27)
	{
		x = x - (x % 54);
	}
	else if (x % 54 > 27)
	{
		x = x - (x % 54)+54;
	}
	if (y % 54 < 27)
	{
		y = y - (y % 54);
	}
	else if (y % 54 > 27)
	{
		y = y - (y % 54) + 54;
	}


	if (num == 0 && x % 54 != 27 &&  y % 54 != 27 && arr[x / 54 + 2][y / 54 + 2] == -1&&x / 54 + 2<18)
	{
		setfillcolor(WHITE);
		fillcircle(x, y, ((boardWidth - boardMargins * 2) / 15) / 3);
		arr[x / 54+2][y / 54+2] = 0;

		
	}
	else if (num == 1 && x % 54 != 27 && y % 54 != 27 && arr[x / 54 + 2][y / 54 + 2] == -1 && x / 54 + 2 < 18)
	{
		setfillcolor(BLACK);
		fillcircle(x, y, ((boardWidth - boardMargins * 2) / 15) / 3);
		arr[x / 54 + 2][y / 54 + 2] = 1 ;

	}
	num = (num + 1) % 2;
}
void isWin()
{
	for (int i = 1; i <= 20; i++)
	{
		for (int j = 1; j <= 20; j++)
		{
			
			if (i>=2&& i<=17 && j >= 2 && j <= 17)
			{
				if (arr[i][j] == 0 && arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2] && arr[i][j] == arr[i][j + 3] && arr[i][j] == arr[i][j + 4] )
				{
					win = 0;
				}
				else if (arr[i][j] == 1 && arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2] && arr[i][j] == arr[i][j + 3] && arr[i][j] == arr[i][j + 4] )
				{
					win = 1;
				}
				//��
				if (arr[i][j] == 0 && arr[i][j] == arr[i+1][j] && arr[i][j] == arr[i+2][j] && arr[i][j] == arr[i+3][j] && arr[i][j] == arr[i+4][j] )
				{
					win = 0;
				}
				else if (arr[i][j] == 1 && arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j] && arr[i][j] == arr[i + 3][j] && arr[i][j] == arr[i + 4][j])
				{
					win = 1;
				}
				//��
				if (arr[i][j] == 0 && arr[i][j] == arr[i - 1][j+1] && arr[i][j] == arr[i - 2][j + 2] && arr[i][j] == arr[i +1 ][j-1] && arr[i][j] == arr[i +2][j-2])
				{
					win = 0;
				}
				else if (arr[i][j] == 1 && arr[i][j] == arr[i - 1][j + 1] && arr[i][j] == arr[i - 2][j + 2] && arr[i][j] == arr[i + 1][j - 1] && arr[i][j] == arr[i + 2][j - 2])
				{
					win = 1;
				}
				//����-����
				if (arr[i][j] == 0 && arr[i][j] == arr[i + 1][j + 1] && arr[i][j] == arr[i + 2][j + 2] && arr[i][j] == arr[i - 1][j - 1] && arr[i][j] == arr[i - 2][j - 2])
				{
					win = 0;
				}
				else if (arr[i][j] == 1 && arr[i][j] == arr[i + 1][j + 1] && arr[i][j] == arr[i + 2][j + 2] && arr[i][j] == arr[i - 1][j - 1] && arr[i][j] == arr[i - 2][j - 2])
				{
					win = 1;
				}
				//����-����
			}

		}

	}
	
}
int setGameMode()
{
	setBackGround();
	setaspectratio(1, 1);
	setorigin(0, 0);
	TCHAR s1[50] = L"ѡ����Ϸģʽ��";
	TCHAR s2[50] = L"1.��սģʽ";
	TCHAR s3[50] = L"2.�˻�ģʽ";
	TCHAR s4[50] = L"By:Dznzctx";
	button(225, 250, 400, 60, s1);
	button(225, 350, 400, 60, s2);
	button(225, 450, 400, 60, s3);
	button(225, 550, 400, 60, s4);
	while (1)
	{
		MOUSEMSG msg;
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)//�������������
		{
			if(msg.x >= 225 && msg.x <= 225 + 400 && msg.y >= 350 && msg.y <= 350 + 60)
			{
				settextcolor(RED);
				settextstyle(42, 20, _T("����"));
				outtextxy(325, 425, _T("ѡ��ģʽ1��"));
				return 1;
				break;

			}
			if (msg.x >= 225 && msg.x <= 225 + 400 && msg.y >= 450 && msg.y <= 450 + 60)
			{
				settextcolor(RED);
				settextstyle(42, 20, _T("����"));
				outtextxy(325, 425, _T("ѡ��ģʽ2��"));
				return 2;
				break;
				
			}
			break;
		}
	}
	return 0;
}

void button(int x, int y, int w, int h, TCHAR * text)
{
	setbkmode(TRANSPARENT);
	setfillcolor(WHITE);
	settextcolor(RGB(128,128,128));
	settextstyle(42, 20, _T("����"));
	fillroundrect(x, y, x + w, y + h, 10, 10);
	// ����ַ�����MBCS �ַ�����
	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;
	outtextxy(tx, ty, text);

}
void game()
{
	setBackGround();//���ñ���
	drawLine();//����������������
	drawPoint();//����������

	//��ʼ����ά����
	for (int i = 1; i <= 20; i++)
	{
		for (int j = 1; j <= 20; j++)
		{
			arr[i][j] = -1;
		}

	}
}

void gameMode0()
{
	game();
	while (win == -1)
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//�������������
		{
			drawPiece(m.x, m.y);
		}
		isWin();

	}
	if (win == 0)
	{
		setaspectratio(1, 1);
		settextcolor(RED);
		settextstyle(42, 20, _T("����"));
		outtextxy(225, -425, _T("��Ϸ����������ʤ����"));
		system("pause");
	}
	else if (win == 1)
	{
		setaspectratio(1, 1);
		settextcolor(RED);
		settextstyle(42, 20, _T("����"));
		outtextxy(225, -425, _T("��Ϸ����������ʤ����"));
		system("pause");
	}
}



void gameMode1()
{
	game();
	while (win == -1)
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//�������������
		{

			drawBotPiece(m.x, m.y);
		}
		isWin();

	}
	if (win == 0)
	{
		setaspectratio(1, 1);
		settextcolor(RED);
		settextstyle(42, 20, _T("����"));
		outtextxy(225, -425, _T("��Ϸ����������ʤ����"));
		system("pause");
	}
	else if (win == 1)
	{
		setaspectratio(1, 1);
		settextcolor(RED);
		settextstyle(42, 20, _T("����"));
		outtextxy(225, -425, _T("��Ϸ����������ʤ����"));
		system("pause");
	}
}
void drawBotPiece(int x, int y)
{
	x = x - boardMargins;
	y = boardWidth - boardMargins - y;
	if (x < 0)
	{
		x = -x;
	}
	if (y < 0)
	{
		y = -y;
	}
	if (x % 54 < 27)
	{
		x = x - (x % 54);
	}
	else if (x % 54 > 27)
	{
		x = x - (x % 54) + 54;
	}
	if (y % 54 < 27)
	{
		y = y - (y % 54);
	}
	else if (y % 54 > 27)
	{
		y = y - (y % 54) + 54;
	}
	if (num == 0 && x % 54 != 27 && y % 54 != 27 && arr[x / 54 + 2][y / 54 + 2] == -1 && x / 54 + 2 < 18)
	{
		setfillcolor(WHITE);
		fillcircle(x, y, ((boardWidth - boardMargins * 2) / 15) / 3);
		arr[x / 54 + 2][y / 54 + 2] = 0;
	}
	num = (num + 1) % 2;
	while (1) 
	{
		int botX = rand() % 15 + 0;//����0~15�������
		int botY = rand() % 15 + 0;//����0~15�������
		if (num == 1  &&arr[botX + 2][botY + 2] == -1 && botX + 2 < 18)
		{
		setfillcolor(BLACK);
		fillcircle(botX * 54, botY * 54, ((boardWidth - boardMargins * 2) / 15) / 3);
		arr[botX + 2][botY + 2] = 1;
		num = (num + 1) % 2;
		break;
		}
	}
	
}
//2023.1.18