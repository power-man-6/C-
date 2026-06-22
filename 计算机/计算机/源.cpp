#include<iostream>
using namespace std;
class Calculator
{
public:int getResult(string oper)
{
	if (oper == "+")
	{
		return m_Num1 + m_Num2;
	}
	else if (oper == "-")
	{
		return m_Num1 - m_Num2;
	}
	else if (oper == "*")
	{
		return m_Num1 * m_Num2;
	}
}
	  int m_Num1;
	  int m_Num2;
};
void test01()
{
	Calculator c;
	c.m_Num1 = 10;
	c.m_Num2 = 10;
	cout << c.m_Num1 << "+" << c.m_Num2 << "=" << c.getResult("+") << endl;
	cout << c.m_Num1 << "-" << c.m_Num2 << "=" << c.getResult("-") << endl;
	cout << c.m_Num1 << "*" << c.m_Num2 << "=" << c.getResult("*") << endl;
}
class Abstractcalculator
{
public:
	virtual int getResult()
	{
		return 0;
	}
	int m_Num1;
	int m_Num2;
};
class Addcalculator :public Abstractcalculator
{
public:
	int getResult()
	{
		return m_Num1 + m_Num2;
	}
};
class Subcalculator :public Abstractcalculator
{
public:
	int getResult()
	{
		return m_Num1 - m_Num2;
	}
};
class MUlcalculator :public Abstractcalculator
{
public:
	int getResult()
	{
		return m_Num1 * m_Num2;
	}
};
void test02()
{
	//创建加法
	Abstractcalculator* abc = new Addcalculator;
	abc->m_Num1 = 10;
	abc->m_Num2= 10;
	cout << abc->m_Num1 << "+" << abc->m_Num2 << "=" << abc->getResult() << endl;
	delete abc;//用完记得删除
	//创建减法
	abc = new Subcalculator;
	abc->m_Num1 = 10;
	abc->m_Num2 = 10;
	cout << abc->m_Num1 << "-" << abc->m_Num1 << "=" << abc->getResult() << endl;
	delete abc;
	//创建乘法
	abc = new MUlcalculator;
	abc->m_Num1 = 12;
	abc->m_Num2 = 12;
	cout << abc->m_Num1 << "*" << abc->m_Num1 << "=" << abc->getResult() << endl;
	delete abc;
}
int main()
{
	//test01();
	test02();
	return 0;
}