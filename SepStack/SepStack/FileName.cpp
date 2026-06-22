#include<iostream>
#include<stack>
#include<string>
using namespace std;
//中缀转后缀表达式
//比较符号的优先级
bool Priority(char ch, char topch)
{
	if ((ch == '*' || ch == '/') && (topch == '+' || topch == '-'))
		return true;
	if (topch == '('&& ch != ')')
		return true;
	return false;
}
string MiddleToEndExpr(string expr)
{
	string result;
	stack<char>s;
	for (char ch : expr)
	{
		if (ch >= '0' && ch <= '9')
		{
			result.push_back(ch);
		}
		else
		{
			for (;;)
			{
				if (s.empty() || ch == '(')
				{
					s.push(ch);
					break;
				}
			//比较当前符号和栈顶符号的优先级
				char topch = s.top();
				//Priority函数返回 ch>topch true 
				if (Priority(ch, topch))
				{
					s.push(ch);
					break;
				}
				else
				{
					s.push(ch);
					if (topch == '(')
						break;
					result.push_back(topch);
				}
			}
		}
	}
	while (!s.empty())
	{
		result.push_back(s.top());
		s.pop();
	}
	return result;
}
int main()
{
	cout << MiddleToEndExpr("(1 + 2) * (3 + 4)") << endl;
	cout << MiddleToEndExpr("2+(4+6)/2+6/3") << endl;
	cout << MiddleToEndExpr("2+6/(4-2)+(4+6/2)") << endl;
}

//链式栈

//class LinkStack
//{
//public:
//	LinkStack() 
//	{
//		 head_ = new Node()
//			 , size_ = 0;
//		 
//	}
//	~LinkStack()
//	{
//		Node* p = head_;
//		while (p != nullptr)
//		{
//			head_ = head_->next_;
//			delete p;
//			p = head_;
//		}
//	}
//public:
//	//入栈
//	void push(int val)
//	{
//		Node* node = new Node(val);
//		node->next_ = head_->next_;
//		head_->next_ = node;
//		size_++;
//	}
//	//出栈
//	void pop()
//	{
//		if (head_->next_ == nullptr)
//			throw "Stack is empty!";
//		Node* p = head_->next_;
//		head_->next_ = p->next_;
//		delete p;
//		size_--;
//	}
//	//获取栈顶元素
//	int top()const
//	{
//		if (head_->next_ == nullptr)
//			throw "Stack is empty!";
//		return head_->next_->data_;
//	}
//	//栈空
//	bool empty()const
//	{
//		return head_->next_ == nullptr;
//	}
//	int size() const
//	{
//		return size_;
//	}
//private:
//	struct Node {
//		int data_;
//		Node* next_;
//		Node(int data = 0)
//			:data_(data)
//			, next_(nullptr) {
//		}
//		
//	};
//    Node* head_;
//	int size_;
//};
//
//int main()
//{
//	int arr[] = { 12,4,56,7,89,31,54,75 };
//	LinkStack s;
//	for (int v : arr)
//	{
//		s.push(v);
//	}
//	
//	cout << s.size()<<endl;
//	while (!s.empty())
//	{
//		cout << s.top() << " ";
//		s.pop();
//	}
//	cout << endl;
//	cout << s.size();
//	cout << endl;
//	return 0;
//}

//class SepStack
//{
//public:
//	SepStack(int size = 10)
//		:mtop(0)
//		, mcap(size)
//	{
//		mpStack = new int[mcap];
//	}
//	~SepStack()
//	{
//		delete[]mpStack;
//		mpStack = nullptr;
//	}
//public:
//	//入栈
//	void push(int val)
//	{
//		//判断是否栈满
//		if (mtop == mcap)
//		{
//			//栈扩容
//			expand(2 * mcap);
//		}
//		mpStack[mtop++] = val;
//	}
//	//出栈
//	void pop()
//	{
//		if (mtop == 0)
//			throw "Stack is empty!";
//		mtop--;
//	}
//	//获取栈顶元素、
//	int top()const
//	{
//		if (mtop == 0)
//			throw "Stack is empty!";
//		return mpStack[mtop - 1];
//	}
//	//栈空
//	bool empty()const
//	{
//		return mtop == 0;
//	}
//	int size()const
//	{
//		return mtop;
//	}
//private:
//	void expand(int size)
//	{
//		int* p = new int(size);
//		memcpy(p, mpStack, mtop * sizeof(int));
//		delete[]mpStack;
//		mpStack = p;
//		mcap = size;
//	}
//	int* mpStack;
//	int mtop;//栈头
//	int mcap;//栈空间大小
//};