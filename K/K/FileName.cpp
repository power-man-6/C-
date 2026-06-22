#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct ListNode {
  int val;
  ListNode* node;
  ListNode(int x) :val(x), node(nullptr) {}
};
ListNode* init_link(initializer_list<int>list) {
  ListNode* head = nullptr;
  ListNode* p = nullptr;
  for (int v : list) {
    if (head == nullptr)
    {
      head = new ListNode(v);
      p = head;
    }
    else
    {
      p->node = new ListNode(v);
      p = p->node;
    }
  }
  return head;
}
ListNode* mergeTwoLink(ListNode* p1, ListNode* p2)
{
  ListNode* head = nullptr;
  if(p1==nullptr)
    return p2;
  if (p2 == nullptr)
    return p1;
  if (p1->val > p2->val)
  {
    head = p2;
    p2 = p2->node;
  }
  else
  {
    head = p1;
    p1 = p1->node;
  }
  ListNode* p = head;
  while (p1 != nullptr && p2 != nullptr)
  {
    if(p1->val > p2->val)
      {
      p->node = p2;
      p = p2;
      p2 = p2->node;
    }
    else
    {
      p->node = p1;
      p = p1;
      p1 = p1->node;
    }
  }
  if (p2 != nullptr)
  {
    p->node = p1;
  }
  if (p1 != nullptr)
  {
    p->node = p2;
  }
  return head;
}
ListNode* mergeLink(vector<ListNode*>& vlink, int i, int j)
{
  if (i >= j)
  {
    return vlink[i];
  }
  int mid = (i + j) / 2;
  ListNode* left = mergeLink(vlink, i, mid);
  ListNode* right = mergeLink(vlink, mid + 1, j);
  return mergeTwoLink(left, right);
}
int main()
{
  vector<ListNode*> vlink;
  vlink.push_back(init_link({4,5 }));
  vlink.push_back(init_link({ 1,3,4 }));
  vlink.push_back(init_link({ 2, }));
  ListNode* head = mergeLink(vlink, 0, vlink.size() - 1);
  for (ListNode* c = head; c != nullptr; c = c->node)
  {
    cout << c->val << " ";
  }
  cout << endl;

  return 0;
}

