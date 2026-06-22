#include<iostream>
using namespace std;
#define MAX 1000
struct Person //通讯录信息
{
	string m_Name;//通讯录姓名
	int  m_sex;//1--男 2--女 通讯录性别
	int m_age;//年龄
	string m_phone;//电话号码
	string m_addr;//家庭住址
};
struct Addressbooks//创建一个通讯录
{
	struct Person personArray[MAX];
	int m_size;
};
	void showMenu() 
{
	cout << "************************" << endl;
	cout << "***** 1,添加联系人 *****" << endl;
	cout << "***** 2,显示联系人 *****" << endl;
	cout << "***** 3,删除联系人 *****" << endl;
	cout << "***** 4,查找联系人 *****" << endl;
	cout << "***** 5,修改联系人 *****" << endl;
	cout << "***** 6,清空联系人 *****" << endl;
	cout << "***** 0,退出联系人 *****" << endl;
	cout << "************************" << endl;
}
	void addPerson(Addressbooks* abs) //添加
    {
		if (abs->m_size == MAX)
		{
			cout << "通讯录已满，无法添加！" << endl;
			return;
		}
		else {

			string name;
			cout << "请输入姓名；" << endl;
			cin >> name;
			abs->personArray[abs->m_size].m_Name = name;

			cout << "请输入性别；" << endl;
			cout << "1----男" << endl;
			cout << "2----女" << endl;
			int sex = 0;
			while (true)
			{
				cin >> sex;
				if (sex == 1 || sex == 2)
				{
					abs->personArray[abs->m_size].m_sex = sex;
					break;
				}
				else
				{
					cout << "输入有误，请重新输入！" << endl;
				}
			}

				cout << "请输入年龄；" << endl;
				int age = 0;
				cin >> age;
				abs->personArray[abs->m_size].m_age = age;
				cout << "请输入电话号码" << endl;
				string phone;
				cin >> phone;
				abs->personArray[abs->m_size].m_phone = phone;
				cout << "请输入住址" << endl;
				string address;
				cin >> address;
				abs->personArray[abs->m_size].m_addr = address;
				abs->m_size++;
				cout << "添加成功" << endl;
				system("pause");
				system("cls");
			
		}
	}
  	void showPerson(Addressbooks* abs)//显示
	{
		if (abs->m_size == 0)
		{
			cout << "当前记录为空！" << endl;
		}
		else 
		{
			for (int i = 0;i < abs->m_size;i++)
			{
				cout << "姓名：" << abs->personArray[i].m_Name << "\t";
				cout << "性别：" << (abs->personArray[i].m_sex==1 ? "男" :"女")<<"\t";
				cout << "年龄：" << abs->personArray[i].m_age << "\t";
				cout << "电话：" << abs->personArray[i].m_phone << "\t";
				cout << "地址：" << abs->personArray[i].m_addr << endl;
			}
		}
		system("pause");
		system("cls");
	}
	void dele(Addressbooks *abs)
	{
	}
	int isExist(Addressbooks* abs, string name)
	{
		for (int i = 0;i < abs->m_size;i++)
		{
			if (abs->personArray[i].m_Name == name)
			{
				return i;
			}
		}  return -1;
		
	}
	void deletePerson(Addressbooks * abs)
	{
		cout<<"请输入您想要删除的姓名：" << endl;
		string name;
		cin >> name;
		int ret = isExist(abs, name);
		if (ret != -1)
		{
			for (int i = ret;i < abs->m_size;i++)
			{
				abs->personArray[i] = abs->personArray[i + 1];
			}
			abs->m_size--;
			cout << "删除成功！" << endl;
		}
		else 
		{
			cout << "查无此人！" << endl;
		}
		system("pause");
		system("cls");
	}//3,删除联系人
	void findPerson(Addressbooks* abs)
	{
		cout << "请输入您想查找的姓名：" << endl;
		string name;
		cin >> name;
		int ret = isExist(abs, name);
		if (ret != -1) 
		{
			cout << "姓名：" << abs->personArray[ret].m_Name << "\t";
			cout << "性别：" << abs->personArray[ret].m_sex << "\t";
			cout << "年龄：" << abs->personArray[ret].m_age << "\t";
			cout << "电话：" << abs->personArray[ret].m_phone << "\t";
			cout << "住址：" << abs->personArray[ret].m_addr << endl;
		}
		else { cout << "查无此人！" << endl; }
		system("pause");
		system("cls");
	}
	void modifyPerson(Addressbooks* abs)
	{
		cout << "请输入您想修改的联系人：" << endl;
		string name;
		cin >> name;
		int ret = isExist(abs, name);
		if (ret!=-1)
		{
			string name;
			cout << "请输入姓名；" << endl;
			cin >> name;
			abs->personArray[ret].m_Name = name;

			cout << "请输入性别；" << endl;
			cout << "1----男" << endl;
			cout << "2----女" << endl;
			int sex = 0;
			while (true)
			{
				cin >> sex;
				if (sex == 1 || sex == 2)
				{
					abs->personArray[ret].m_sex = sex;
					break;
				}
				else
				{
					cout << "输入有误，请重新输入！" << endl;
				}
			}

			cout << "请输入年龄；" << endl;
			int age = 0;
			cin >> age;
			abs->personArray[ret].m_age = age;
			cout << "请输入电话号码" << endl;
			string phone;
			cin >> phone;
			abs->personArray[ret].m_phone = phone;
			cout << "请输入住址" << endl;
			string address;
			cin >> address;
			abs->personArray[ret].m_addr = address;
			abs->m_size++;
			cout << "修改成功" << endl;
			system("pause");
			system("cls");
		}
		else
		{
			cout << "查无此人！" << endl;
		}
	}
	void cleanPerson(Addressbooks* abs)
	{
		abs->m_size = 0;
		cout << "已清空" << endl;
		system("pause");
		system("cls");
	}
int main()
{
	Addressbooks abs;
	abs.m_size = 0;
	int select = 0;//创建用户输入的变量
	while (true)
	{
		showMenu();
		cin >> select;
	
			switch (select)
			{
			case 1:   
				addPerson(&abs);//1,添加联系人
				break;
			case 2:
				showPerson(&abs);//2,显示联系人
				break;
			case 3:
				deletePerson(&abs);
				break;
			case 4:findPerson(&abs);//4,查找联系人
				break;
			case 5:modifyPerson(&abs);//5,修改联系人
				break;
			case 6:cleanPerson(&abs);//6,清空联系人
				break;
			case 0://0,退出联系人
				cout << "欢迎下次使用！" << endl;
				system("pause");
				return 0;
				break;
			default:
				break;
		     }
	}
	
	system("pause");
	return 0;
}