#include<iostream>
using namespace std;
#include<vector>
#include<string>
//基数排序
/*
1.找出最长的数字，确定要处理的基数排序的躺数
2.依次由个位开始把相应位数的数字放入相应的桶，完成后，再按桶的顺序依次取出里面的数据
*/
void RadixSort(int arr[], int size)
{
	//确定最长数字
	int maxData = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (maxData < arr[i])
		{
			maxData = arr[i];
		}
	}
	int len = to_string(maxData).size();
	vector<vector<int>> vecs;
	int mod = 10;
	int der = 1;
	for (int i = 0; i < len; i++, mod *= 10, der *= 10)
	{
		vecs.resize(10);
		for (int j = 0; j < size; j++)
		{
			int index = arr[j] % mod / der;
			vecs[index].push_back(arr[j]);
		}
		//依次遍历所有的桶，把元素拷贝回原来的数组中
		int idx = 0;
		for (auto vec : vecs)
		{
			for (int v : vec)
			{
				arr[idx++] = v;
			}
		}
		vecs.clear();
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
	RadixSort(arr,10);
	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}
