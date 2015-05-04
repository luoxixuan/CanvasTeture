#include "stdafx.h"
#include "Dragon.h"


Dragon::Dragon()
{
	// 设定所有恐龙初始的贴图坐标都为（200,200），初始的移动方向都为向左。
	x = 200;
	y = 200;
	dir = 3;
}

Dragon::~Dragon()
{
}

// 运算符
bool Dragon::operator <=(Dragon & a) const
{
	if (y <= a.Y())
		return true;
	else
		return false;
}

// 只读
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

// 写
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