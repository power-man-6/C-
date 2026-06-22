#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
//问题描述：
//给定两个长度为n的有序数组，求这两个数组的中位数
double middleValue(vector<int>&v1,int length1,vector<int>&v2,int length2)
{
	if (length1 > length2)
	{
		return middleValue(v2,length2,v1,length1);
	}
	int i = 0, j = 0;
	int begin = 0, end = length1;
	int k = (length1 + length2+1) / 2;
	
	while (begin<=end)//二分搜索的算法思想，对数时间找到i+j=k
	{
		i = (begin + end) / 2;
		j = k - i;
		if (i>0&&j<length2&&v1[i - 1] > v2[j]) {
			end = i - 1;
		}
		else if (j > 0 && i<length1 && v2[j - 1]>v1[i])
		{
			begin = i + 1;
		}
		else {
			break;
		}
		
	}
	//v1特别短或者v2特别短，导致i=0或者j=0的情况
	int left = 0, right = 0;
	if (i == 0)
	{
		left = v2[j - 1];
	}
	else if (j == 0)
	{
		left =v1[i - 1];
	}
	else
	{
		left = std::max(v1[i - 1], v2[j - 1]);
	}
	
	if (i == length1)
	{
		right = v2[j];
	}
	else if (j == length2)
	{
		right = v1[i];
	}
	else
	{
		right = std::min(v1[i], v2[j]);
	}
	//找到了合适的i和j
	if ((length1 + length2) % 2 == 0)
	{
		return (left + right) / 2.0;
	}
	else
	{
		return left;
	}
	
}
int main()
{
	vector<int>v1;
	vector<int>v2;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(rand() % 101);
	}
	for (int i = 0; i < 10; i++)
	{
		v2.push_back(rand() % 101);
	}
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	for (int i = 0; i < 10; i++)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << v2[i] << " ";
	}
	cout << endl;
	double midval = middleValue(v1, v1.size(), v2, v2.size());
	cout << "中位数为：" << midval << endl;
	return 0;
}