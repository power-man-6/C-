#include<iostream>
#include<cmath>
using namespace std;

int arr[] = { 12,6,7,11,16,3,8 };
int total = 0;
int sum = 0;
const int length = sizeof(arr) / sizeof(arr[0]);
int x[length] = { 0 };
int bestx[length] = { 0 };
unsigned int minn = 0XFFFFFFFF;

void fun(int i) {
  if (i == length) {
    int diff = abs(total - 2 * sum);
    if (diff < minn) {
      minn = diff;
      for (int j = 0; j < length; j++)
        bestx[j] = x[j];
    }
    return;
  }

  x[i] = 1;
  sum += arr[i];
  fun(i + 1);
  sum -= arr[i];

  x[i] = 0;
  fun(i + 1);
}

int main() {
  for (int v : arr)
    total += v;

  fun(0);

  cout << "Selected numbers: ";
  for (int i = 0; i < length; i++)
    if (bestx[i] == 1)
      cout << arr[i] << " ";
  cout << endl;

  cout << "Min difference: " << minn << endl;
  return 0;
}
