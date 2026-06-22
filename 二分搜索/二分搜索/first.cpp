#include<iostream>
using namespace std;

int binarysearch(int arr[], int i, int j, int val)
{
	if (i >j)
	{
		return -1;
	}
	int mid = (i + j) / 2;
	if (arr[mid] == val)
	{
		return mid;
	}
	else if (arr[mid] < val)
	{
		return binarysearch(arr, mid + 1, j, val);
	}
	else 
	{
		return binarysearch(arr, i, mid - 1, val);
	}



}
//int Erfen(int arr[],int size,int val)
//{
//	int first = 0; 
//	int last = size - 1;
//	while (first <= last)
//	{
//		int mid = (first + last) / 2;
//		if (val ==arr[mid])
//		{
//			return mid;
//		}
//		else if (val < arr[mid])
//		{
//			last = mid - 1;
//		}
//		else
//		{
//			first = mid + 1;
//		}
//		
//	}
//	return -1; // Element not found
//}
int main()
{
	int arr[] = { 1,3,45,67,89,90,99 };
	int size = sizeof(arr) / sizeof(arr[0]);
	int val = 45;
	int result = binarysearch(arr,0, size, val);
	int vall = 2;
	int resuylt = binarysearch(arr,0, size, vall);
	cout << "Element found at index " << result << endl;
	cout << "Element found at index: " << resuylt << endl;
}