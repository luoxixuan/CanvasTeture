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
	// 运算符重载
	bool operator<=(Dragon & a)const;
	// 读取器
	float Y()const;
	float X()const;
	int Dir()const;
	// 写入器
	float Y(float yTmp);
	float X(float xTmp);
	int Dir(int   dirTmp);
	// 更新
	void update();
private:
	// move the dragon
	void move(float xAdd, float yAdd);
};

