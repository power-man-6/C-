#include<iostream>
#include<algorithm>
using namespace std;
//AVL树是一种自平衡二叉搜索树，它在插入和删除节点时会自动调整树的结构，以保持树的平衡。AVL树的每个节点都包含一个平衡因子（Balance Factor），表示该节点的左子树高度与右子树高度之差。AVL树的平衡因子只能是-1、0或1，如果某个节点的平衡因子超过了这个范围，就需要进行旋转操作来恢复平衡。
template<typename T>
class AVLTree
{
public:
	AVLTree(): root_(nullptr)
	{}
	//AVL树的插入操作
	void insert(const T& val)
	{
		root_ = insert(root_, val);
	}
private:
		//定义AVL树节点
	struct Node {
		Node(T data = T())
			: data_(data)
			,left_(nullptr)
			, right_(nullptr)
			, height(1)
		{}
		T data_; //节点数据
		Node* left_; //左子树指针
		Node* right_; //右子树指针
		int height; //节点高度
		};
	//节点的高度值
	int height(Node* node)
	{
		return node == nullptr ? 0 : node->height;
	}
	//右旋转操作 以参数node为轴做右旋操作，并把新的根节点返回
	Node* rightRotate(Node* node)
	{
		//节点旋转
		Node* child = node->left_;
		node->left_ = child->right_;
		child->right_ = node;
		//更新节点高度  node  child
		node->height = max(height(node->left_), height(node->right_)) + 1;
		child->height = max(height(child->left_), height(child->right_)) + 1;
		//返回旋转后的子树新的根节点
		return child;
	}
	//左旋转操作 以参数node为轴做左旋转操作，并把新的根节点返回
	Node* leftRotate(Node* node)
	{
		//节点旋转
		Node* child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;
		//更新节点高度  node  child
		node->height = max(height(node->left_), height(node->right_)) + 1;
		child->height = max(height(child->left_), height(child->right_)) + 1;
		//返回旋转后的子树新的根节点
		return child;
	}
	//左平衡操作
	Node* leftBalance(Node* node)
	{
		node->left_ = leftRotate(node->left_);
		return rightRotate(node); 
	}
	//右平衡操作
	Node* rightBalance(Node* node)
	{
		node->right_ = rightRotate(node->right_);
		return leftRotate(node);
	}

	Node* insert(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return new Node(val);
		}
		if (node->data_ > val)
		{

			node->left_ = insert(node->left_, val);
			//在递归回溯时判断节点是否失衡，如果失衡了就进行旋转操作
			if (height(node->left_) - height(node->right_) > 1)
			{
				if (height(node->left_->left_) >= height(node->left_->right_))
				{
					node =rightRotate(node);
				}
				else
				{
					node =leftBalance(node);
				}
			}
		}
		else if (node->data_ < val)
		{
			node->right_ = insert(node->right_, val);
			//
			if (height(node->right_) - height(node->left_) > 1)
			{
				if (height(node->right_->right_) >= height(node->right_->left_))
				{
					node = leftRotate(node);
				}
				else
				{
					node = rightBalance(node);
				}
			}
		}
		else
		{
			;//找到相同节点了，不用再往下递归了，直接向上回溯
		}
		//添加3 因为子树中增加了一个节点，所以父节点的高度要增加1
		node->height = max(height(node->left_), height(node->right_)) + 1;
		return node;

	}
	Node* root_; //AVL树的根节点
};


int main()
{	
	AVLTree<int>avl;
	for (int i = 0; i < 11; i++)
	{
		avl.insert(i);
	}
	return 0;
}