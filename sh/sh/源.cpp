#include<iostream>
#include<vector>
using namespace std;
int main()
{
	vector<int>v;
	int array[10] = { 1,2,3,4,5,6,7,8,9,10 };
	v = vector<int>(array, array + 10);
	//第一种遍历
	cout << "1:" << endl;
	for (int i = 0;i < v.size();++i)
		cout << v[i] << " ";
	//第二种遍历
	cout <<endl <<"2:" << endl;
	vector<int>::iterator i;  
	for (i = v.begin();i != v.end();++i)
		cout << *i << " " ;
	//第三种遍历
	cout << endl << "3:" << endl;
	for (i = v.begin();i < v.end();++i)
		cout << *i << " ";
	//第四种遍历
	cout << endl << "4:" << endl;
	i = v.begin();
	while (i < v.end())
	{
		cout << *i << " ";
		i += 2;
	}


}