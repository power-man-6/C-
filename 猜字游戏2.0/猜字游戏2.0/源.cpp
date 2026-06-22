#include<iostream>
using namespace std;
class point
{public:
	void setX(int x)
	{
		m_x = x;
	}
	int getX()
	{
		return m_x;
	}
	void setY(int y)
	{
		m_y = y;
	}
	int getY()
	{
		return m_y;
	}
private:
	int m_x;
	int m_y;
};
class circle
{public:
	void setR(int r) //设置半径
	{
		m_r = r;
	}
	int getR()//获取半径
	{
		return m_r;
	}
	void setCenter(point center) //设置圆心
	{
		m_center = center;
	}
	point getCenter()//获取圆心
	{
		return m_center;
	}
private:
	int m_r;
	point m_center;
};
void isincricle(circle& c, point& p)
{
	int distion =
		(c.getCenter().getX() - p.getX()) * (c.getCenter().getX() - p.getX()) +
		(c.getCenter().getY() - p.getY()) * (c.getCenter().getY() - p.getY());
	int d = c.getR() * c.getR();
	if (distion==d)
	{
		cout << "点在圆上！" << endl;
	}
	else if(distion > d)
	{
		cout << "点在圆外！" << endl;
	}
	else
	{
		cout << "点在圆内！" << endl;
	}
}
int main()
{
	circle c;
	c.setR(10);
	point center;
	center.setX(10);
	center.setY(0);
	c.setCenter(center);
	point p;
	p.setX(10);
	p.setY(10);
	isincricle(c,p);
	return 0;
}