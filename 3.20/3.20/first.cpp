#include<iostream>
using namespace std;
int main() 
{
	int arr[] = { 300,500,400,350,1000 };
	int max = 0;
	for (int i = 0;i < 5;i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	cout << "最大值为 : " <<max <<endl;
	return 0;
}