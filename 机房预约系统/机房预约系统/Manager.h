#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
class Manager :public Identity
{
public:
	//默认构造
	Manager();
	//有参构造
	Manager(string name, string pwd);
	//菜单界面
	virtual void oderMenu();
	//添加账户
	void addManager();
	//查看账户
	void showManager();
	//查看机房信息
	void showComplate();
	//清空账户
	void cleanFile();

};