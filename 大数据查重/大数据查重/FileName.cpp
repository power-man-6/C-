#include<iostream>
using namespace std;
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<cstdlib>
#include<ctime>

int main()
{

	//vector<int>vec;
	//srand(time(NULL));
	//for (int i = 0; i < 10000; i++)
	//{
	//	vec.push_back(rand() % 10000);
	//}

	//unordered_set<int>s1;
	//for (auto key : vec)
	//{
	//	auto it = s1.find(key);
	//	if (it == s1.end())
	//	{
	//		s1.insert(key);
	//	}
	//	else
	//	{
	//		
	//	
	//	}
	//}
	////统计重复数字以及重复次数
	//unordered_map<int,int>m1;
	//for (int key : vec)
	//{
	//	auto it = m1.find(key);
	//	if (it == m1.end())
	//	{
	//		m1.emplace(key, 1);
	//	}
	//	else
	//	{
	//		it->second += 1;
	//	}
	//}
	//for (auto pair : m1)
	//{
	//	if (pair.second > 1)
	//	{
	//		cout << "key" << pair.first << "count:" << pair.second << endl;
	//	}
	//}
	


	//找出第一个没有重复出现的字符
	string str = "jjhfgiyuryytres";
	unordered_map<char, int>m;
	for (char ch : str)
	{
		m[ch]++;
	}
	for (char ch : str)
	{
		if (m[ch] == 1)
			cout << ch << endl;
	}
	return 0;
}
