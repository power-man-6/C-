//快排
#include<iostream>
using namespace std;
//处理基准数的函数
int partition(int arr[], int i, int j)
{
  int pivot = arr[i];  // 选择第一个元素作为基准
  int l = i, r = j;

  while (l < r)
  {
    // 从右向左找第一个小于 pivot 的元素
    while (l < r && arr[r] >= pivot)
      r--;
    if (l < r)
      arr[l++] = arr[r];

    // 从左向右找第一个大于 pivot 的元素
    while (l < r && arr[l] <= pivot)
      l++;
    if (l < r)
      arr[r--] = arr[l];
  }
  arr[l] = pivot;
  return l;
}
void quickSort(int arr[], int l, int r)
{
  if (l >= r)
  {
    return;
  }
  int pos = partition(arr, l, r);
  quickSort(arr, l, pos - 1);
  quickSort(arr, pos + 1, r);

}
int main()
{
  srand(time(NULL));
  int arr[10];
  for (int i = 0; i < 10; i++)
  {
    arr[i] = rand() % 101;
  }
  for (int i = 0; i < 10; i++)
  {
    cout << arr[i] << " ";
  }
  cout << endl;
  quickSort(arr, 0, 9);
  for (int i = 0; i < 10; i++)
  {
    cout << arr[i] << " ";
  }
  return 0;
}
