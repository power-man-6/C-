#include "WorkerManger.h"
#include"employee.h"
#include"Manger.h"
#include"Boss.h"
WorkerManger::WorkerManger()
{
	//初始化属性
	this->m_EmpNum = 0;
	//初始化数组指针
	this->m_EmpArray = NULL;
}
void WorkerManger::show_Menu()
{
	cout << "\t\t\t**********************************" << endl;
	cout << "\t\t\t*******欢迎使用职工管理系统!******" << endl;
	cout << "\t\t\t********* 0.退出管理程序 *********" << endl;
	cout << "\t\t\t********* 1.增加职工信息 *********" << endl;
	cout << "\t\t\t********* 2.显示职工信息 *********" << endl;
	cout << "\t\t\t********* 4.修改职工信息 *********" << endl;
	cout << "\t\t\t********* 3.删除离职职工 *********" << endl;
	cout << "\t\t\t********* 5.查找职工信息 *********" << endl;
	cout << "\t\t\t********* 6.按照编号排序 *********" << endl;
	cout << "\t\t\t********* 7.清空所有文档 *********" << endl;
	cout << "\t\t\t**********************************" << endl;
	cout << endl;
}
//增加职工
void WorkerManger::Add_Emp()
{
	cout << "请输入增加职工的数量：" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum>0)
{//计算新空间大小
		int newsize = this->m_EmpNum + addNum;//新空间人数=原来的人数+用户输入色人数
	 //开辟新空间
		Worker** newspace = new Worker * [newsize];
	 //将原来的数据拷贝到新的空间
	if (this->m_EmpArray != NULL)
		{
		 for (int i = 0;i < this->m_EmpNum;i++)
		 {
			newspace[i] = this->m_EmpArray[i];
		 }
		}
	//批量添加新数据
	for (int i = 0;i < addNum;i++)
	{
		int id;
		string name;
		int dselect;
		cout << "请输入第" << i + 1 << "个新职工编号" << endl;
		cin >> id;
		cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
		cin >> name;
		cout << "请选举该职工的岗位：" << endl;
		cout << "1.普通岗位" << endl;
		cout << "2.经理" << endl;
		cout << "3.老板" << endl;
		cin >> dselect;

		Worker* Worker = NULL;
		switch (dselect)
		{
		case 1://普通职工
			Worker = new Employee(id, name, 1);
			break;
		case 2://经理
			Worker = new Manger(id, name, 2);
			break;
		case 3://老板
			Worker = new Boss(id, name, 3);
		default:
			break;
			//将创建职工职责，保存到数组
			newspace[this->m_EmpNum + i] = Worker;
		}
		//释放原有空间
		delete[]this->m_EmpArray;
		//更新空间的指向
		this->m_EmpNum = newsize;
		//提示
		cout << "成功添加！" << addNum << "名新职工" << endl;
		this->save();
	} 
	}
	else
	{
		cout << "输入有误" << endl;
	}
	system("pause");
	system("cls");
	cin.get();
}
//保存文件
	void WorkerManger::save()
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::out);//用输出的方式打开wenjian————写文件
			for (int i=0;i<this->m_EmpNum;i++)
			{
				ofs << this->m_EmpArray[i]->m_Id << " "
					<< this->m_EmpArray[i]->m_Name << " "
					<< this->m_EmpArray[i]->m_DeptId << endl;
			}
			//关闭文件
			ofs.close();

}
//退出系统
void WorkerManger::Exitsystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
	WorkerManger::~WorkerManger()
{
	if (this->m_EmpArray != NULL)
	{
		delete[]this->m_EmpArray;
		this->m_EmpArray = NULL;
	}

}
