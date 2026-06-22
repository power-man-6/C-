#pragma once
#include<iostream>
using namespace std;
//身份抽象类
class Identity
{
public:
	//操作菜单
	virtual void oderMenu() = 0;
	string m_Name;
	int m_Pwd;
};

