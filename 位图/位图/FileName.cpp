//有两个文件分别是a和b，里面放了许多ip地址（url地址，email地址），让你找出两个文件重复的ip地址

#include<iostream>
using namespace std;

#include<ctime>
#include<cstdlib>
#include<vector>
#include<memory>
int main()
{
	vector<int>vec{ 12,78,123,8,9,9};
	//定义位图数组
	int max = vec[0];
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] > max)
		{
			max = vec[i];
		}
	}
	int* bitmap = new int[max / 32 + 1]();
	unique_ptr<int[]>ptr(bitmap);
	//找到第一个重复的数字
	for (auto key : vec)
	{
		int index = key / 32;
		int offset = key % 32;
		//取key对应的位图值
		if (0 == (bitmap[index] & (1 << offset)))
		{
			//没有出现过
			bitmap[index] |= (1 << offset);
		}
		else
		{
			cout << "第一个重复的数字是：" << key << endl;
			break;
		}
	}
	return 0;
}