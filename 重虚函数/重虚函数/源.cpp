#include<iostream>
using namespace std;
class Animal
{
public:
	Animal()
	{
		cout << "Animal构造函数的调用" << endl;
	}
	virtual void speak() = 0;
	/*virtual ~Animal()
	{
		cout << "Animal析构函数的调用" << endl;
	}*/
	virtual ~Animal() = 0;
};
Animal::~Animal()
{
	cout << "Animal析构函数的调用" << endl;
}
class Cat :public Animal
{
public:
	Cat(string name)
	{
		cout << "Cat构造函数的调用" << endl;
		m_Name = new string(name);
	}
	virtual void speak()
	{
		cout << *m_Name << "小猫在说话" << endl;
	}
	~Cat()
	{
		cout << "Cat析构函数的调用" << endl;
		if (this->m_Name != NULL)
		{
			delete m_Name;
			m_Name = NULL;
		}
	}
public:string *m_Name;
};
void test()
{
	Animal*animal = new Cat("Tom");
	animal->speak();
}
int main()
{
	test();
	return 0;
}