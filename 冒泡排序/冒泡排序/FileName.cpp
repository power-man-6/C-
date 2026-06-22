#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
//冒泡排序
//void Bubblesort(int arr[], int size)
//{
//	bool flag = false;
//	for (int i = 0; i < size - 1; i++) 
//	{
//		//一趟
//		for (int j=0; j < size - 1-i; j++)
//		{
//			if (arr[j] > arr[j + 1])
//			{
//				int  temp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = temp;
//			}flag = true;
//		}
//		if (!flag)
//		{
//			return;
//		}
//	}
// 
//}
//选择排序
//void choicesort(int arr[], int size)
//{
//	for (int i = 0; i < size - 1; i++)
//	{
//		int min = arr[i];
//		int k = i;
//		for (int j =i+1; j < size ; j++)
//		{
//			if (min > arr[j])
//			{
//				min = arr[j];
//				k = j;
//			}
//		}
//		if (k != i)
//		{
//			int temp = arr[i];
//			arr[i] = arr[k];
//			arr[k] = temp;
//		}
//	}
//	
//}
//void Insertsort(int arr[], int size)
//{
//	for (int i = 1; i < size; i++)
//	{
//		int val = arr[i];
//		int j = i-1;
//		for (; j >= 0; j--)
//		{
//			if (arr[j] <= val)
//			{
//				break;
//			}
//			arr[j + 1] = arr[j];
//		}
//		arr[j + 1] = val;
//	}
//}
//希尔排序 
void shellsort(int arr[],int size)
{
	for (int gas = size / 2; gas > 0; gas /= 2)
	{
		for (int i = gas; i < size; i++)
		{
			int val = arr[i];
			int j = i - gas;
			for (; j >= 0; j -= gas)
			{
				if (arr[j] <= val)
				{
					break;
				}
				arr[j + gas] = arr[j];
			}
			arr[j + gas] = val;
		}
	}
}
int main()
{
	int arr[10];
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100 + 1;
	}
	for (int v : arr)
	{
		cout << v << " ";

	}
	cout << endl;
	int size = sizeof(arr) / sizeof(arr[0]);
	shellsort(arr, size);
	for (int v : arr)
	{
		cout << v << " ";

	}
	cout << endl;
	return 0;
}