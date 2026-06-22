#include<iostream>
using namespace std;
#include"WorkerManger.h"
#include"Worker.h"
#include"employee.h"
#include"Manger.h"
#include"Boss.h"
int main()
{/*
	Worker* worker = NULL;
	worker = new Employee(1, "张三",1);
	worker->showInFo();
	delete worker;
	worker = new Manger(2, "李四", 2);
	worker->showInFo();
	delete worker;
	worker = new Boss(3, "张三", 3);
	worker->showInFo();
	delete worker;*/
	WorkerManger wm;
	int choice = 0;
	while (true)
	{
		wm.show_Menu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			wm.Exitsystem();//退出管理程序
			break;
		case 1:wm.Add_Emp();//增加职工信息
			break;
		case 2://显示职工信息
		break;
		case 3://修改职工信息
		break;
	    case 4://删除离职职工
		break;
		case 5://查找职工信息
		break;
		case 6://按照编号排序
			break;
		case 7://清空所有文档
			break;
	default:
			system("cls");
			break;
		}
	}
	
	return 0;
}