#include<iostream>
#include <stdexcept>
using namespace std;
//队列的特点:
//1.先进先出2.后进后出
//queue  push()  pop()  front()  back()  empty()  size()
class Queue
{
public:
	Queue(int size)
		:cap_(size),
		front_(0),
		rear_(0),
		size_(0)
	{
		pQue = new int[cap_];
	}
	~Queue()
	{
		delete[] pQue;
		pQue = nullptr;
	}
public:
	//入队
	void push(int val)
	{ 
		if ((rear_ + 1) % cap_ == front_)
		{
			expand(2 * cap_);
		}
		pQue[rear_] = val;
		rear_ = (rear_ + 1) % cap_;
		size_++;
	}
	//出队
	void pop()
	{
		if(empty())
		{
			return;
		}
		front_ = (front_ + 1) % cap_;
		size_--;
	}
	//获取队头元素 
	int front()const
	{
		if (empty())
			throw out_of_range("Queue::front() - queue is empty");
		return pQue[front_];
	}
	//获取队尾元素
	int back()const
	{
		if (empty())
			throw out_of_range("Queue::back() - queue is empty");
		return pQue[(rear_ - 1 + cap_) % cap_];
	}
	//判断队列是否为空
	bool empty()const
	{
		return front_ ==rear_;
	}
	//获取队列的元素个数
	int size()
	{
		return size_;
	}
private:
	void expand(int size)
	{	
		int* NewQue = new int[size];
		int i = 0;
		int j = front_;
		for (; j != rear_; i++, j = (j + 1) % cap_)
		{
			NewQue[i] = pQue[j];
		}
		delete[]pQue;
		pQue = NewQue;
		cap_ = size;
		front_ = 0;
		rear_ = i;
	}
private:
	int* pQue;
	int cap_;//空间容量
	int front_;//队头
	int rear_;//队尾
	int size_;//元素个数
};
int main()
{	

	Queue q(4);
	q.push(1);
	q.push(2);
	q.push(3);
	cout << "front: " << q.front() << ", back: " << q.back() << ", size: " << q.size() << endl;
	q.pop();
	cout << "front after pop: " << q.front() << ", size: " << q.size() << endl;
	return 0;
}