#pragma once
#include <iostream>
using namespace std;
#include"Worker.h"
class Manger :public Worker
{
public:
	//构造函数
	Manger(int id, string name, int did);
	//显示个人信息
	virtual void  showInFo();
	//获取岗位名称
	virtual string GetDeptName();
};