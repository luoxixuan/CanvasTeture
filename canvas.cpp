#include "stdafx.h"
#include <stdio.h>

//定义一个结构体
struct dragon        //定义dragon结构，代表画面上的恐龙，其结构成员x和y为贴图坐标，dir为目前恐龙的移动方向
{
	int x, y;
	int dir;
};

//定义常数
const int draNum = 4096;  //定义常数draNum，代表程序在画面上要出现的恐龙数目，在此设定为4096个
const int sortMethod = 0; //选择排序算法，0为归并排序，其他值为起泡排序

//全局变量定义
HINSTANCE hInst;
HBITMAP draPic[4], bg;   //draPic[4]储存恐龙上下左右移动的连续图案，bg为存储背景图
HDC		hdc, mdc, bufdc;
HWND	hWnd;
DWORD	tPre, tNow;
int		picNum;
//dragon  dra[draNum];   //按照draNum的值建立数组dra[]，产生画面上出现的恐龙。
vector<Dragon> dra(draNum);   //按照draNum的值建立向量dra，产生画面上出现的恐龙。
//array<Dragon, draNum> dra;
int clockRecord;

//全局函数声明
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				MyPaint(HDC hdc);
void				draInit(int arrSize, vector<Dragon> & sortVec);

//****WinMain函数，程序入口点函数**************************************
int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR     lpCmdLine,
					 int       nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	//初始化
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	GetMessage(&msg, NULL, NULL, NULL);//初始化msg
	//消息循环
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			tNow = GetTickCount();
			if (tNow - tPre >= 100)
				MyPaint(hdc);
		}
	}

	return msg.wParam;
}

//****设计一个窗口类，类似填空题，使用窗口结构体*************************
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "canvas";
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex);
}

//****初始化函数*************************************
// 加载位图并设定各初始值
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HBITMAP bmp;
	hInst = hInstance;

	hWnd = CreateWindow("canvas", "绘图窗口", WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	MoveWindow(hWnd, 10, 10, 640, 480, true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);
	bufdc = CreateCompatibleDC(hdc);

	bmp = CreateCompatibleBitmap(hdc, 640, 480);  //建立一个空位图并放入mdc中
	SelectObject(mdc, bmp);


	// 加载各张恐龙跑动图及背景图，这里以0,1,2,3来代表恐龙的上，下，左，右移动
	draPic[0] = (HBITMAP)LoadImage(NULL, "dra0.bmp", IMAGE_BITMAP, 528, 188, LR_LOADFROMFILE);
	draPic[1] = (HBITMAP)LoadImage(NULL, "dra1.bmp", IMAGE_BITMAP, 544, 164, LR_LOADFROMFILE);
	draPic[2] = (HBITMAP)LoadImage(NULL, "dra2.bmp", IMAGE_BITMAP, 760, 198, LR_LOADFROMFILE);
	draPic[3] = (HBITMAP)LoadImage(NULL, "dra3.bmp", IMAGE_BITMAP, 760, 198, LR_LOADFROMFILE);
	bg = (HBITMAP)LoadImage(NULL, "bg.bmp", IMAGE_BITMAP, 640, 480, LR_LOADFROMFILE);

	MyPaint(hdc);

	return TRUE;
}

//起泡排序
void BubSort(int n)
{
	int i, j;
	bool f;
	Dragon tmp;

	for (i = 0; i < n - 1; i++)
	{
		f = false;
		for (j = 0; j < n - i - 1; j++)
		{
			if (dra[j + 1].Y() < dra[j].Y())	//交换两个恐龙数据
			{
				tmp = dra[j + 1];
				dra[j + 1] = dra[j];
				dra[j] = tmp;
				f = true;
			}
		}
		if (!f)
			break;
	}
}

