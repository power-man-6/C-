#include<iostream>
using namespace std;
#include<fstream>
//1.包含头文件
void test01()
{
	//2,创建流对象
	ifstream ifs;
	//3.打开文件并判断文件是否打开
	ifs.open("test.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}
	//4.读文件(四种)
	//(1)
	char buf[1024] = { 0 };
	while (ifs >> buf)
	{
		cout << buf << endl;
	}
	ifs.close();
}
int main()
{
	test01();
	return 0;
}