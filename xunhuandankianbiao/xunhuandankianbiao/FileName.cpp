#include<iostream>
using namespace std;
//单项循环链表
class circleLink
{
private:
	circleLink()
	{
		head_ = new Node();
		tail_ = head_;
		head_->next_ = head_;
	}

//析构函数
	~circleLink()
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			head_->next_ = p->next_;
			delete p;
			p = head_->next_;
		}
		delete head_; 
	}
private:
	struct Node
	{
		Node(int data = 0) :data_(data), next_(nullptr) {};
		int data_;
		Node* next_;
	};
	Node* head_;//指向头节点
	Node* tail_;//指向末尾节点
public:
	//尾插法
	void push_back(int val)
	{
		Node* node = new Node(val);
		node->next_ = tail_->next_;//node->head_;
		tail_->next_ = node;
		tail_ = node;
	}
	//头插法
	void push_front(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		if (node->next_ = head_)
		{
			tail_ = node;
		}
	}
};

int main()
{

}