#include<iostream>
using namespace std;
class  Animal
{
public:
 virtual void speak()
	{
		cout << "¶¯Îï½Ð" << endl;
	}
};
class cat: public Animal
{
public:
	void speak()
	{
		cout << "Ã¨½Ð" << endl;
	}
};
class dog :public Animal
{
public:
	void speak()
	{
		cout << "¹·½Ð" << endl;
	}
};
void Dospeak(Animal&animal)
{
	animal.speak();
}
void test01()
{
	cat cat01;
	Dospeak(cat01);
	dog dog01;
	Dospeak(dog01);
}
int main()
{
	test01();
	return 0;
}