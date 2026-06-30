#include<iostream>
#include<algorithm>
#include<functional>
#include<map>
#include<memory>
using namespace std;
/*
lambda表达式只能使用在语句当中，如果想跨语句使用之前定义好的lambda表达式，应该怎么做，
用什么类型来表示?
lambda表达式=》函数对象
1：用function类型来表示函数对象的类型
*/
int main()
{
	//智能指针自定义删除器 delete p;FILE* fclose(FIKEE*)
	unique_ptr<FILE, function<void(FILE*)>>
		ptr1(fopen("data.txt", "w"), [](FILE* pf) {fclose(pf); });
# if 0
	map<int, function<int(int, int)>>caculateMap;
	caculateMap[1] = [](int a, int b)->int {return a + b; };
	caculateMap[2] = [](int a, int b)->int {return a - b; };
	caculateMap[3] = [](int a, int b)->int {return a * b; };
	caculateMap[4] = [](int a, int b)->int {return a / b; };

	cout << "请输入:" << endl;
	int choice;
	cin >> choice;
	cout << "10+15=" << caculateMap[choice](10, 15) << endl;
	return 0;
#endif
}