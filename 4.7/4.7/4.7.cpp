#include<iostream>
using namespace std;
class Person
{
public:
	Person(int age)
	{
		//将年龄数据开辟到堆区
		m_Age = new int(age);
	}
	Person& operator=(Person& p)
	{
		if (m_Age != NULL)
		{
			delete m_Age;
			m_Age = NULL;
		}
		m_Age = new int(*p.m_Age);
		return *this;
	}
	~Person()
	{
		if (m_Age != NULL)
		{
			delete m_Age;
			m_Age = NULL;
		}
	}
	int* m_Age;
};
void test01()
{
	Person p1(18);
	Person p2(20);
	Person p3(30);
	p1 = p2 = p3;
	cout << "p1的年龄为：" <<*p3.m_Age << endl;
}
int main()
{
	test01();
	return 0;
}