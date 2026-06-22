#ifndef CONSISYENT_HASH_H
#define CONSISTENT_HASH_H
#include<string>
#include<vector>
#include<map>
#include<memory>
#include<mutex>
#include<functional>
#include<sstream>

namespace distributed
{
	/*
	* @brief（指示） 一致性哈希算法实现类
	* 
	* 用于分布式系统中数据分片和负载均衡，支持虚拟节点机制
	* 线程安全：所有公共方法都通过互斥锁保护
	*/
	class ConsistentHash
	{
	public:
		/*
			@brief 构造函数
			@param virtual_nodes 每个真实节点对应的虚拟节点数，默认是100
			
		*/
		explicit ConsistentHash(int virtual_nodes = 100);
		/*
					@brief析构函数
		*/
		~ConsistentHash() = default;
		//禁止拷贝和赋值
		ConsistentHash(const ConsistentHash&) = delete;
		ConsistentHash& operator=(const ConsistentHash&) = delete;

		//允许移动
		ConsistentHash(ConsistentHash&&) = default;
		ConsistentHash& operator=(ConsistentHash&&) = default;
		/*
		@brief 添加真实节点
		@param node 节点标识（如IP地址或主机名）
		@return true 添加成功，false节点已存在
		*/
		bool addNode(const std::string& node);
		/*
		@brief 移除真实节点
		@return true 移除成功 ，false节点不存在
		*/
		bool removeNode(const std::string& node);
		/*
		@brief 获取key对应的节点
		@param key 数据键值
		@return 节点标识，如果环为空则返回空字符串
		*/
		std::string getNode(const std::string& key)const;
		/*
		@获取所有真实节点
		@return 真实节点列表
		*/
		std::vector<std::string>getNode()const;
		/*
		@brief 获取虚拟节点总数
		*/
		size_t getVirtualNodeCount()const;
		/*
		@brief 清空所有节点
		*/
		void clear();
		/*
		@brief 获取节点数
		*/
		size_t size()const;
		/*
		@检查是否为空
		*/
		bool empty() const;
	private:
		using RingType = std::map<size_t, std::string>;

		/*
		@biref 哈希函数（可替换为更高效的实现）
		@param(参数) str 输入字符串
		@return  哈希值
		*/
		size_t hash(const std::string& str)const;
		/*
			@brief 生成虚拟节点名称
			@param node 真实的节点
			@param index 虚拟节点索引
		*/
		std::string getVirtualNodeName(const std::string& node, int index);

		/*
			检查节点是否存在（不加锁，内部使用）
		*/

		bool nodeExists(const std::string& node)const;
	
	private:
		int virtual_nodes_;//每个真实节点的虚拟节点数
		RingType ring_;//一致性哈希环，键为哈希值，值为节点名称
		std::vector<std::string>real_nodes_;//真实节点列表
		mutable std::mutex mutex_;//互斥锁，保护共享数据结构
		friend class ConsistentHashTest;//测试类，允许访问私有成员
	};	
}//namespace distirbuted
#endif//CONSISTENT_HASH_H
