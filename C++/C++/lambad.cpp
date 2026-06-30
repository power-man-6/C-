#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>
using namespace std;
/*
lambda表达式
函数对象的缺点：
使用在泛型算法参数传递  比较性质/自定义操作  优先级队列  智能指针
*/

/*
lambda表达式的用法：[捕获外部的变量](形参列表)->返回值{操作代码}；
[]:表示不捕获任何外部变量
[=]:表示以传值的形式捕获外部变量
[&]:表示以传引用的方式捕获外部的所有变量
[this]:表示以传引用的方式捕获当前对象的所有成员变量
[=,&a]:表示以传值的形式捕获外部变量，a以传引用的方式捕获
[&,a]:表示以传引用的方式捕获外部变量，a以传值的方式捕获
[a,b]:表示以传值的方式捕获外部变量a,b
[&,a,b]:表示以传引用的方式捕获外部变量，a,b以传值的方式捕获
[=,&a,&b]:表示以传值的方式捕获外部变量，a,b以传引用的方式捕获
*/
template<typename T=void>
class TestLambda01
{
public:
	void operator()()const
	{
		cout << "hello word" << endl;
	}
};
template<typename T=int>
class TeatLambda02
{
public:
	int operator()(int a, int b)const
	{
		return a + b;
	}
};
class TestLambda03
{
public:
	TestLambda03(int& a, int& b) :ma(a), mb(b) {};
	void operator()()const
	{
		int temp = ma;
		ma = mb;
		mb = temp;

	}
private:
	int& ma;
	int& mb;
};
//实例:
int main()
{
	vector<int>vec;
	for (int i = 0; i < 10; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}
	sort(vec.begin(), vec.end());
	for (int i = 0; i < 10; i++)
	{
		cout << vec[i]<<" ";
	}cout << endl;
	sort(vec.begin(), vec.end(), [](int a, int b)->bool {return a > b; });
	for (int val : vec)
	{
		cout << val << " ";
	}cout << endl;

	//65按序插入序列  要找第一个小于65的数字
	auto it = find_if(vec.begin(), vec.end(), [](int a)->bool {return a < 65; });
		if (it != vec.end())
		{
			vec.insert(it, 65);
		}
		for (int val : vec)
		{
			cout << val << " ";
		}cout << endl;
		auto it01 = for_each(vec.begin(), vec.end(), [](int a)
			{
				if(a%2==0)
				   cout << a << " ";
			}); cout << endl;

	
}	
//int main()
//{
//	auto func = []()->void {cout << "hello word" << endl; };
//	/*
//	* ()相当于调用了函数对象的operator方法
//	* ->相当于operator方法的返回值类型，若为空则省略。
//	* {}相当于operator方法的函数体
//	* []相当于捕获外部变量，若为空则不捕获
//	*/
//	auto func1 = [](int a, int b)->int {return a + b; };
//	cout << func1(2, 5) << endl;
//	func();
//	TestLambda01<>t1;
//	t1();
//	TeatLambda02<> t2;
//	cout << t2(2, 5) << endl;
//	int a = 10; 
//	int b = 20;
//	auto fun2 = [&]()//相当与TestLambda03
//	{
//		int temp = a;
//		a = b;
//		b = temp;
//	};
//	fun2();
//	cout << "a" << a << endl;
//	cout << "b" << b << endl;
//	TestLambda03 t3(a,b);
//	t3();
//	cout << "a" << a << endl;
//	cout << "b" << b << endl;
//
//	return 0;
//}