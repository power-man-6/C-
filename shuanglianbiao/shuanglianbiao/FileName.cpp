#include<iostream>
using namespace std;
struct Node {
	int data;
	Node* next_;
	Node* pre_;
	Node(int data)
		:data(data)
		, next_(nullptr)
		, pre_(nullptr) {
	};
};
class DoubleLinkedList {
	//构造函数
public:
	DoubleLinkedList()
		:head_(new Node(0)) {
	}
	~DoubleLinkedList()
	{
		Node* p = head_;
		while (p!= nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
	}
private:
	Node* head_;
public:
	//头插法
	void Insert(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		node->pre_ = head_;
		if (head_->next_ != nullptr)
		{
			head_->next_->pre_ = node;
		}
		head_->next_ = node;
	}

	//尾插法
	void Append(int val)
	{
		Node* p =head_;
		while (p->next_ != nullptr)
		{
			p = p->next_;
		}
		Node* node = new Node(val);
		node->pre_ = p;
		node->next_ = nullptr;
		p->next_ = node;
	}
	//show
	void show()
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			cout << p->data << " ";
			p = p->next_;
		}
		cout << endl;
	}
	//删除节点
	void Delete(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data == val)
			{
				p->pre_->next_ = p->next_;
				if (p->next_ != nullptr)
				{
					p->next_->pre_ = p->pre_;
				}
				delete p;
				return;
			}
		}
	}
	//查找节点
	bool Find(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data ==val)
			{
				cout << "Found" << endl;
				return true;
			}
			p = p->next_;

		}
		cout << "Not Found" << endl;
		return false;
	}
};
int main()
{
	DoubleLinkedList d1;
	d1.Append(1);
	d1.Append(2);
	d1.show();
	return 0;
}