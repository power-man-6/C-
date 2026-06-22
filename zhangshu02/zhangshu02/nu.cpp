#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int arr[] = { 12,6,7,11,16,3,8,4 };
const int length = sizeof(arr) / sizeof(arr[0]);
vector<int> v1;
vector<int> best;
int num = 0;
int nnum = 0;
int minn = 0x7fffffff;
int cnt = 0;
int leftc=length;
void func(int i)
{
  if (i == length)
  {
    cnt++;
    if (v1.size() != length / 2)
    {
      return;
    }
    int result = abs(num - nnum);
    if (result < minn)
    {
      minn = result;
      best = v1;
    }
    return;
  }
  else
  {
    leftc--;
    if (v1.size() < length / 2)
    {  num += arr[i];
    nnum -= arr[i];
    v1.push_back(arr[i]);
    func(i + 1);

    num -= arr[i];
    nnum += arr[i];
    v1.pop_back();
    }
    if (v1.size() + leftc >= length / 2)
    {
       func(i + 1);
    }
    leftc++;
  }
 
}

int main()
{
  for (int i = 0; i < length; i++)
  {
    nnum += arr[i];
  }
  func(0);

  for (int i = 0; i < best.size(); i++)
  {
    cout << best[i] << " ";
  }
  cout << endl;
  cout << minn << endl;
  cout << cnt;
  return 0;
}

//int arr[] = { 12,6,7,11,16,3,8 };
//const int length = sizeof(arr) / sizeof(arr[0]);
//int num = 0;
//int nnum = 0;
//vector<int> v1;
//vector<int> v2;
//int minn = 0x7fffffff;
//
//void func(int i)
//{
//  if (i == length)
//  {
//    int result = abs(num - nnum);
//    if (result < minn)
//    {
//      minn = result;
//      v2 = v1;
//    }
//    return;
//  }
//  else
//  {
//    nnum -= arr[i];
//    num += arr[i];
//    v1.push_back(arr[i]);
//    func(i + 1);
//    num -= arr[i];
//    nnum += arr[i];
//    v1.pop_back();
//    func(i + 1);
//  }
//}
//
//int main()
//{
//  for (int i = 0; i < length; i++)
//  {
//    nnum += arr[i];
//  }
//  func(0);
//  for (int i = 0; i < v2.size(); i++)
//  {
//    cout << v2[i] << " ";
//  }
//  cout << endl;
//  cout << minn;
//  return 0;
//}
