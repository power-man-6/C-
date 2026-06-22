#include<iostream>
using namespace std;
//除以函数，当除数为0时抛出异常
double divide(double a, double b)
{
	if (b == 0)
	{//抛出字符串类型的异常信息
		throw"错误：除数不能为0！";
	}
	return a / b;
}
int main() 
{
	double num1, num2;
	cout << "请输入两个数字！" << endl;
	cin >> num1 >> num2;
	//try块：包裹可能异常的代码
	try
	{
		double result = divide(num1, num2);
		cout << "结果是：" << result << endl;
	}
	//catch块：捕获并处理异常（这里匹配字符串的异常）
	catch (const char* errorMsg)

	{
		cout << "捕获到异常：" << errorMsg << endl;
	}
	cout << "程序继续执行..." << endl;
	return 0;
}