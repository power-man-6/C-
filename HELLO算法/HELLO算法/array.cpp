#include<iostream>
using namespace std;
/*随机访问元素*/
int randomAccess(int* nums, int size)
{
	//在区间[0,size]中随机抽取一个元素
	int randomIndex = rand() % size;
	return nums[randomIndex];
}
/*在数组的索引index下插入元素num*/
void insert(int* nums, int size, int index,int num)
{
	for (int i = size - 1; i > index; i--)
	{
		nums[i] = nums[i - 1];
	}
	nums[index] = num;
}
/*在数组的索引index下删除元素num*/
void remove(int *nums, int size, int index)
{
	for (int i=index;i<size-1;i++)
	{
		nums[i] = nums[i + 1];
	}
}
//遍历数组
void traverase(int* nums, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		cout << nums[i] << endl;
	}
}
//求数组元素的和
int sum(int* num, int size)
{
	int sum = 0;
	for (int i = 0; i < size - 1; i++)
	{
		sum += num[i];
	}
	return sum;
}
int main()
{
	/*初始化数组*/
	//储存在栈上
	int arr[5];
	int nums[5] = { 1,3,2,5,4 };
	//存储在堆上(需要主动释放空间)
	int* arr1 = new int[5];
	int* num1 = new int[5] { 1, 3, 2, 5, 4 };
	int size = sizeof(num1) / sizeof(num1[0]);
	cout<<randomAccess(num1, size)<<endl;
	//释放堆上空间
	delete[]arr1;
	delete[]num1;
	return 0;
}