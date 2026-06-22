#include<iostream>
#include<deque>
using namespace std;
void printDeque(const deque<int>& d)
{
	for (deque<int>::const_iterator it = d.begin();it != d.end();it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
void test01()
{
	deque<int>d1;
	d1.push_back(10);
	d1.push_back(20);
	d1.push_front(100);
	d1.push_front(200);
	printDeque(d1);
	d1.pop_back();
	printDeque(d1);
	d1.pop_front();
	printDeque(d1);

}
//≤Â»Î
void test02()
{
	deque<int>d;
	d.push_back(10);
	d.push_back(20);
	d.push_front(100);
	d.push_front(200);
	printDeque(d);
	d.insert(d.begin(), 100);
	printDeque(d);
	d.insert(d.end(), 10, 100);
	printDeque(d);
	deque<int>d1;
	d1.push_back(10);
	d1.push_front(200);
	d.insert(d.begin(), d1.begin(), d1.end());
	printDeque(d);
	d.erase(d.begin());
	printDeque(d);

}
int main()
{
	/*test01();*/
	test02();
	return 0;
}
