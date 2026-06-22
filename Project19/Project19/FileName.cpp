#include<iostream>
using namespace std;
#include<ctime>
#include<cstdlib>
void Adarr(int arr[], int size)
{
	int* p = arr;
	int* q = arr + size - 1;
	while (p < q)
	{
		if ((*p & 0x1) == 0)
		{
			p++;
			continue;
		}
		if ((*q & 0x1) == 1)
		{
			q--;
			continue;
		}
		//p->ÆæÊý  q->Å¼Êý
		int tmp = *p;
		*p = *q;
		*q = tmp;
		p++;
		q--;
	}
}
int main()
{
	int arr[10]{};
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100;
	}
	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
	Adarr(arr, 10);
	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl; 
}