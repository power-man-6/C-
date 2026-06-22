#include<iostream>
using namespace std;
//int num = 0;
//void swap(int arr[],int i,int j)
//{
//  int temp = arr[i];
//  arr[i] = arr[j];
//  arr[j] = temp;
//}
//void func(int arr[],int i,int length)
//{
//  if(i==length)
//  {
//    num++;
//    for (int j = 0; j < length; j++)
//    {
//      cout << arr[j] << " ";
//    }
//    cout << endl;
//  }
//  else
//  {
//    for (int k = i; k < length; k++)
//   {
//      swap(arr, i, k);
//      func(arr, i + 1, length);
//      swap(arr, i, k);
//   }
//  }
//}
//int main()
//{
//  int arr[] = { 1,2,3,4 };
//  int length = sizeof(arr) / sizeof(arr[0]);
//  func(arr, 0, length);
//  cout << "Total permutations: " << num << endl;
//  return 0;
//}

/*
"八皇后问题":国际象棋棋盘上放置八个皇后，使得它们不能互相攻击。
即任意两个皇后都不能处于同一行、同一列或同一斜线上。
求解这个问题的算法可以使用回溯法来实现。
*/
int num = 0;
void swap(int arr[], int i, int j)
{
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j]=temp;
}
bool judge(int arr[], int i)
{
  for (int j = 0; j < i; ++j)
  {
    if (i == j || arr[i] == arr[j] || abs(i - j) == abs(arr[i] - arr[j]))
    {
      return false;
    }
  }
  return true;
}
void func(int arr[], int i, int length)
{
  if (i == length)
  {
    num++;
    for (int j = 0; j < length; j++)
    {
      cout << arr[j] << " ";
    }
    cout << endl;
  }
  else
  {
    for (int k = i; k < length; k++)
    {
      swap(arr, i, k);
      if(judge(arr,i))
         func(arr, i + 1, length);
      swap(arr, i, k);
    }
  }
}
int main()
{
  int arr[] = { 1,2,3,4,5,6,7,8 };
  int length = sizeof(arr) / sizeof(arr[0]);
  func(arr, 0, length);
  cout << "Total arrangements: " << num << endl;
}
