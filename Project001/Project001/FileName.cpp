#include <iostream>
#include <vector>
#include <chrono>  // 用于计时

using namespace std;
using namespace chrono;

// ----------------- 1. 冒泡排序 -----------------
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;  // 优化：提前结束
    }
}

// ----------------- 2. 选择排序 -----------------
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// ----------------- 3. 快速排序 -----------------
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSortWrapper(vector<int>& arr) {
    if (!arr.empty()) {
        quickSort(arr, 0, arr.size() - 1);
    }
}

// ----------------- 辅助函数 -----------------
void printArray(const vector<int>& arr, const string& title) {
    cout << title << " (共" << arr.size() << "个元素): ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

// 计时执行排序
template<typename Func>
long long measureTime(Func sortFunc, vector<int> arr, const string& name) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << name << " 执行时间: " << duration.count() << " 微秒" << endl;
    return duration.count();
}

int main() {
    // 原始测试数据
    vector<int> original = { 64, 34, 25, 12, 22, 11, 90, 5, 77, 30 };

    cout << "========== 排序算法实验报告 ==========" << endl;
    cout << "原始序列: ";
    for (int val : original) cout << val << " ";
    cout << "\n" << endl;

    // 1. 冒泡排序
    vector<int> arr1 = original;
    bubbleSort(arr1);
    printArray(arr1, "冒泡排序结果");

    // 2. 选择排序
    vector<int> arr2 = original;
    selectionSort(arr2);
    printArray(arr2, "选择排序结果");

    // 3. 快速排序
    vector<int> arr3 = original;
    quickSortWrapper(arr3);
    printArray(arr3, "快速排序结果");

    // 验证三种排序结果一致
    if (arr1 == arr2 && arr2 == arr3) {
        cout << "\n✅ 验证通过：三种排序结果一致！" << endl;
    }

    // 性能测试（可选）
    cout << "\n========== 性能对比 ==========" << endl;
    vector<int> largeData = { 64, 34, 25, 12, 22, 11, 90, 5, 77, 30, 88, 42, 19, 73, 8, 61, 54, 33, 47, 99 };

    measureTime([](vector<int> v) { bubbleSort(v); }, largeData, "冒泡排序");
    measureTime([](vector<int> v) { selectionSort(v); }, largeData, "选择排序");
    measureTime([](vector<int> v) { quickSortWrapper(v); }, largeData, "快速排序");

    return 0;
}