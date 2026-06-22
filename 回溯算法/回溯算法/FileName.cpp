#include<iostream>
using namespace std;
#include<vector>
//子集数
//void func(int i);
//int arr[]={12,3,4};
//int length = sizeof(arr) / sizeof(int);
//vector<int> path;
//void func(int i)
//{
//  if (length == i)
//  {
//    for (int i = 0; i < path.size(); i++)
//    {
//      cout << path[i] << " ";
//    }
//    cout << endl;
//  }
//  else
//  {
//    path.push_back(arr[i]);
//    func(i + 1);
//    path.pop_back();
//    func(i + 1);
//  }
//} 
//
//int main()
//{
// 
//  func(0);
//  return 0;
//}



//问题：
//  0-1背包问题：有一组物品，其重量分别是w1,w2,w3,...,wn，价值分别是v1,v2,v3,...,vn，
// 在背包容量为C的情况下，// 如何选择物品使得背包内物品的总价值最大？
int w[] = { 2,3,4 };
int v[] = { 1,4,6 };
int length = sizeof(w) / sizeof(int);
int C = 5;
int wc = 0;
int vc = 0;
int maxv = 0;
vector<int> best;
vector<int> path;
void func(int i)
{
  if (i == length)
  {
    if (wc <= C)
    {
      if (vc > maxv)
      {
        maxv = vc;
        best = path;
      }
    }
    return;
  }
  else
  {
    wc += w[i];
    vc += v[i];
    path.push_back(w[i]);
    func(i + 1);
    path.pop_back();
    wc -= w[i];
    vc -= v[i];
    func(i + 1);
  }
}
int main()
{
  func(0);
  cout << "选中的物品重量：";
  for (int x : best) {
    cout << x << " ";
  }
  cout << endl;
  cout << "最大价值 maxv = " << maxv << endl;

  return 0;
}
