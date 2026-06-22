#include<iostream>
using namespace std;
#include<queue>
class Person
{
public:Person(string name,int age)
{
	this->m_Name = name;
	this->m_Age = age;
}
	  string m_Name;
	  int m_Age;
};
//创建队列
void test01()
{queue<Person>q;
Person p1("孙悟空", 1000);
Person p2("唐僧",30);
Person p3("猪八戒", 6000);
q.push(p1);
q.push(p2);
q.push(p3);
while (!q.empty())
{
	cout << "队头元素__姓名：" << q.front().m_Name << "年龄：" << q.front().m_Age << endl;
	cout << "队头元素__姓名：" << q.back().m_Name << "年龄：" << q.back().m_Age << endl;
	cout << endl;
	q.pop();
}
cout << "队列大小为：" << q.size() << endl;

}

int main()
{
	test01();
	return 0;
}