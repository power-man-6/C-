#include"consistent_hash.h"
#include<iostream>
#include<iomanip>
#include<map>
#include<random>
#include<chrono>
//简单的性能测试
void performanceTest()
{
	using namespace distributed;
	std::cout << "\n=========性能测试========" << std::endl;

	ConsistentHash ch(150);//150个虚拟节点

	//添加10个真实节点

	for (int i = 1; 1 <= 10; ++i)
	{
		ch.addNode("192.168.1." + std::to_string(i));
	}

	//测试查找性能
	const int TEST_COUNT = 1000000;
	auto start = std::chrono::high_resolution_clock::now();
	
	for (int i = 0; i < TEST_COUNT; ++i)
	{
		std::string key = "test_key_" + std::to_string(i);
		ch.getNode(key);

	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "查找" << TEST_COUNT << "次耗时：" << duration.count() << "ms" << std::endl;
	std::cout << "平均每次：" << duration.count() * 1000.0 / TEST_COUNT << "us" << std::endl;

}