#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

// 单链表节点定义
struct Node {
	Node(int data = 0) :data_(data), next_(nullptr) {}
	int data_;
	Node* next_;
};

// 单链表实现（使用哨兵头节点）
class Clink
{
public:
	Clink()
	{
		// 初始化哨兵头节点
		head_ = new Node();
	}
	~Clink()
	{
		// 释放链表中所有节点（包含哨兵）
		Node* p = head_;
		while (p != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
		head_ = nullptr;
	}
public:
	// 在链表尾部插入节点 O(n)
	void PushBack(int val)
	{
		// 找到链表末尾
		Node* cur = head_;
		while (cur->next_ != nullptr)
		{
			cur = cur->next_;
		}
		// 创建并插到末尾
		Node* node = new Node(val);
		cur->next_ = node;
	}
	// 头插法 O(1)
	void PushFront(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
	}
	// 打印链表（不打印哨兵）
	void Print()
	{
		Node* cur = head_->next_;
		while (cur != nullptr)
		{
			cout << cur->data_ << " ";
			cur = cur->next_;
		}
	}
	// 删除第一个匹配的节点
	void Remove(int val)
	{
		Node* q = head_;
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				q->next_ = p->next_;
				delete p;
				return;
			}
			else
			{
				q = p;
				p = p->next_;
			}
		}
	}
	// 删除所有匹配的节点
	void RemoveAll(int val)
	{
		Node* p = head_->next_;
		Node* q = head_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				q->next_ = p->next_;
				delete p;
				p = q->next_;
			}
			else
			{
				q = p;
				p = p->next_;
			}
		}
	}
	// 查找（线性搜索）
	bool Find(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				return true;
			}
			else
			{
				p = p->next_;
			}
		}
		return false;
	}

private:
	Node* head_; // 哨兵头节点
	friend void Revers(Clink& clink);
	friend bool IsLinkHasCircle(Node* head, int& val);
	friend void MergetLink(Clink& link1, Clink& link2);
	friend bool FindKthToTail(Clink& clink, int k, int& val);
};

// 反转链表（就地反转，使用哨兵）
void Revers(Clink& clink)
{
	Node* p = clink.head_->next_;
	if (p == nullptr)
	{
		return;
	}
	clink.head_->next_ = nullptr;
	while (p != nullptr)
	{
		Node* q = p->next_;
		p->next_ = clink.head_->next_;
		clink.head_->next_ = p;
		p = q;
	}
}

// 求倒数第 K 个节点的值（K 从 1 开始）
bool FindKthToTail(Clink& clink, int k, int& val)
{
	if (k < 1) return false;
	Node* head = clink.head_;
	Node* pre = head;
	Node* p = head;
	for (int i = 0; i < k; i++)
	{
		p = p->next_;
		if (p == nullptr)
		{
			return false;
		}
	}
	// pre 在哨兵，p 在第 k 个节点。两指针同步前进至 p 到尾时，pre 即为倒数第 k 节点
	while (p != nullptr)
	{
		pre = pre->next_;
		p = p->next_;
	}
	val = pre->data_;
	return true;
}

// 合并两个已排序链表（移动节点到 link1，合并后 link2 为空）
void MergetLink(Clink& link1, Clink& link2)
{
	Node* p = link1.head_->next_;
	Node* q = link2.head_->next_;
	Node* last = link1.head_;
	link2.head_->next_ = nullptr;

	while (p != nullptr && q != nullptr)
	{
		if (p->data_ <= q->data_)
		{
			last->next_ = p;
			p = p->next_;
			last = last->next_;
		}
		else
		{
			last->next_ = q;
			q = q->next_;
			last = last->next_;
		}
	}
	// 接上剩余部分
	if (p != nullptr)
	{
		last->next_ = p;
	}
	else
	{
		last->next_ = q;
	}
}

// 检测链表是否有环并返回环入口节点的值（使用快慢指针）
bool IsLinkHasCircle(Node* head, int& val)
{
	Node* fast = head;
	Node* slow = head;
	while (fast != nullptr && fast->next_ != nullptr)
	{
		slow = slow->next_;
		fast = fast->next_->next_;

		if (slow == fast)
		{
			// 快慢指针相遇，链表存在环
			// 将 fast 置回头部，fast 和 slow 同步以步长 1 前进，
			// 再次相遇的位置即为环的入口节点
			fast = head;
			while (fast != slow)
			{
				slow = slow->next_;
				fast = fast->next_;
			}
			val = slow->data_;
			return true;
		}
	}
	return false;
}
bool IsLinkhasMerge(Node* head1, Node* head2, int &val)
{
	int cnt1 = 0, cnt2 = 0;
	Node* p= head1->next_;
	Node* q = head2->next_;
	while (p != nullptr)
	{
		cnt1++;
		p = p->next_;
	}
	while (q != nullptr)
	{
		cnt2++;
		q = q->next_;
	}
	p = head1;
	q = head2;
	if (cnt1 > cnt2)
		//第一个链表长
	{
		int offset = cnt1 - cnt2;
		while (offset-- > 0)
		{
			p = p->next_;
		}
	}
	else
	{
		//第二个链表长
		int offset= cnt2 - cnt1;
		while (offset-- > 0)
		{
			q = q->next_;
		}	
	}


	while (p != nullptr && q != nullptr)
	{
		if (p == q)
		{
			val = p->data_;
			return true;
		}
		p = p->next_;
		q = q->next_;
	}
	return false;
}
int main()
{
	Node head1;
	Node n1(25), n2(37), n3(52), n4(78), n5(88);
	head1.next_ = &n1;
	n1.next_ = &n2;
	n2.next_ = &n3;
	n3.next_ = &n4;

	Node head2;
	head2.next_ = &n5;

	n5.next_ = &n3; // 形成合并，入口为 n3
	int val;
	if (IsLinkhasMerge(&head1, &head2, val))
	{
		cout<< "链表有合并，合并节点值为: " << val << endl;
	}
	else
	{
		cout << "链表无合并" << endl;
	}
}
#if 0
int main()
{
	// 在栈上构造一段有环的链表用于测试
	Node head;
	Node n1 = (25), n2 = (37), n3 = (52), n4 = (78), n5 = (88);
	head.next_ = &n1;
	n1.next_ = &n2;
	n2.next_ = &n3;
	n3.next_ = &n4;
	n4.next_ = &n2; // 形成环，入口为 n2
	int val;
	if (IsLinkHasCircle(&head, val))
	{
		cout << "链表有环，环入口节点值为: " << val << endl;
	}
	else
	{
		cout << "链表无环" << endl;
	}
}
#endif