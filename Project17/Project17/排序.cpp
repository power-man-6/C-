#include<iostream>
using namespace std;
#include<time.h>
#include<stdlib.h>
class Array 
{
public:
	//构造函数
	Array(int size=10) :mCur(0), mCar(size)
	{
		mpArr = new int[mCar];
	}
	~Array()
	{
		delete[]mpArr;
		mpArr = nullptr;
	}
public:
	//尾插法
	void push_back(int val)
	{
		if (mCur == mCar)
		{
			expand(2 * mCar);
		}
		mpArr[mCur] = val;
		mCur++;
	}
	//未删法
	void pop_back()
	{
		if(mCur==0)
		{
			return;
		}
		mCur--;
	}
	//按元素下标查找元素
	int find(int pos)
	{
		if (pos < 0 || pos >= mCur)
		{
			return -1;
		}
		else
		{
			return mpArr[pos];
		}
	}

	//按元素的位置删除元素
	void erase(int pos)
	{
		if (pos < 0 || pos >= mCur)
		{
			return;
		}
		for (int i = pos; i < mCur-1; i++)
		{
			mpArr[i] = mpArr[i+1];
		}
		mCur--;
	}
	//按元素的位置插入元素
	void insert(int pos ,int val)
	{
		if (pos<0 || pos>mCur)
		{
			return;
		}
		if (mCur == mCar)
		{
			expand(2 * mCar);
		}//元素后移，为插入元素腾出位置
		for (int i=mCur-1;i>=pos;i--)
		{
			mpArr[i + 1] = mpArr[i];
		}
		mpArr[pos] = val;
		mCur++;
	}
	//扩容函数
	void expand(int size)
	{
		int* p = new int[size];
		memcpy(p, mpArr, sizeof(int)*mCar);
		delete[]mpArr;
		mpArr = p;
		mCar = size;
	}
	void show()
	{
		for (int i = 0; i < mCur; i++)
		{
			cout << mpArr[i] << " ";
		}
		cout << endl;
	}
private:
	int* mpArr;//可扩容的数组
	int mCur;//当前元素的个数
	int mCar;//数组的容量
};
int main()
{
	Array arr;
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		arr.push_back(rand() % 10 + 1);
	}
	arr.show();
	int v=arr.find(3);
	if (v == -1)
	{
		cout << "索引3无效" << endl;
	}
	else {
		cout << "索引3的值是:" << v << endl;
	}
	arr.insert(3, 99);
	arr.show();
	arr.erase(3);
	arr.show();
	arr.pop_back();
	arr.show();


}