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
{
}

// �����
bool Dragon::operator <=(Dragon & a) const
{
	if (y <= a.Y())
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