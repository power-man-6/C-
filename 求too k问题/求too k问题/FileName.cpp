#include<iostream>
#include<vector>
#include<queue>
#include<ctime>
#include<functional>
#include<unordered_map>
#if 0
int main()
{
	std::vector<int>vec;
	srand(time(NULL));
	for (int i = 0; i < 1000; i++)
	{
		vec.push_back(rand() % 10000);
	}
	//求vec中值最小的元素
	std::priority_queue<int,std::vector<int>,std::greater<int>>maxheap;
	int k = 5;
	//由前k个元素构建一个大根堆
	for (int i = 0; i < 5; i++)
	{
		maxheap.push(vec[i]);
		
}
	for (int i = 5; i < vec.size(); i++)
		{
			if (maxheap.top() < vec[i])
			{
				maxheap.pop();
				maxheap.push(vec[i]);
			}
		}
		//输出
	while (!maxheap.empty())
	{
		std::cout << maxheap.top() << " ";
		maxheap.pop();
	}
	std::cout << std::endl;
}
#endif
int main()
{
	std::vector<int>vec;
	srand(time(NULL));
	for (int i = 0; i < 10000; i++)
	{
		vec.push_back(rand() % 10000);
	}
	//统计重复次数最小的元素
	std::unordered_map<int, int>map;
	for (auto key : vec)
	{
		map[key]++;
	}
	//放入大根堆的时候放入key和value
	int k = 3;
	using Type = std::pair<int, int>;
	using Comp = std:: function<bool(Type&, Type&)>;
	std::priority_queue<Type, std::vector<Type>, Comp>maxheap(
		[](Type& a, Type& b)->bool
		{
			return a.second > b.second;
		});
	auto it = map.begin();
	for (int i = 0; i < k; i++,it++)
	{
		maxheap.push(*it);
	}
	for (; it != map.end(); ++it)
	{
		if (maxheap.top().second <it->second)
		{
			maxheap.pop();
			maxheap.push(*it);
		}
	}
	while (!maxheap.empty())
	{
		std::cout << maxheap.top().first << " " << maxheap.top().second << std::endl;
		maxheap.pop();
	}
}