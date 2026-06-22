#include<iostream>
#include<algorithm>
using namespace std;
//AVL类
template<typename T>
class AVLTree
{
public:
	//构造函数
	AVLTree() :root_(nullptr)
	{}
	//插入函数
	void insert(const T &val)
	{
		root_=insert(root_, val);
	}
	//删除节点函数
	void remove(const T& val)
	{
		root_ = remove(root_, val);
	}
private:
	//AVLtree节点构建
	struct Node {
		T data_;//数据段
		Node* left_;//左节点
		Node* right_;//右节点
		int height;//节点高度
		Node(T data=T()) :
			data_(data)
			, left_(nullptr)
			, right_(nullptr)
			, height(1)
		{}
	};
	Node* root_;//根节点
private:
	int height(Node* node)
	{	
		return node == nullptr ? 0 : node->height;
	}
	// 左旋转操作  01  LL
	Node* leftRotate(Node* node)
	{
		//旋转操作
		Node*child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;
		//更新高度
		node->height = max(height(node->left_),height(node->right_)) + 1;
		child->height = max(height(child->left_), height(child->right_)) + 1;
		//返回孩子节点
		return child;
	}
	//右旋转操作   02 RR
	Node* rightRotate(Node* node)
	{
		//旋转操作
		Node* child = node->left_;
		node->left_ = child->right_;
		child->right_ = node;
		//更新高度
		node->height = max(height(node->left_), height(node->right_)) + 1;
		child->height = max(height(child->left_), height(child->right_)) + 1;
		//返回孩子节点
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
	Node* insert(Node* node, T val)
	{
		if (node == nullptr)
		{
			return new Node(val);
		}
		else if (node->data_ >val)
		{
			node->left_=insert(node->left_, val);
			
			if (height(node->left_) - height(node->right_) > 1)
			{
				if (height(node->left_->left_) > height(node->left_->right_))//LL
				{
					node = rightRotate(node);
				}
				else//LR
				{
					node = leftBalance(node);
				}
			}
		}
		else if(node->data_<val)
		{
			node->right_ = insert(node->right_, val);
			if (height(node->right_) - height(node->left_) > 1)
			{
				if (height(node->right_->right_) > height(node->right_->left_))//RR
				{
					node = leftRotate(node);
				}
				else//RL
				{
					node = rightBalance(node);
				}
			}
		}
		else
		{
			;
		}
		node->height = max(height(node->left_), height(node->right_)) + 1;
		return node;
	}
	Node* remove(Node* node, const T& val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->data_ > val)
		{
			node->left_ = remove(node->left_, val);
			//左子树删除后可能引起右子树过高
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
		else if (node->data_ < val)
		{
			node->right_ = remove(node->right_, val);
			//右子树删除后可能引起左子树过高
			if (height(node->left_) - height(node->right_) > 1)
			{
				if (height(node->left_->left_) > height(node->left_->right_))
				{
					node= rightRotate(node);
				}
				else
				{
					node = leftBalance(node);
				}
			}
		}
		else
		{
			//找到了先处理情况三
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				//为避免删除前驱或者后继节点时引起的平衡问题，谁高删谁
				if (height(node->left_) >=height(node->right_))
				{
					//删前驱
					Node* pre = node->left_;
					while (pre->right_!= nullptr)
					{
						pre = pre->right_;
					}
					node->data_ = pre->data_;
					node->left_ = remove(node->left_,pre->data_);

				}
				else
				{
					//删后继
					Node* post = node->right_;
					while (post->left_ != nullptr)
					{
						post = post->left_;
					}
					node->data_ = post->data_;
					node->right_ = remove(node->right_, post->data_);
				}
			}
			else//删除节点只有一个子树或者没有子树
			{
				if (node->left_ != nullptr)
				{
					Node* left = node->left_;
					delete node;
					return left;
				}
				else if (node->right_ != nullptr)
				{
					Node* right = node->right_;
					delete node;
					return right;
				}
				else
				{
					delete node;
					return nullptr;
				}
			}
		}
		node->height = max(height(node->left_), height(node->right_)) + 1;
		return node;//递归回溯过程
	}
};
int main()
{	
	AVLTree <int>val;
	for (int i = 1; i <=10; i++)
	{
		val.insert(i);
	}
	val.remove(9);
	val.remove(10);
	return 0;
}