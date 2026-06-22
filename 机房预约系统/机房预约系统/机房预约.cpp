#include<iostream>
using namespace std;
#include<string>
#include"Identity.h"
#include<fstream>
#include"globalFile.h"
#include"Student.h"
#include"Teacher.h"
#include"Manager.h"
void LoginIn(string fileName, int type)
{
	//父类指针用来指向子类指针
	Identity* Person = NULL;
	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);
	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	//接受用户信息
	int id = 0;
	string name;
	string pwd;
	//判断身份
	if (type == 1)//学生身份
	{
		cout << "请输入你的学号：" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入你的职工号：" << endl;
		cin >> id;
	}
	cout << "请输入你的姓名：" << endl;
	cin >> name;
	cout << "请输入你的密码：" << endl;
	cin >> pwd;
	if (type == 1)//学生验证
	{
		int fId;
		string fName;
		string fPwd;
		while (ifs>>fId&&ifs>>fName&&ifs>>fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");
				Person = new Student(id, name, pwd);
				return;
			}
		}
	}
	else if (type == 2)//教师验证
	{
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");
				Person = new Teacher(id, name, pwd);
			}
		}
	}
	else if (type == 3)//管理员验证
	{
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				cout << "管理员登录验证成功！" << endl;
				system("pause");
				system("cls");
				Person = new Manager(name, pwd);
			}
		}
	}
	cout << "登录失败！" << endl;
	system("pause");
	system("cls");
	return;
}
//创建菜单
void Menue()
{
	cout << "================欢迎使用机房预约系统==================" << endl;
	cout << "请输入你的身份！" << endl;
	cout << "_______________________________________________________" << endl;
	cout << " \t\t| 1.学生登录   |\t\t" << endl;
	cout << " \t\t| 2.教师登录   |\t\t" << endl;
	cout << " \t\t| 3.管理员登录 | \t\t" << endl;
	cout << " \t\t| 0.退出系统   |\t\t" << endl;
	cout << "_______________________________________________________" << endl;
	cout << "请输入您的选择：" << endl;
}
int main()
{
	
	while (true)
	{
		int select = 0;
		Menue();
		cin >> select;
		switch (select)
		{
		case 1://学生登录
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2://教师登录
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://管理员登录
			LoginIn(DAMIN_FILE, 3);
			break;
		case 0://退出
			cout << "欢迎下次使用！" << endl;
			return 0;
			break;
		default:
			cout << "输入有误，请重新输入！" << endl;
			system("pause");
			system("cls");
		}
	}
	
	system("pause");
	return 0;
}