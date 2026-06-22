#include<iostream>
using namespace std;
#include<string>
struct Student
{
	string name;
	int age;
	int score;

};
int main()
{
	/*struct Student studarray[3] =
	{
		{"张三",19,62},
		{"李四",20,80},
		{"王五",19,90}
	};
	
	for (int i = 0;i < 3;i++)
	{
		cout << "姓名" << studarray[i].name << "  "
			<< "年龄" << studarray[i].age << "  "
			<< "分数" << studarray[i].score << endl;
	}*/
	struct Student s1 = { "张三",19,100 };
	Student* p = &s1;
	cout << "姓名" << p->name << "年龄" << p->age << "分数" << p->score << endl;
	return 0;
}
	

	
