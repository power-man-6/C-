#include<iostream>
#include<vector>
#include<functional>
#include<string>
#include<cmath>

class BloomFilter
{
private:
	std::vector<bool>bits;//位数组
	int size;//位数组的大小
	int hash_count;//哈希函数的数量
	int element_count;//已插入元素的数量

	//使用不同的种子来模拟多个哈希函数
	std::vector<unsigned int>seeds;

		//基础的哈希函数：BKDRHash
		unsigned int BKDRHash(const std::string& str, unsigned int seed)const
	{
			unsigned int hash = 0;
			for (char c : str)
			{
				hash = hash * seed + c;
			}
			return hash;
	}
		//获取第K个哈希函数的位置
		unsigned int hash(const std::string& str, int k)const
		{
			return BKDRHash(str, seeds[k] )% size;
		}
public:
	//构造函数
	BloomFilter(int size, int hash_count)
		:size(size)
		,hash_count(hash_count)
		,element_count(0)
	{
		bits.resize(size, false);

		//初始化不同的种子
		seeds.resize(hash_count);
		for (int i = 0; i < hash_count; i++)
		{
			seeds[i] = 131 + i * 131;
		}
	}
public:
	//插入元素
	void insert(const std::string& str)
	{
		for (int i = 0; i < hash_count; i++)
		{
			unsigned int pos = hash(str, i);
			bits[pos] = true;
		}
		element_count++;
	}

	//查询元素是否存在
	bool contains(const std::string& str)const
	{
		for (int i = 0; i < hash_count; i++)
		{
			unsigned int pos = hash(str, i);
			if (!bits[pos])
			{
				return false;//如果有一个位置为0，说明元素一定不存在
			}
		}
		return true;//所有位都为1，可能存在（有一定的误判率）
	}
	//清空过滤器(将所有的位都填充成0)
	void clear()
	{
		std::fill(bits.begin(), bits.end(), false);
			element_count = 0;
	}
	//获取误判率
	double getFalsePositiveRate() const
	{
		if (element_count == 0) return 0.0;
		//误判率公式：（1-e^(-hash_count * element_count/size)）^hash_count
		double p = std::exp(-static_cast<double>(hash_count) * element_count / size);
		p = 1 - p;
		p = std::pow(p, hash_count);
		return p;
			
	}
	//获取当前填充率
	double getFillRate()const
	{
		int count = 0;
		for (bool b : bits)
		{
			if (b) count++;
		}
		return static_cast<double>(count) / size;
	}
	//打印统计信息
	void printStats()const
	{
		std::cout << "Bloom Filter statistics:\n";
		std::cout << "Size" << size << "bits\n";
		std::cout << "Hash functions:" << hash_count << "\n";
		std::cout << "Elements:" << element_count << "\n";
		std::cout << "Fill ratio" << getFillRate() * 100 << "%\n";
		std::cout << "Estimated false positive rate:"
			<< getFalsePositiveRate() * 100 << "%\n";
	}

};
//高级实现
class AdvanceBloomFilter
{
private:
	std::vector<bool>bits;
	int size;
	int hash_count;
	int element_count;
	std::vector<std::function<unsigned int(const std::string&)>> hash_function;
	//多种哈希函数的实现
	static unsigned int RSHash(const std::string& str)
	{
		unsigned int b = 378551;
		unsigned int a = 63689;
		unsigned int hash = 0;
		for (char c : str)
		{
			hash = hash * a + c;
			a *= b;
		}
		return hash;
	}
	//根据预期元素数量和期望误判率自动优化参数
	AdvanceBloomFilter(int expected_elements, double false_positive_rate)
	{
		//m=-n*ln(p) /(ln(2)^2)
		size = static_cast<int>(
			-expected_elements * std::log(false_positive_rate)
			/ (std::log(2) * std::log(2))
			) + 1;
	}
};
int main() {
	std::cout << "=== 基础布隆过滤器 ===\n";
	// 创建一个大小为1000位，使用3个哈希函数的布隆过滤器
	BloomFilter bf(1000, 3);
	// 插入一些元素
	std::vector<std::string> test_data = {
		"apple", "banana", "orange", "grape", "watermelon"
	};
	// 查询存在的元素
	for (const auto& item : test_data) {
		std::cout << item << ": "
			<< (bf.contains(item) ? "可能存在" : "一定不存在") << "\n";
	}
	// 测试误判
	int false_positive = 0;
	int tests = 10000;
	for (int i = 1000; i < 1000 + tests; i++) {
		if (bf.contains("key" + std::to_string(i))) {
			false_positive++;
		}
	}
}
//int main()
//{
//	std::cout << "===基础布隆过滤器===\n";
//	//创建一个大小为1000位，使用3个哈希函数的布隆过滤器
//	BloomFilter bf(1000, 3);
//	//插入一些元素
//	std::vector<std::string>test_data = {
//		"apple", "banana", "orange", "grape", "watermelon",
//		"peach", "strawberry", "blueberry", "kiwi", "mango"
//	};
//	for (const auto& item : test_data)
//	{
//		bf.insert(item);
//		std::cout << "Inserted:" << item << "\n";
//	}
//	//查询一些元素
//	std::cout << "\n===查询存在的元素===\n";
//	for (const auto& item : test_data)
//	{
//		std::cout << item << ":"
//			<< (bf.contains(item) ? "可能存在" : "一定不存在") << "\n";
//	}
//	//查询不存在的元素（可能产生误判）
//	std::cout << "\n===查询不存在的元素===\n";
//	std::vector<std::string> test_not_exist = {
//	"ponrapple","kiwi","mange" };
//
//	for (const auto& item : test_not_exist)
//	{
//		std::cout << item << ":"
//			<< (bf.contains(item) ? "可能存在（可能误判）" : "一定不存在") << "\n";
//	}
//	bf.printStats();
//
//}

