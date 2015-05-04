#include "stdafx.h"
#include <stdio.h>

//����һ���ṹ��
struct dragon        //����dragon�ṹ���������ϵĿ�������ṹ��Աx��yΪ��ͼ���꣬dirΪĿǰ�������ƶ�����
{
	int x, y;
	int dir;
};

//���峣��
const int draNum = 4096;  //���峣��draNum����������ڻ�����Ҫ���ֵĿ�����Ŀ���ڴ��趨Ϊ4096��
const int sortMethod = 0; //ѡ�������㷨��0Ϊ�鲢��������ֵΪ��������

//ȫ�ֱ�������
HINSTANCE hInst;
HBITMAP draPic[4], bg;   //draPic[4]����������������ƶ�������ͼ����bgΪ�洢����ͼ
HDC		hdc, mdc, bufdc;
HWND	hWnd;
DWORD	tPre, tNow;
int		picNum;
//dragon  dra[draNum];   //����draNum��ֵ��������dra[]�����������ϳ��ֵĿ�����
vector<Dragon> dra;   //����draNum��ֵ��������dra[]�����������ϳ��ֵĿ�����
int clockRecord;

//ȫ�ֺ�������
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				MyPaint(HDC hdc);
void				draInit(int arrSize, vector<Dragon> & sortVec);

//****WinMain������������ڵ㺯��**************************************
int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR     lpCmdLine,
					 int       nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	//��ʼ��
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	GetMessage(&msg, NULL, NULL, NULL);//��ʼ��msg
	//��Ϣѭ��
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

//****���һ�������࣬��������⣬ʹ�ô��ڽṹ��*************************
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

//****��ʼ������*************************************
// ����λͼ���趨����ʼֵ
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HBITMAP bmp;
	hInst = hInstance;

	hWnd = CreateWindow("canvas", "��ͼ����", WS_OVERLAPPEDWINDOW,
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

	bmp = CreateCompatibleBitmap(hdc, 640, 480);  //����һ����λͼ������mdc��
	SelectObject(mdc, bmp);


	// ���ظ��ſ����ܶ�ͼ������ͼ��������0,1,2,3������������ϣ��£������ƶ�
	draPic[0] = (HBITMAP)LoadImage(NULL, "dra0.bmp", IMAGE_BITMAP, 528, 188, LR_LOADFROMFILE);
	draPic[1] = (HBITMAP)LoadImage(NULL, "dra1.bmp", IMAGE_BITMAP, 544, 164, LR_LOADFROMFILE);
	draPic[2] = (HBITMAP)LoadImage(NULL, "dra2.bmp", IMAGE_BITMAP, 760, 198, LR_LOADFROMFILE);
	draPic[3] = (HBITMAP)LoadImage(NULL, "dra3.bmp", IMAGE_BITMAP, 760, 198, LR_LOADFROMFILE);
	bg = (HBITMAP)LoadImage(NULL, "bg.bmp", IMAGE_BITMAP, 640, 480, LR_LOADFROMFILE);

	// �趨���п�����ʼ����ͼ���궼Ϊ��200,200������ʼ���ƶ�����Ϊ����
	draInit(draNum, dra);

	MyPaint(hdc);

	return TRUE;
}
// ������ʼ��
void draInit(int arrSize, vector<Dragon> & sortVec)
{
	//Dragon draTmp;

	for (size_t i = 0; i < arrSize; i++)
	{
		Dragon draTmp;							// ������ʱ��������
		sortVec.push_back(draTmp);				// д��������
	}

	clockRecord = clock();

	mergeSort(sortVec);							// ��ʼ������

	std::cout << "Dragon�����㷨����ʱ��:\t" << (clock() - clockRecord) << "ms" << std::endl;
}

//��������
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
			if (dra[j + 1].Y() < dra[j].Y())	//����������������
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

//****�Զ����ͼ����*********************************
// 1.�Դ������ܶ��Ŀ�������������ͼ
// 2.������ͼ��������
void MyPaint(HDC hdc)
{
	int w, h, i;

	clockRecord = clock();						// ��¼ÿ֡��ʼʱ��

	if (picNum == 8)
		picNum = 0;

	//��mdc�������ϱ���ͼ
	SelectObject(bufdc, bg);
	BitBlt(mdc, 0, 0, 640, 480, bufdc, 0, 0, SRCCOPY);

	// ���Ͽ���ͼ֮ǰ����BubSort����������������
	// ѡ�������㷨
	// �������Կ������������㷨������������͹鲢���򡪡���Ч�ʲ��
	switch (sortMethod)
	{
	case 0:
		mergeSort(dra);
		break;

	default:
		BubSort(draNum);
		break;
	}
	
	//�������forѭ��������Ŀǰ�������ƶ�����dra[i].dir��
	//ѡȡ��Ӧ��λͼ��bufdc�У����趨���еĴ�С��
	//ÿһ��Ҫ�ڴ����ϳ��ֵĿ���ͼ����������mdc�Ͻ���͸����ͼ�Ĳ�����
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

	//���������ʾ�ڴ�����
	BitBlt(hdc, 0, 0, 640, 480, mdc, 0, 0, SRCCOPY);

	tPre = GetTickCount();         //��¼�˴λ�ͼʱ��
	picNum++;


	//�������forѭ��������ÿһֻ������һ�ε��ƶ�������ͼ����
	for (i = 0; i < draNum; i++)
	{
		dra[i].update();
		/*
		//���������4�������������´��ƶ���������0,1,2,3�ֱ�����ϣ��£�����
		switch (rand() % 4)          
		{
		//case 0����Ĵ��룬����Ŀǰ���ƶ�������������Ϊ��������ͼ���ߴ粻һ�¶���������ͼ������
		//�������ÿ���ƶ��ĵ�λ�����ϣ��£�����ÿ��20����λ�����õ��´��µ���ͼ����
		case 0:					     //��
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
		//�ڼ�����µ���ͼ����֮�󣬻����жϴ��µ�����᲻��ʹ�ÿ�����ͼ�������ڱ߽磬
		//���������򽫸÷����ϵ������趨Ϊ�պõ����ٽ�ֵ
		if (dra[i].Y() < 0)
		dra[i].Y(0);
		dra[i].Dir(0);
		break;
		//���������պ�������ͬ�ķ�������
		case 1:				     	//��
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
		case 2:				    	//��
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
		case 3:				    	//��
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

	cout << "ÿ֡ˢ��ʱ��:\t" << (clockRecord - clock()) << endl;
}

//****��Ϣ������***********************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		int i;

	case WM_DESTROY:					//���ڽ�����Ϣ����������DC  
		DeleteDC(mdc);
		DeleteDC(bufdc);
		for (i = 0; i < 4; i++)
			DeleteObject(draPic[i]);
		DeleteObject(bg);
		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break;
	default:							//������Ϣ
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

