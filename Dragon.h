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
	//�����
	bool operator<=(Dragon & a)const;
	//ֻ����ȡ��
	float Y()const;
	float X()const;
	int Dir()const;
	//д����
	float Y(float yTmp);
	float X(float xTmp);
	int Dir(int   dirTmp);
};