//****自定义绘图函数*********************************
// 1.对窗口中跑动的恐龙进行排序贴图
// 2.恐龙贴图坐标修正
void MyPaint(HDC hdc)
{
	int w, h, i;

	clockRecord = clock();						// 记录每帧起始时间

	if (picNum == 8)
		picNum = 0;

	//在mdc中先贴上背景图
	SelectObject(bufdc, bg);
	BitBlt(mdc, 0, 0, 640, 480, bufdc, 0, 0, SRCCOPY);

	// 贴上恐龙图之前调用BubSort（）函数进行排序
	// 选择排序算法
	// 可以明显看出两个排序算法——起泡排序和归并排序——的效率差距
	switch (sortMethod)
	{
	case 0:
		mergeSort(dra);
		break;

	default:
		BubSort(draNum);
		break;
	}
	
	//下面这个for循环，按照目前恐龙的移动方向dra[i].dir，
	//选取对应的位图到bufdc中，并设定截切的大小。
	//每一张要在窗口上出现的恐龙图案依次先在mdc上进行透明贴图的操作。
	for (i = 0; i < draNum; i++)
	{
		SelectObject(bufdc, draPic[dra[i].Dir()]);
		switch (dra[i].Dir())
		{
		case 0:
			w = 66;
			h = 94;
			break;
		case 1:
			w = 68;
			h = 82;
			break;
		case 2:
			w = 95;
			h = 99;
			break;
		case 3:
			w = 95;
			h = 99;
			break;
		}
		BitBlt(mdc, (int)dra[i].X(), (int)dra[i].Y(), w, h, bufdc, picNum*w, h, SRCAND);
		BitBlt(mdc, (int)dra[i].X(), (int)dra[i].Y(), w, h, bufdc, picNum*w, 0, SRCPAINT);
	}

	//将最后画面显示在窗口中
	BitBlt(hdc, 0, 0, 640, 480, mdc, 0, 0, SRCCOPY);

	tPre = GetTickCount();         //记录此次绘图时间
	picNum++;


	//下面这个for循环，决定每一只恐龙下一次的移动方向及贴图坐标
	for (i = 0; i < draNum; i++)
	{
		dra[i].update();
		/*
		//随机数除以4的余数来决定下次移动方向，余数0,1,2,3分别代表上，下，左，右
		switch (rand() % 4)          
		{
		//case 0里面的代码，按照目前的移动方向来修正因为各个方向图案尺寸不一致而产生的贴图坐标误差，
		//加入恐龙每次移动的单位量（上，下，左，右每次20个单位）而得到下次新的贴图坐标
		case 0:					     //上
		switch (dra[i].Dir())
		{
		case 0:
		dra[i].Y(dra[i].Y() - 20);
		break;
		case 1:
		dra[i].X(dra[i].X() + 2);
		dra[i].Y(dra[i].Y() - 31);
		break;
		case 2:
		dra[i].X(dra[i].X() + 14);
		dra[i].Y(dra[i].Y() - 31);
		break;
		case 3:
		dra[i].X(dra[i].X() + 14);
		dra[i].Y(dra[i].Y() - 20);
		break;
		}
		//在计算出新的贴图坐标之后，还需判断此新的坐标会不会使得恐龙贴图超出窗口边界，
		//若超出，则将该方向上的坐标设定为刚好等于临界值
		if (dra[i].Y() < 0)
		dra[i].Y(0);
		dra[i].Dir(0);
		break;
		//其他方向按照和上面相同的方法计算
		case 1:				     	//下
		switch (dra[i].Dir())
		{
		case 0:
		dra[i].X(dra[i].X() - 2);
		dra[i].Y(dra[i].Y() + 31);
		break;
		case 1:
		dra[i].Y(dra[i].Y() + 20);
		break;
		case 2:
		dra[i].X(dra[i].X() + 15);
		dra[i].Y(dra[i].Y() + 29);
		break;
		case 3:
		dra[i].X(dra[i].X() + 15);
		dra[i].Y(dra[i].Y() + 29);
		break;
		}

		if (dra[i].Y() > 370)
		dra[i].Y(370);
		dra[i].Dir(1);
		break;
		case 2:				    	//左
		switch (dra[i].Dir())
		{
		case 0:
		dra[i].X(dra[i].X() - 34);
		break;
		case 1:
		dra[i].X(dra[i].X() - 34);
		dra[i].Y(dra[i].Y() - 9);
		break;
		case 2:
		dra[i].X(dra[i].X() - 20);
		break;
		case 3:
		dra[i].X(dra[i].X() - 20);
		break;
		}
		if (dra[i].X() < 0)
		dra[i].X(0);
		dra[i].Dir(2);
		break;
		case 3:				    	//右
		switch (dra[i].Dir())
		{
		case 0:
		dra[i].X(dra[i].X() + 6);
		break;
		case 1:
		dra[i].X(dra[i].X() + 6);
		dra[i].Y(dra[i].Y() - 10);
		break;
		case 2:
		dra[i].X(dra[i].X() + 20);
		break;
		case 3:
		dra[i].X(dra[i].X() + 20);
		break;
		}
		if (dra[i].X() > 535)
		dra[i].X(535);
		dra[i].Dir(3);
		break;
		}
		*/
	}

	cout << "每帧刷新时间:\t" << (clockRecord - clock()) << endl;
}

//****消息处理函数***********************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		int i;

	case WM_DESTROY:					//窗口结束消息，撤销各种DC  
		DeleteDC(mdc);
		DeleteDC(bufdc);
		for (i = 0; i < 4; i++)
			DeleteObject(draPic[i]);
		DeleteObject(bg);
		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break;
	default:							//其他消息
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

