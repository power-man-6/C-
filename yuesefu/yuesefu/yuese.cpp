//#include<iostream>
//using namespace std;
//
//struct Node {
//	int data;
//	Node* next_;
//	Node(int data) :data(data), next_(nullptr) {};
//};
////约瑟夫环问题
//void josephus(Node* node, int k, int m)
//{
//	if (node == nullptr || k <= 0 || m <= 0) return;
//	Node* tail = node;
//	while (tail->next_ != nullptr)
//	{
//		tail = tail->next_;
//	}
//	tail->next_ = node;
//	Node* prev = tail;
//	Node* curr = node;
//	for (int i = 1; i < k; ++i)
//	{
//		prev = curr;
//		curr = curr->next_;
//	}
//	while (curr->next_ != curr)
//	{
//		for (int count = 1; count < m; ++count)
//		{
//			prev = curr;
//			curr = curr->next_;
//		}
//		//删除节点
//		cout << "删除节点:" << curr->data << endl;
//		prev->next_ = curr->next_;
//		delete curr;
//		curr = prev ->next_;
//	}
//	cout << "最后存活节点:" << curr->data << endl;
//	delete curr;
//}
//int main()
//{
//	int n, k, m;
//	cout << "请输入总人数n,起始位置k,报数间隔m:" << endl;
//	if (!(cin >> n >> k >> m))
//	{
//		cerr << "输入错误\n";
//		return 1;
//	}
//	if (n < 0 || k <= 0 || m <= 0)
//	{
//		cerr << "n,k,m必须为整数\n";
//		return 1;
//	}
//	//构建线性链表1->2->3->...->n
//	Node* head = new Node(1);
//	Node* tail = head;
//	for (int i = 2; i <= n; ++i)
//	{
//		tail->next_ = new Node(i);
//		tail = tail->next_;
//	}
//	josephus(head, k, m);
//	return 0;
//}
#include<iostream>
using namespace std;
struct Node {
	int data;
	Node* next_;
	Node(int data) :data(data), next_(nullptr) {};
};
void josephus (Node* head, int k, int m)
{
	Node* p = head;
	Node* q = head;
	//将q指向链表的尾部
	while (q->next_ != head)
	{
		q=q->next_;
	}
	for (int i = 1; i < k; i++)
	{
		q = p;
		p = p-> next_;
	} 
	while (p->next_ != p)
	{
		for (int j = 1; j < m; j++)
		{
			q = p;
			p = p->next_;
		}
		cout << p->data << " ";
		q->next_ = p->next_;
		delete p;
		p = q->next_;
		if (p == q)
		{
			cout << "最后存活节点:" << p->data << endl;
			delete p;
		}
	}

}
int main()
{
	int n, k, m;
	cout << "请输入总人数n,起始位置k,报数间隔m:" << endl;
	if (!(cin >> n >> k >> m))
	{
		cerr << "输入错误\n";
		return 1;
	}
	if (n < 0 || k <= 0 || m <= 0)
	{
		cerr << "n,k,m必须为整数\n";
		return 1;
	}
	//构建循环链表1->2->3->...->n
	Node* head = new Node(1);
	Node* tail = head;
	for (int i = 2; i <= n; ++i)
	{
		tail->next_ = new Node(i);
		tail = tail->next_;
	}
	tail->next_ = head; //形成循环链表
	josephus(head, k, m);
	return 0;
}