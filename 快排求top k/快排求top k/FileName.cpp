#include<iostream>
using namespace std;

// 快排分区函数（适配找最小topk）
int Partation(int arr[], int begin, int end)
{
    int val = arr[begin];  // 选基准值（区间第一个元素）
    int i = begin;
    int j = end;

    while (i < j)
    {
        // 1. 从右往左找：比基准值小的数（关键修改：val > arr[j]）
        while (i < j && val < arr[j])
            j--;
        if (i < j)
        {
            arr[i] = arr[j];  // 把小数移到左指针位置
            i++;
        }

        // 2. 从左往右找：比基准值大的数（关键修改：val < arr[i]）
        while (i < j && val > arr[i])
            i++;
        if (i < j)
        {
            arr[j] = arr[i];  // 把大数移到右指针位置
            j--;
        }
    }
    arr[i] = val;  // 基准值归位（此时i=j，是基准值的正确位置）
    return i;      // 返回基准值的索引
}

// 求最小的前k个数（基于快排分区的TopK算法）
void SelectTopk(int arr[], int begin, int end, int k)
{
    int pos = Partation(arr, begin, end);  // 分区，得到基准值的位置

    if (pos == k - 1)
    {
        // 基准值刚好是第k小的数（索引k-1），左侧就是最小的前k个数，直接返回
        return;
    }
    else if (pos > k - 1)
    {
        // 基准值位置偏右，说明第k小数在左区间，递归处理左区间
        SelectTopk(arr, begin, pos - 1, k);
    }
    else
    {
        // 基准值位置偏左，说明第k小数在右区间，递归处理右区间
        SelectTopk(arr, pos + 1, end, k);
    }
}

int main()
{
    int arr[] = { 64,45,62,80,66,0,2,18,75 ,4};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 3;  // 找最小的前3个数

    SelectTopk(arr, 0, size - 1, k);

    // 输出最小的前k个数
    cout << "最小的前" << k << "个数：";
    for (int i = 0; i < k; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}