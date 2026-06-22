#include<iostream>
using namespace std;
class Animal
{
public:	int M_Age;
};
class sheep : virtual public Animal{};
class Tuo :virtual  public Animal {};
class sheepTuo :public sheep,public Tuo {};
void test()
{
	sheepTuo st;
	st.sheep::M_Age = 100;
	st.Tuo::M_Age = 200;
	cout << "M_Age=" << st.M_Age << endl;
	cout << "sheep=" << st.sheep::M_Age << endl;
	cout << "Tuo=" << st.Tuo::M_Age << endl;
}
int main()
{
	test();

}