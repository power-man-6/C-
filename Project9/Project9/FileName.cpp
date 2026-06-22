#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
//ÆÕÍ¨º¯Êý
void test01(int val)
{
	cout << val << " ";
}
class print
{
public:void operator()(int val)
{
	cout << val << " ";
}
};
int main()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	for_each(v.begin(), v.end(), test01);
	cout << endl;
	for_each(v.begin(), v.end(), print());
	cout << endl;
	return 0;
}