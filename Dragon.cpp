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
{}

// 运算符
bool Dragon::operator <=(Dragon & a) const
{
	if (y <= a.y)
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

// 更新
// move dragon
void Dragon::move(float xAdd, float yAdd)
{
	x += xAdd;
	y += yAdd;
}
// update position and direction
void Dragon::update()
{
	//随机数除以4的余数来决定下次移动方向，余数0,1,2,3分别代表上，下，左，右
	switch (rand() % 4)          
	{
		//case 0里面的代码，按照目前的移动方向来修正因为各个方向图案尺寸不一致而产生的贴图坐标误差，
		//加入恐龙每次移动的单位量（上，下，左，右每次20个单位）而得到下次新的贴图坐标
	case 0:					     //上
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
		//在计算出新的贴图坐标之后，还需判断此新的坐标会不会使得恐龙贴图超出窗口边界，
		//若超出，则将该方向上的坐标设定为刚好等于临界值
		if (y < 0)
			Y(0);
		Dir(0);
		break;
		//其他方向按照和上面相同的方法计算
	case 1:				     	//下
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
	case 2:				    	//左
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
	case 3:				    	//右
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