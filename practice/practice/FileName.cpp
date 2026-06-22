#include<iostream>
using namespace std;
int sum(int a=30,int b=0);
int sum(int a, int b)
{
	return a+b;
}
int main()
{
	
		int b= 20;
		cout << sum(b) << endl;
}