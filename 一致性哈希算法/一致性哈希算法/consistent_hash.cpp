//#include<iostream>
//#include<string>
//#include<set>
//#include<list>
//using namespace std;
//#include"md5.h"
//
////一致性哈希环的取值类型
//using uint = unsigned int;
////前置生命物理节点主机类型
//class PhscialHost;
//
////虚拟节点 
//class VirtualHost
//{
//public:
//	VirtualHost(string ip, PhscialHost* p)
//		:ip_(ip)
//		,phscialHost_(p)
//	{
//		md5_ = getMD5(ip_.c_str());
//	}
//	bool operator<(const VirtualHost& host)
//	{
//		return md5_ < host.md5_;
//	}
//	bool operator==(const VirtualHost& host)
//	{
//		return ip_ == host.ip_;
//	}
//private:
//	string ip_;//虚拟节点的ip信息
//	int md5_;//虚拟节点在一致性哈希环上的位置
//	PhscialHost* phscialHost_;//虚拟节点隶属的物理节点
//};
////物理节点
//class PhscialHost
//{
//public:
//	PhscialHost(string ip, int vnumber)
//		:ip_(ip)
//	{
//		for (int i = 0; i < vnumber; i++)
//		{
//			//虚拟节点需要一个IP,还需要记录它属于哪一个物理节点
//			virtualHosts_.emplace_back(
//				ip + "#" + ::to_string(i),
//				this
//			);
//		}
//	}
//	string getIP()const
//	{
//		return ip_;
//	}
//	const list<VirtualHost>& getVirtualHosts()const
//	{
//		return virtualHosts_;
//	}
//private:
//	string ip_;//物理机器的IP地址
//	list<VirtualHost>virtualHosts_;//存储虚拟节点的列表
//
//};
////一致性哈希原理
//class ConsistentHash
//{
//public:
//	//在一致性哈希环上添加物理主机的虚拟节点
//	void addHost(PhscialHost& host)
//	{
//		//获取物理主机所有的虚拟节点列表
//		auto list = host.getVirtualHosts();
//		for (auto host : list)
//		{
//			hashCircle_.insert(host);
//		}
//	}
//	//在一致性哈希环上删除物理主机的虚拟节点
//	void delHost(PhscialHost& host)
//	{
//		//获取物理主机所有的虚拟节点列表
//		auto list = host.getVirtualHosts();
//		for (auto host : list)
//		{
//			auto it = hashCircle_.find(host);
//			if (it != hashCircle_.end())
//			{
//				//在一致性哈希环上删除所有物理主机对应的虚拟节点
//				hashCircle_.erase(it);
//			}
//		}
//	}
//	//返回负载的真实物理节点IP信息
//	string getHost(string clientip)
//	{
//		int md5 = getMD5(clientip.c_str());
//	}
//	
//private:
//	set<VirtualHost>hashCircle_;//一致性哈希环
//
//};
//int main()
//{
//	return 0;
//}
#include<iostream>
#include"consistent_hash.h"
#include<algorithm>

namespace distributed
{
	//使用std::hash作为默认的哈希函数
	static std::hash<std::string>hasher;
	ConsistentHash::ConsistentHash(int virtual_nodes)
		:virtual_nodes_(virtual_nodes)
	{
		if (virtual_nodes_ <= 0)
		{
			virtual_nodes_ == 100;//默认值
		}
	}
	bool ConsistentHash::addNode(const std::string& node)
	{
		std::lock_guard<std::mutex>lock(mutex_);
		//检查节点是否已存在
		if (nodeExists(node))
		{
			return false;
		}
		//添加真实节点
		real_nodes_.push_back(node);

		//创建虚拟节点并添加到哈希环
		for (int i = 0; i < virtual_nodes_; ++i)
		{
			std::string virtual_node = getVirtualNodeName(node, i);
			size_t h = hash(virtual_node);
			ring_[h] = node;//虚拟节点映射到真实节点
		}
		return true;
	}
	bool ConsistentHash::removeNode(const std::string& node)
	{
		std::lock_guard<std::mutex>lock(mutex_);

		//从真实节点列表中移除
		auto it = std::find(real_nodes_.begin(), real_nodes_.end(), node);
		if (it == real_nodes_.end())
		{
			return false;//节点不存在
		}
		real_nodes_.erase(it);

		//从哈希环中移除所有属于该节点的虚拟节点
		for (auto ring_it = ring_.begin(); ring_it != ring_.end();)
		{
			if (ring_it->second == node)
			{
				ring_it = ring_.erase(ring_it);
			}
			else {
				++ring_it;
			}
		}
		return true;
	}
	std::string ConsistentHash::getNode(const std::string& key)const
	{
		std::lock_guard<std::mutex>lock(mutex_);

		if (ring_.empty())
		{
			return "";//环为空，返回空字符串
		}

		//计算key的哈希值
		size_t h = hash(key);

		//在环上查找第一个哈希值大于等于h的节点
		auto it = ring_.lower_bound(h);

		//如果没找到（即h大于环上所有哈希值），则返回第一个节点
		if (it == ring_.end())
		{
			it = ring_.begin();
		}
		return it->second;
	}
	std::vector<std::string>ConsistentHash::getNode()const
	{
		std::lock_guard<std::mutex>lock(mutex_);
		return real_nodes_;
	}
	void ConsistentHash::clear()
	{
		std::lock_guard<std::mutex>lock(mutex_);
		ring_.clear();
		real_nodes_.clear();
	}
	size_t ConsistentHash::size()const
	{
		std::lock_guard<std::mutex> lock(mutex_);
		return real_nodes_.size();
	}
	bool ConsistentHash::empty() const
	{
		std::lock_guard<std::mutex> lock(mutex_);
		return real_nodes_.empty();
	}
	size_t ConsistentHash::hash(const std::string& str)const
	{
		return hasher(str);
	}
	std::string ConsistentHash::getVirtualNodeName(const std::string& node, int index)
	{
		return node + "#" + std::to_string(index);
	}
	bool ConsistentHash::nodeExists(const std::string& node)const
	{
		return std::find(real_nodes_.begin(), real_nodes_.end(), node) != real_nodes_.end();
	}
}
