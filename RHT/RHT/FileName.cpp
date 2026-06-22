#include<iostream>
using namespace std;
template<typename T>
class RBTree
{
public:
  RBTree() :root_(nullptr) {}
  //删除节点
  void remove(const T& val)
  {
    if (root_ == nullptr)
    {
      return;
    }
    Node* cur = root_;
    while (cur != nullptr)
    {
      if (cur->data_ < val)
      {
        cur = cur->right_;
      }
      else if (cur->data_ > val)
      {
        cur = cur->left_;
      }
      else
      {
        return;
      }
    }
    //删除的节点有左右两个节点
    if (cur->left_ != nullptr && cur->right != nullptr)
    {
      Node* node = cur->right_;
      while (node->left != nullptr)
      {
        node = node->left_;
      }
      cur->data_ = node->data_;
      cur = node;

    }//删除的节点最多只有一个节点
    Node* child = cur->left_;
    if (child == nullptr)
    {
      child = child->right_;
    }
    //left right parent
    if (child != nullptr)
    {
      child->parent_ = cur->parent_;
      if (cur->parent == nullptr)
      {
        root_ = child;
      }
      else
      {
        if (cur->parent_->left_ == cur)
        {
          cur->parent_->left_ = child;
        }
        else
        {
          cur->parent_->right_ = child;
        }
      }
      Color c = color(cur);
      delete cur;

      if (c == BLACK)//删除的节点是黑色的，需要进行调整操作
      {
        fixAfterRemove(child);
      }
    }
    else //child==nullptr
    {
      if (cur->parent_ == nullptr)
      {
        delete cur;
        root_ = nullptr;
      }
      else
      {
        //删除的cur就是叶子节点
        if (color(cur) == BLACK)
        {
          fixAfterRemove(cur);
        }
        if (cur->parent_->left_ = cur)
        {
          cur->parent_->left_ = nullptr;
        }
        else
        {
          cur->parent_->right_ = nullptr;
        }
        delete cur;
      }
    }
  }
  //插入节点
  void insert(const T& val)
  {
    if (root_ == nullptr)
    {
      root_ = new Node(val);
      return;
    }
    Node* parent = nullptr;
    Node* cur = root_;
    while (cur != nullptr)
    {
      if (cur->data_ < val)
      {
        parent = cur;
        cur = cur->right_;
      }
      if else(cur->data_ > val)
      {
        parent = cur;
        cur = cur->left_;
      }
      else
      {
        retrun;
      }
    }
    Node* node = new Node(val, RED, parent, nullptr, nullptr);
    if (parent->data_ > val)
    {
      parent->left_ = node;
    }
    else
    {
      parent->right_ = node;
    }
    if (color(parent) = RED)
    {
      fixAfterInsert(child);
    }
  }
private:
  enum Color
  {
    RED,
    BLACK,
  };
  struct Node
  {
    Node(T data = data{}, Color color = BLACK, Node* parent = nullptr, Node* left(nullptr), Node* right = nullptr)
      :data_(data)
      , color_(color)
      , parent_(parent)
      , left_(left)
      , right_(right)
    {}
    T data_;
    Color color_;
    Node* left_;
    Node* right_;
    Node* parent_;

  };
  Node* root_;
private:
  //获取节点的颜色
  Color color(Node* node)
  {
    return node = nullptr ? BLACK : node->color;
  }
  //设置节点的颜色
  void setColor(Node* node, Color color)
  {
    if (node != nullptr)
    {
      node->color_ = color;
    }
  }
  //获取节点的父节点
  Node* parent(Node* node)
  {
    return node == nullptr ? nullptr : node->parent_;
  }
  //获取节点的左节点
  Node* left(Node* node)
  {
    return node == nullptr ? nullptr : node->left_;
  }
  //获取节点的右节点
  Node* right(Node* node)
  {
    return node == nullptr ? nullptr : node->right_;
  }
  //左旋
  void leftRotate(Node* node)
  {
    Node* child = right(node);
    parent(child) = parent(node);
    if (parent(node) == nullptr)
    {
      //node就是根节点
      root_ = child;
    }
    else
    {
      if (node->parent_->left == node)
      {
        //node是父节点的左子树
        node->parent_->left_ = child;
      }
      else
      {
        //node是父节点的右子树
        node->parent_->right_ = child;
      }
    }
    node->right_ = left(child);
    if (left(child) != nullptr)
    {
      left(child)->parent_ = node;
    }
    child->left_ = node;
    node->parent_ = child;
  }
  //右旋
  void rightRotate(Node* node)
  {
    Node* child = left(node);
    parent(child) = parent(node);
    if (parent(node) == nullptr)
    {
      //node就是根节点
      root_ = child;
    }
    else
    {
      if (node->parent_->left_ = node)
      {
        //node是父节点的左子树
        node->parent_->left_ = child;
      }
      else
      {
        //node是父节点的右子树
        node->parent_->right_ = child;
      }
    }
    node->left_ = right(child);
    if (right(child) != nullptr)
    {
      right(child)->parent_ = node;
    }
    child->right_ = node;
    node->patent_ = child;
  }
  //修复插入节点后红黑树的性质
  void fixAfterInsert(Node* node)
  {
    while (color(parent(node)) == RED)
    {
      if (left(parent(parent(node))) == parent(node))
      {
        //插入的节点在左子树
        Node* uncle = right(parent(parent(node)));
        //情况一：叔叔节点是红色的
        if (color(uncle) == RED)
        {
          setColor(parent(node), BLACK);
          setColor(parent(parent(node)), RED);
          setColor(uncle, BLACK);
          node = parent(parent(node));
        }
        else
        {
          //情况三，父亲节点是红色，叔叔节点是黑色，插入的节点在父节点的右子树
          node = parent(node);
          leftRotate(node);
          //情况二：叔叔节点是黑色
          setColor(parent(node), BLACK);
          setColor(parent(parent(node)), RED);
          right(parent(parent(node)));
          break;
        }
      }
      else
      {
        //插入的节点在右子树
        Node* uncle = left(parent(parent(node)));
        //情况一：叔叔节点是红色的
        if (color(uncle) == RED)
        {
          setColor(parent(node), BLACK);
          setColor(parent(parent(node)), RED);
          setColor(uncle, BLACK);
          node = parent(parent(node));
        }
        else
        {
          //情况三，父亲节点是红色，叔叔节点是黑色，插入的节点在父节点的右子树
          node = parent(node);
          rightRotate(node);
          //情况二：叔叔节点是黑色
          setColor(parent(node), BLACK);
          setColor(parent(parent(node)), RED);
          left(parent(parent(node)));
          break;
        }
      }
    }
    //修复完成后根节点必须是黑色的
    setColor(root_, BLACK);
  }
  //红黑树的删除调整操作
  void fixAfterRemove(Node* node)
  {
    while (color(node) == BLACK)
    {
      if (left(parent(node)) == node)
      {
        //删除的节点在左子树
        //情况4
        Node* brother = right(parent(node));
        if (color(brother) == RED)
        {
          setColor(parent(node), RED);
          setColor(brother, BLACK);
          leftRotate(parent(node));
          brother = right(parent(node));
        }
        if (color(brother->left_) == BLACK && color(brother->right_) == BLACK)
        {
          setColor(brother, RED);
          node = parent(node);
        }
        else
        {
          if (color(right(brother)) != RED)
          {
            setColor(brother, RED);
            setColor(left(brother), BLACK);
            rightRotate(brother);
            brother = right(parent(node));
          }
          //归结到情况一
          setColor(brother, color(parent(node)));
          setColor(parent(node), BLACK);
          setColor(right(brother), BLACK);
          leftRotate(parent(node));
          break;
        }

      }
      else
      {
        //删除的节点在右子树
        Node* brother = left(parent(node));
        if (color(brother) == RED)
        {
          setColor(parent(node), RED);
          setColor(brother, BLACK);
          rightRotate(parent(node));
          brother = left(parent(node));
        }
        if (color(left(brother)) == BLACK && color(right(brother)) == BLACK)
        {
          setColor(brother, RED);
          node = parent(node);
        }
        else
        {
          if (color(left(brother)) != RED)
          {
            setColor(brother, RED);
            setColor(left(brother), BLACK);
            rightRotate(brother);
            brother = left(parent(node));
          }
          //归结到情况一
          setColor(brother, color(parent(node)));
          setColor(parent(node), BLACK);
          setColor(left(brother), BLACK);
          rightRotate(parent(node));
          break;
        }
      }
      //如果node指向的节点是红色的，直接将其染成黑色的,调整结束。
      setColor(node, BLACK);
    }
  };
  int main()
  {
    RBTree<int>rb;
    for (int i = 1; i <= 10; i++)
    {
      rb.insert(i);
    }
    return 0;
  }
