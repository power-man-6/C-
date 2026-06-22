#pragma once
#include<iostream>
#include"Identity.h"
using namespace std;
class Student :public Identity
{
public:
	//默认构造
	Student();
	//有参构造
	Student(int Id, string m_Name, string m_Pwd);
	//菜单
	virtual void oderMenu();
	//申请预约
	void applyOrder();
	//查看我的预约
	void showOrder();
	//查看所有的预约
	void showallOrder();
	//取消预约
	void cancelOder();
	//学生学号
	int m_Id;
};