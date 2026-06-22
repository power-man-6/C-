#include<iostream>
using namespace std;
class Myprint
{
public:
	void operator()(string test)
	{
		cout << test << endl;
	}
};
void test01()
{
	Myprint myFunc;
	myFunc(("hellow"));
}
class Myadd
{
public:
	int operator()(int v1, int v2)
	{
		return v1 + v2;
	}

};
void test02()
{
	Myadd;
	int ret =Myadd()(10, 10);
	cout << "ret=" << ret << endl;
	cout << "Myadd()(100,100)=" << Myadd()(100, 100) << endl;
}
int main()
{
	test01();
	test02();
	return 0;
}