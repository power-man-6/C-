#include<iostream>
using namespace std;
#include<vector>
//one-dimensional array
int arr[] = { 1,2,3 };
int length = sizeof(arr) / sizeof(arr[0]);
bool state[] = {0};
vector<int>path;
void swap(int arr[], int i, int j)
{
  int temp= arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}
void func01(int i)
{
  if (i == length)
  {
    for (int j = 0; j < length; ++j)
    {
      cout << arr[j] << " ";
    }
    cout << endl;
  }
  else
  {
    for (int k = i; k < length; ++k)
    {
      swap(arr, i, k);
      func01(i + 1);
      swap(arr, i, k);
    }
  }
}
void func02(int i)
{
  if (i == length)
  {
    for (int j = 0; j < length; ++j)
    {
      cout << path[j] << " ";
    }
    cout << endl;
  }
  else
 {
    for (int k = 0; k < length; ++k)
    {
      if (!state[k])
      {
        path.push_back(arr[k]);
        state[k] = 1;
        func02(i + 1);
        path.pop_back();
        state[k] = 0;
      }
    }
 }
}
int main()
{
  func01(0);
  cout << "===============================" << endl;
  func02(0);
  return 0;
}
