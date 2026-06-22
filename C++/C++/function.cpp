#include<iostream>
using namespace std;
#include<functional>
#include<string>
#include<typeinfo>
/*
function函数对象的实现原理
*/
//应用:
//void hello(string str) { cout << str<< endl; }
//int main()
//{
//	function<void(string)>func1 = hello;
//	func1 (	 "hello world");
//	return 0;
//}
//=========================================
//实现myfunction：
void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }
template<typename Fty>
class myfunction {};
/*template<typename R,typename A1,typename A2>
class myfunction<R(A1,A2)>
{
public:
	using PFUNC = R(*)(A1,A2);
	myfunction(PFUNC pfunc) :_func(pfunc) {};
	R operator()(A1 arg1, A2 arg2)
	{
		return _func(arg1,arg2);
	}
private:
	PFUNC _func;
};
*/
template<typename R,typename... A>
class myfunction<R(A...)>
{
public:
	using PFUNC = R(*)(A...);
	myfunction(PFUNC pfunc) :_func(pfunc) {};
	R operator()(A... args)
	{
		return _func(args...);
	}
private:
	PFUNC _func;
};
//int main()
//{
//	myfunction<void(string)>func1 = hello;
//	myfunction<int(int, int)>func2 = sum;
//	func1("hello word");
//	cout<<func2 (10, 20)<<endl;
//	return 0;
//}