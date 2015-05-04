#include "stdafx.h"
#include "Dragon.h"


Dragon::Dragon()
{
	// �趨���п�����ʼ����ͼ���궼Ϊ��200,200������ʼ���ƶ�����Ϊ����
	x = 200;
	y = 200;
	dir = 3;
}

Dragon::~Dragon()
{}

// �����
bool Dragon::operator <=(Dragon & a) const
{
	if (y <= a.y)
		return true;
	else
		return false;
}

// ֻ��
float Dragon::Y()const
{
	return y;
}
float Dragon::X()const
{
	return x;
}
int Dragon::Dir()const
{
	return dir;
}

// д
float Dragon::X(float xTmp)
{
	x = xTmp;
	return x;
}
float Dragon::Y(float yTmp)
{
	y = yTmp;
	return y;
}
int Dragon::Dir(int dirTmp)
{
	dir = dirTmp;
	return dir;
}

// ����
// move dragon
void Dragon::move(float xAdd, float yAdd)
{
	x += xAdd;
	y += yAdd;
}
// update position and direction
void Dragon::update()
{
	//���������4�������������´��ƶ���������0,1,2,3�ֱ�����ϣ��£�����
	switch (rand() % 4)          
	{
		//case 0����Ĵ��룬����Ŀǰ���ƶ�������������Ϊ��������ͼ���ߴ粻һ�¶���������ͼ������
		//�������ÿ���ƶ��ĵ�λ�����ϣ��£�����ÿ��20����λ�����õ��´��µ���ͼ����
	case 0:					     //��
		switch (Dir())
		{
		case 0:
			move(0, 20);
			break;
		case 1:
			move(2, -31);
			break;
		case 2:
			move(14, -31);
			break;
		case 3:
			move(14, -20);
			break;
		}
		//�ڼ�����µ���ͼ����֮�󣬻����жϴ��µ�����᲻��ʹ�ÿ�����ͼ�������ڱ߽磬
		//���������򽫸÷����ϵ������趨Ϊ�պõ����ٽ�ֵ
		if (y < 0)
			Y(0);
		Dir(0);
		break;
		//���������պ�������ͬ�ķ�������
	case 1:				     	//��
		switch (Dir())
		{
		case 0:
			move(-2, 31);
			break;
		case 1:
			move(0, 20);
			break;
		case 2:
			move(15, 29);
			break;
		case 3:
			move(15, 29);
			break;
		}

		if (y > 370)
			Y(370);
		Dir(1);
		break;
	case 2:				    	//��
		switch (Dir())
		{
		case 0:
			move(-34, 0);
			break;
		case 1:
			move(-34, -9);
			break;
		case 2:
			move(-20, 0);
			break;
		case 3:
			move(-20, 0);
			break;
		}
		if (x < 0)
			X(0);
		Dir(2);
		break;
	case 3:				    	//��
		switch (Dir())
		{
		case 0:
			move(6, 0);
			break;
		case 1:
			move(6, -10);
			break;
		case 2:
			move(20, 0);
			break;
		case 3:
			move(20, 0);
			break;
		}
		if (x > 535)
			X(535);
		Dir(3);
		break;
	}
}