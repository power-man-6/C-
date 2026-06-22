#pragma once
#include<iostream>
using namespace std;
class Worker
{public:
	//显示个人信息
	virtual void  showInFo()=0;
	//获取岗位名称
	virtual string GetDeptName() = 0;
public:
	//职工编号
	int m_Id;
	//职工姓名
	string m_Name;
	//部门编号
	int m_DeptId;

};