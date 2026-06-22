#include<iostream>
#include<vector>
using namespace std;
void printVector(vector<int>& v)
{
	for (vector<int>::iterator it = v.begin();it != v.end();it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
void test01()
{
	vector<int>v1;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	v1.push_back(40);
	v1.push_back(50);
	printVector(v1);
	v1.pop_back();
	printVector(v1);
	v1.insert(v1.begin(), 100);
	printVector(v1);
	v1.insert(v1.end(), 10);
	printVector(v1);
	v1.insert(v1.begin(), 2, 1000);
	printVector(v1);
	v1.erase(v1.begin());
	printVector(v1);
	v1.erase(v1.begin(), v1.end());
	printVector(v1);
	v1.clear();
	printVector(v1);
}
void test02()
{
	vector<int>v1;
	for (int i = 0;i < 10;i++)
	{
		v1.push_back(i);

	}
	for (int i = 0;i < 10;i++)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	for (int i = 0;i < v1.size();i++)
	{
		cout << v1.at(i) << " ";
	}
	cout << endl;
	cout << "v1的第一个元素为：" << v1.front()<<endl;
	cout << "v1的最后一个元素为：" << v1.back() << endl;
}
int main()
{
	test01();
	test02();
	return 0;
}