#define  _CRT_SECURE_NO_WARNINGS 1
#define boardWidth 850
#define boardHeight 850
#define boardMargins 20
#define rightLine 300

#include<stdio.h>
#include<graphics.h>
#include<windows.h>
//________________________全局变量___________________________

int num = 0; //0表示白子。1表示黑子
int arr[20][20] = { -1 };
int win = -1; //0为白子赢，1为黑子赢,平局懒得写；

//_______________________________________________________________

//_________________________声明函数______________________________
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
	if (setGameMode() == 1)  //模式选择1为对战模式，2为人机模式；
	{
		gameMode0();
	}
	else if (setGameMode() == 2)
	{
		gameMode1();
	}
	return 0;
}
//________________________函数区域___________________________
void setBackGround()
{
	initgraph(boardHeight, boardHeight);//绘制画布
	setorigin(boardMargins, boardHeight- boardMargins);//调整坐标
	setaspectratio(1, -1); // x轴方向不变，让y轴翻转。
	// 设置背景色
	setbkcolor(RGB(247, 226, 201));
	// 用背景色清空屏幕
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
				//竖
				if (arr[i][j] == 0 && arr[i][j] == arr[i+1][j] && arr[i][j] == arr[i+2][j] && arr[i][j] == arr[i+3][j] && arr[i][j] == arr[i+4][j] )
				{
					win = 0;
				}
				else if (arr[i][j] == 1 && arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j] && arr[i][j] == arr[i + 3][j] && arr[i][j] == arr[i + 4][j])
				{
					win = 1;
				}
				//横
				if (arr[i][j] == 0 && arr[i][j] == arr[i - 1][j+1] && arr[i][j] == arr[i - 2][j + 2] && arr[i][j] == arr[i +1 ][j-1] && arr[i][j] == arr[i +2][j-2])
				{
					win = 0;
				}
				else if (arr[i][j] == 1 && arr[i][j] == arr[i - 1][j + 1] && arr[i][j] == arr[i - 2][j + 2] && arr[i][j] == arr[i + 1][j - 1] && arr[i][j] == arr[i + 2][j - 2])
				{
					win = 1;
				}
				//左上-右下
				if (arr[i][j] == 0 && arr[i][j] == arr[i + 1][j + 1] && arr[i][j] == arr[i + 2][j + 2] && arr[i][j] == arr[i - 1][j - 1] && arr[i][j] == arr[i - 2][j - 2])
				{
					win = 0;
				}
				else if (arr[i][j] == 1 && arr[i][j] == arr[i + 1][j + 1] && arr[i][j] == arr[i + 2][j + 2] && arr[i][j] == arr[i - 1][j - 1] && arr[i][j] == arr[i - 2][j - 2])
				{
					win = 1;
				}
				//右上-左下
			}

		}

	}
	
}
int setGameMode()
{
	setBackGround();
	setaspectratio(1, 1);
	setorigin(0, 0);
	TCHAR s1[50] = L"选择游戏模式：";
	TCHAR s2[50] = L"1.对战模式";
	TCHAR s3[50] = L"2.人机模式";
	TCHAR s4[50] = L"By:Dznzctx";
	button(225, 250, 400, 60, s1);
	button(225, 350, 400, 60, s2);
	button(225, 450, 400, 60, s3);
	button(225, 550, 400, 60, s4);
	while (1)
	{
		MOUSEMSG msg;
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)//如果鼠标左键按下
		{
			if(msg.x >= 225 && msg.x <= 225 + 400 && msg.y >= 350 && msg.y <= 350 + 60)
			{
				settextcolor(RED);
				settextstyle(42, 20, _T("隶书"));
				outtextxy(325, 425, _T("选择模式1！"));
				return 1;
				break;

			}
			if (msg.x >= 225 && msg.x <= 225 + 400 && msg.y >= 450 && msg.y <= 450 + 60)
			{
				settextcolor(RED);
				settextstyle(42, 20, _T("隶书"));
				outtextxy(325, 425, _T("选择模式2！"));
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
	settextstyle(42, 20, _T("黑体"));
	fillroundrect(x, y, x + w, y + h, 10, 10);
	// 输出字符串（MBCS 字符集）
	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;
	outtextxy(tx, ty, text);

}
void game()
{
	setBackGround();//设置背景
	drawLine();//绘制棋盘线条及星
	drawPoint();//绘制棋盘星

	//初始化二维数组
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
		if (m.uMsg == WM_LBUTTONDOWN)//如果鼠标左键按下
		{
			drawPiece(m.x, m.y);
		}
		isWin();

	}
	if (win == 0)
	{
		setaspectratio(1, 1);
		settextcolor(RED);
		settextstyle(42, 20, _T("隶书"));
		outtextxy(225, -425, _T("游戏结束，白子胜利！"));
		system("pause");
	}
	else if (win == 1)
	{
		setaspectratio(1, 1);
		settextcolor(RED);
		settextstyle(42, 20, _T("隶书"));
		outtextxy(225, -425, _T("游戏结束，黑子胜利！"));
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
		if (m.uMsg == WM_LBUTTONDOWN)//如果鼠标左键按下
		{

			drawBotPiece(m.x, m.y);
		}
		isWin();

	}
	if (win == 0)
	{
		setaspectratio(1, 1);
		settextcolor(RED);
		settextstyle(42, 20, _T("隶书"));
		outtextxy(225, -425, _T("游戏结束，白子胜利！"));
		system("pause");
	}
	else if (win == 1)
	{
		setaspectratio(1, 1);
		settextcolor(RED);
		settextstyle(42, 20, _T("隶书"));
		outtextxy(225, -425, _T("游戏结束，黑子胜利！"));
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
		int botX = rand() % 15 + 0;//生成0~15的随机数
		int botY = rand() % 15 + 0;//生成0~15的随机数
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