#pragma once
class Dragon
{
private:
	float x;
	float y;
	int dir;

public:
	Dragon();
	~Dragon();
	//运算符
	bool operator<=(Dragon & a)const;
	//只读读取器
	float Y()const;
	float X()const;
	int Dir()const;
	//写入器
	float Y(float yTmp);
	float X(float xTmp);
	int Dir(int   dirTmp);
};

