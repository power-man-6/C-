#include<iostream>
using namespace std;
#include<vector>
#include<cmath>
/*
整数问题：给定一个数组2n个整数，要求将这些整数分成两组，每组n个，使得两组整数的和的差的绝对值最小。输出这个最小的差值和对应的数组。
*/
//#if 0
//int arr[] = { 12,3,45,67,7,6 };
//int length = sizeof(arr) / sizeof(arr[0]);
//int num = 0;
//int x[6] = {0};
//void func(int arr[], int i,int length,int x[])
//{
//  if (i == length)
//  {
//    num++;
//      for (int j =0; j < length; j++)
//    {
//        if (x[j  ] == 1)
//        {
//            cout << arr[j] << " ";
//        }
//      
//    }
//    cout << endl;
//   
//  }
//  else
//  {
//    x[i] = 1;
//    func(arr, i + 1, length,x);
//    x[i] = 0;
//    func(arr, i + 1, length,x);
//  }
//}
//int main()
//{
//  func(arr, 0, length,x);
//  cout << num;
//  return 0;
//}
//#endif

int arr[] = { 23,45,6,7,44,3,2 };
int length = sizeof(arr) / sizeof(arr[0]);
int num = 0;//计算已选的整数和
int nnum = 0;//计算未选的整数和
vector <int> v1;//存贮已选的整数
vector<int>v2;//存贮未选的整数
int minn = 0x7fffffff;
void func(int i)
{
  if (i == length)
  {
    int result = abs(num - nnum);
    if (result < minn)
    {
      minn = result;
      v2 = v1;
    }
    return;
  }
  else
  {
    nnum -= arr[i];
    num += arr[i];
    v1.push_back(arr[i]);
    func(i + 1);
    num -= arr[i];
    nnum += arr[i];
    v1.pop_back();
    func(i + 1);

  }
}
int main()
{
  for (int i = 0; i < length; i++)
  {
    nnum += arr[i];
  }
  func(0);
  for (int i = 0; i < v2.size(); i++)
  {
    cout << v2[i] << " ";
  }
  return 0;
}
