#include<iostream>
using namespace std;
#include<ctime>
#include<cstdlib>
#include<functional>
//优先级队列
class PriorityQueue
{
public:
	using Comp = function<bool(int, int)>;
	PriorityQueue(int cap = 20, Comp comp = greater<int>())
		:size_(0)
		, cap_(cap)
		, comp_(comp)
	{
		que_ = new int[cap_];
	}
	PriorityQueue(Comp comp )
		:size_(0)
		, cap_(20)
		, comp_(comp)
	{
		que_ = new int[cap_];
	}
	~PriorityQueue()
	{
		delete[]que_;
		que_ = nullptr;
	}
public:
	//入堆操作
	void push(int val)
	{
		//判断扩容
		if (size_ == cap_)
		{
			int* p = new int[2 * cap_];
			memcpy(p, que_, cap_ * sizeof(int));
			delete[]que_;
			que_ = p;
			cap_ *= 2;

		}
		if (size_ == 0)
		{
			//只有一个元素，不用进行堆的上浮调整
			que_[size_] = val;
		}
		else
		{
			//堆里面有多个元素，需要进行上浮调整
			siftup(size_, val);
		}
		size_++;
	}

	//出堆的操作
	void pop()
	{
		if (size_ == 0)
			throw"container is empty";
		size_--;
		if (size_ > 0)
		{
			siftDown(0, que_[size_]);
		}
	}
	bool empty()const { return size_ == 0; }
	int top()const
	{
		if (size_ == 0)
			throw" container is empty!";
		return que_[0];
	}
	int  size()const { return size_; }
private:
	//入堆上浮
	void siftup(int i, int val)
	{
		while (i > 0)//最多计算到根节点
		{
			int father = (i - 1) / 2;
			if (comp_(val, que_[father]))
			{
				que_[i] = que_[father];
				i = father;
			}
			else
			{
				break;
			}
		}
		//把val放到i的位置
		que_[i] = val;
	}
	//下称调整
	void siftDown(int i, int val)
	{
		while (i <size_ / 2)
		{
			int child = 2*i + 1;
			if (child + 1 < size_&&comp_(que_[child+1],que_[child]))
			{
				child = child + 1;
			}
			if (comp_(que_[child], val))
			{
				que_[i] = que_[child];
				i = child;
			}
			else
			{
				break;
			}
		}
		que_[i] = val;
	}
	int* que_;//指向动态扩容的数组
	int size_;// 数组元素的个数
	int cap_;//数组的总空间大小
	Comp comp_;//比较器对象
};
int main()
{
	PriorityQueue que([](int a, int b) {return a < b; });
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		que.push(rand() % 100);
	}
	while (!que.empty())
	{
		cout << que.top() << " ";
		que.pop();
	}
	cout << endl;
	return 0;
}