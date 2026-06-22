#pragma once
#include<iostream>
using namespace std; 
#include"Worker.h"
#include"employee.h"
#include"Manger.h"
#include"Boss.h"
#include<fstream>
#define  FILENAME "empFile .txt"
class WorkerManger
{
public:
	WorkerManger();//构造函数
	//展示菜单
	void show_Menu();
	//退出系统
	void Exitsystem();
	//记录文件中的人数
	int m_EmpNum;
	//员工数组指针
	Worker** m_EmpArray;
	void Add_Emp();
	//保存文件
	void save();
	~WorkerManger();//析构函数
};