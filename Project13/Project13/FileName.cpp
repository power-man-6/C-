#include<iostream>
using namespace std;
#include<stdlib.h>
#include<time.h>
class Array
{
public :
	Array(int size = 10) : mCap(0), mCur(size)
	{
		mpArry = new int[mCur];
	}
	~Array()
	{
		delete[]mpArry;
		mpArry = nullptr;
	} 

private:int *mpArry;
	   int mCap;//数组的容量
	   int mCur;//有效值
public:  void expand(int size)
	  {
		  int* p = new int[size];
		  memcpy(p, mpArry, sizeof(int) * mCap);
		  delete[]mpArry;
		  mpArry = p;
		  mCap = size;
	  }
	void push_back(int val)
{
	if (mCur == mCap) 
	{
		expand(2 * mCap);
	}
	mpArry[mCur++]=val;
}
	void pop_back()
	{
		if (mCur = 0)
		{
			return;
		}
		mCur--;
	}
	//移动元素
	void sert(int pos, int val)
	{
		if (pos<0 || pos>=mCur)
		{
			return;
		}
		if (mCur == mCap)
		{
			expand(2 * mCap);
		}
		for (int i = mCur - 1; i >= pos; i--)
		{
			mpArry[i+1] = mpArry[i];
		}
		mpArry[pos] = val;
		mCur++;
	}
	
	void easer(int pos)
	{
		if (pos < 0 || pos >= mCur)
		{
			return;
		}
		for (int i = pos + 1; i < mCur; i++)
		{
			mpArry[i + 1] = mpArry[i];
		}
		mCur--;
	}
	 int find(int val)
	{
		for (int i = 0; i < mCur; i++)
		{
			if (mpArry[i] = val)
			{
				return i;
			}

		}return -1;
	}void show()const
	{
		for (int i = 0; i < mCur; i++)
		{
			cout << mpArry[i];
		}
		cout << endl;
	}
};
int main()
{
	Array arr;
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		arr.push_back(rand() % 100);
	}
	arr.show();

	return 0;
}