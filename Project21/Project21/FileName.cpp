#include<iostream>
using namespace std;
#include<ctime>
//堆的下沉调整
void siftDown(int arr[], int i, int size)
{
	int val = arr[i];
	while (i<=size/2-1)
	{
		int child = 2 * i + 1;
		if (child + 1 < size && arr[child + 1] > arr[child])
		{
			child = child + 1;
		}
		if (arr[child] > val)
		{
			arr[i] = arr[child];
			i = child;//i继续指向它的孩子
		}
		else
		{
			break;
		}

	}
	arr[i] = val;
}
//堆排序
void HeapSort(int arr[], int size)
{
	int n= size - 1;
	//从第一个非叶子节点
	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		siftDown(arr, i, size);
	}
	//把堆顶元素与末尾元素进行交换
	for (int i = n; i > 0; i--)
	{
		int tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;
		siftDown(arr, 0, i);//第三个参数，参与调整元素的个数
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
	HeapSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
	return 0;
}