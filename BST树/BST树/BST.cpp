#include<iostream>
#include<functional>
using namespace std;
#include<stack>
template <typename T, typename Compare = less<T>>
class BSTree
{
public:
	BSTree() :root_(nullptr) {};
	~BSTree() {};
	
	//非递归删除
	void n_remove(const T& val)
	{
		//查找val
		if (root_ ==nullptr)
			return;
		Node* parent = nullptr;
		Node* cur =root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				break;
			}
			
			else if(com_(cur->data_,val))
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				parent = cur;
				cur = cur->left_;
			}
		}
		if (cur == nullptr)
		{
			return;
		}
		//情况三
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			parent = cur;
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				parent = pre;
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre;//让cur指向前驱节点，转换成情况1，2
		}

		//cur指向删除节点，parent指向其父节点，统一处理1，2
		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}
		if (parent == nullptr)
		{
			root_ = child;
		}
		else
		{
			if (parent->left_ == cur)
			{
				parent->left_ = child;
			}
			else
			{
				parent->right_ = child;
			}
		}
		delete cur;
	}
	void n_insert(const T &val)
	{
		if (root_ == nullptr)
		{
			root_ =  new Node(val);
			return;
		}
		//搜索合适的插入位置,插入父节点
		Node* parent = nullptr;
		Node* cur = root_;

		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				return;
			}
			
			else if (com_(cur->data_, val))
			{
				parent = cur;
				cur=cur->right_;
			}
			else { 
				parent = cur;
				cur = cur->left_;
			}
		}
		//把新节点插入到parent节点的孩子上
		if (com_(val, parent->data_))
		{
			parent->left_ = new Node(val);
		}
		else
		{
			parent->right_ = new Node(val);
		}
	}
	//搜索
	bool n_query(const T& val)
	{
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				return true;
			}
			else if (com_(cur->data_, val))
			{
				cur = cur->right_;
			}
			else
			{
				cur = cur->left_;
			}
		}
		return false;
	}
	void preOrder()
	{
		cout << "[递归]前序遍历:";
		preOrder(root_);
		cout << endl;
	} 
	void inOrder()
	{
		cout << "[递归]中序遍历:";
		inOrder(root_);
		cout << endl;
	}
	void postOrder()
	{
		cout << "[递归]后序遍历:";
		postOrder(root_);
		cout << endl;
	}
	void levelOrder()
	{
		cout << "[递归]层序遍历:";
		int h = high();
		for (int i = 0; i < h; ++i)
		{
			levelOrder(root_, i);
		}
		cout << endl;
	}
	//递归求二叉树层数
	int high()
	{
		return level(root_);
	}
	//递归求二叉树节点个数
	int number()
	{
		return number(root_);
	}
	//求满足区间的元素值[i,j]
	void findValuse(vector<T>& vec, int i, int j)
	{
		findValuse(root_, vec, i, j);
	}
	//非递归前序遍历操作
	//void preOrder()
	//
	//	cout << "[非递归]前序遍历:";
	//	if(roo)
	//	stack<Node*>s;
	//		cout << endl;
	//}
private: 
	//节点定义
	struct Node
	{	
		Node(T data = T{})
			:data_(data)
			, left_(nullptr)
			, right_(nullptr)
		{
		}
		T data_;//数据端
		Node* left_;//左值
		Node* right_;//右值
	};
	//递归前序遍历的实现VLR
	void preOrder(Node* node)
	{
		if (node != nullptr)
		{
			cout << node->data_ << " ";//操作V
			preOrder(node->left_);//L
			preOrder(node->right_);//R
		}
	}
	void inOrder(Node* node)
	{
		if (node != nullptr)
		{
			inOrder(node->left_);//L
			cout << node->data_ << " ";//V
			inOrder(node->right_);//R
		}
	}
	void postOrder(Node* node)
	{
		if (node != nullptr)
		{
			postOrder(node->left_);
			postOrder(node->right_);
			cout << node->data_<<" ";
		}
	}
	//递归实现求二叉树层数，求以node为节点的子树的高度并返回高度值
	int level(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int left = level(node->left_);
		int right = level(node->right_);
		return right > left ? right + 1 : left + 1;
	}
	//递归求二叉树节点个数的实现，求以node为根节点的树的节点总数，并返回
	int number(Node* node)
	{
		if (node == nullptr)
			return 0;
		int left = number(node->left_);
		int right = number(node->right_);
		return left + right + 1;
	}
	//递归层序遍历的实现
	void levelOrder(Node* node, int i)
	{
		if (node == nullptr)
			return;
		if (i == 0)
		{
			cout << node->data_ << " ";
			return;
		}
		levelOrder(node -> left_, i - 1);
		levelOrder(node->right_, i - 1);
	}
	//求满足区间的元素值[i,j]实现
	void findValuse(Node*node,vector<T>& vec, int i, int j)
	{
		if (node != nullptr)
		{
			if (node->data_ > i)
			{
				findValuse(node->left_, vec, i, j);//L
			}
			
			if (node->data_ >= i && node->data_ <= j)
			{
				vec.push_back(node->data_);//存储满足区间元素的值
			}
			if (node->data_ < j)
			{
				findValuse(node->right_, vec, i, j);//R
			}
			
		} 
	}
	Node* root_;//指向BT树的根节点
	Compare com_;//定义一个函数对象
};
int main()
{
	int arr[] = { 58,24,67,0,34,62,34,62,69,5,41,64,78 };
	BSTree<int>bst;
	for (int v : arr)
	{
		bst.n_insert(v);
	}
	bst.n_insert(12);
	//cout << bst.n_query(12) << endl;
	//bst.n_remove(12);
	//cout<<bst.n_query(12)<<endl;
	bst.preOrder();
	bst.inOrder();
	bst.postOrder();
	bst.levelOrder();
	cout << bst.high() << endl;
	cout << bst.number() << endl;
	vector<int>vec;
	bst.findValuse(vec, 10, 60);
	for (int v : vec)
	{
		cout << v << " ";
	}
	return 0;
}