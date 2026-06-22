#include<iostream>
using namespace std;
#include<vector>
#include<list>
class HashTable
{
public:
	HashTable(int size = primes_[0], double loadFactor = 0.75) :useBucketNum_(0)
		, loadFactor_(loadFactor)
		, primeIdx_(0)
	{
		if (size != primes_[0])
		{
			for (; primeIdx_ < PRIME_SIZE; primeIdx_++)
			{
				if (primes_[primeIdx_] > size)
				{
					break;
				}
			}
			if (primeIdx_ == PRIME_SIZE)
			{
				primeIdx_--;
			}
		}
		table_.resize(primes_[primeIdx_]);
	}
public:
	//增加元素，不能重复插入key
	void insert(int key)
	{
		//判断扩容
		double factor = useBucketNum_ * 1.0 / table_.size();
		cout << "factor:" << factor << endl;
		if (factor > loadFactor_)
		{
			expand();
		}
		int idx = key % table_.size();
		if (table_[idx].empty())
		{
			useBucketNum_++;
			table_[idx].emplace_front(key);
		}
		else
		{
			//使用全局的::find泛型算法，而不是调用自己的成员发法。
			auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
			if (it == table_[idx].end())
			{
				//key不存在
				table_[idx].emplace_front(key);
			}
		}
	}
	//删除
	void erase(int key)
	{
		int idx = key % table_.size();
		auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
		if (it != table_[idx].end())
		{
			table_[idx].erase(it);
			if (table_[idx].empty())
			{
				useBucketNum_--;
			}
		}
	}
	//搜索元素
	bool find(int key)
	{
		int idx = key % table_.size();
		auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
		return it != table_[idx].end();

	}
private:
	void expand()
	{
		if (primeIdx_ + 1 == PRIME_SIZE)
			throw "hashtable can not expand anymore!";
		primeIdx_++;
		useBucketNum_ = 0;
		vector<list<int>>oldTable;
		table_.swap(oldTable);
		table_.resize(primes_[primeIdx_]);
		for (auto &list : oldTable)
		{
			for (auto key : list)
			{
				int idx = key % table_.size();
				if (table_[idx].empty())
				{
					useBucketNum_++;
				}
				table_[idx].emplace_front(key);
			}
		}
	}
private:
	vector<list<int>>table_;//哈希表的数据结构
	int useBucketNum_;//记录桶的个数
	double loadFactor_;//记录哈希表的装载因子
	static const int PRIME_SIZE = 10;//素数表的个数
	static int primes_[PRIME_SIZE];//素数表
	int primeIdx_;//当前使用素数表的下标
};
int HashTable::primes_[HashTable::PRIME_SIZE] = {
	11, 23, 47, 97, 193, 389, 769, 1543, 3079, 6151
};
int main()
{
	HashTable htable;
	htable.insert(21);
	htable.insert(32);
	htable.insert(14);
	htable.insert(15);
	htable.insert(2333);

	// 测试查找和删除
	cout << htable.find(21) << endl;
	htable.erase(21);
	cout << htable.find(21) << endl;
	return 0;
}