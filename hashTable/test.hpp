// #pragma once
// #include<iostream>
// #include<vector>
// using namespace std;

// // 哈希表位置的状态枚举
// enum st
// {	
// 	Empty,	// 空状态，该位置未被占用
// 	Delete,	// 删除状态，该位置曾经有数据但已被删除
// 	Exist	// 存在状态，该位置当前有有效数据
// };

// // 哈希表数据结构模板
// template<class K,class V>
// struct HashData
// {
// 	pair<K, V> _kv;	// 键值对
// 	enum st _state;	// 状态标记
// };

// // 哈希表类模板
// template<class K,class V>
// class HashTable
// {
// public:
// 	// 构造函数，初始化哈希表
// 	HashTable()
// 		:_tables(__stl_next_prime(0))	// 使用素数初始化表大小
// 		, _n(0)	// 初始化元素个数为0
// 	{}

// 	// 获取下一个素数（用于哈希表扩容）
// 	inline unsigned long __stl_next_prime(unsigned long n)
// 	{
// 		// 注意：假设long至少32位
// 		static const int __stl_num_primes = 28;	// 素数个数
// 		// 预定义的素数列表
// 		static const unsigned long __stl_prime_list[__stl_num_primes] = {
// 			53, 97, 193, 389, 769,
// 			1543, 3079, 6151, 12289, 24593,
// 			49157, 98317, 196613, 393241, 786433,
// 			1572869, 3145739, 6291469, 12582917, 25165843,
// 			50331653, 100663319, 201326611, 402653189, 805306457,
// 			1610612741, 3221225473, 4294967291
// 		};
// 		const unsigned long* first = __stl_prime_list;
// 		const unsigned long* last = __stl_prime_list + __stl_num_primes;
// 		const unsigned long* pos = lower_bound(first, last, n);
// 		return pos == last ? *(last - 1) : *pos;
// 	}

// 	// 插入键值对
// 	bool insert(const pair<K, V>& kv)
// 	{
// 		// 如果键已存在，插入失败
// 		if (Find(kv.first)) return false;
		
// 		// 负载因子达到0.7时进行扩容
// 		if (_n / (double)_tables.size() >= 0.7)
// 		{
// 			HashTable<K, V> newht;	// 创建新的哈希表
// 			newht._tables.resize(__stl_next_prime(_tables.size() + 1));	// 扩容到下一个素数大小
			
// 			// 将旧表中的数据重新插入到新表中
// 			for (auto val : _tables)
// 			{
// 				newht.insert(val._kv);
// 			}
// 			_tables.swap(newht._tables);
// 		}
		
// 		// 计算初始位置（使用除留余数法）
// 		int k = kv.first % _tables.size();
		
// 		// 线性探测，找到空位置
// 		while (_tables[k]._state == Exist)
// 		{
// 			k++;
// 			if (k == _tables.size()) k = 0;	// 到达表尾时从头开始
// 		}
		
// 		// 插入数据
// 		_tables[k]._kv = kv;
// 		_tables[k]._state = Exist;
// 		_n++;
// 		return true;
// 	}

// 	// 查找键
// 	bool Find(const K key)
// 	{
// 		// 计算初始位置
// 		int k = key % _tables.size();
		
// 		// 线性探测查找
// 		while (_tables[k]._state != Empty)
// 		{
// 			// 找到匹配的键且状态为存在
// 			if (_tables[k]._kv.first == key&& _tables[k]._state==Exist) return true;
// 			k++;
// 			if (k == _tables.size()) k = 0;	// 到达表尾时从头开始
// 		}
// 		return false;
// 	}

// 	// 删除键值对
// 	bool Erase(K key)
// 	{
// 		// 计算初始位置
// 		int k = key % _tables.size();
		
// 		// 线性探测查找要删除的元素
// 		while (_tables[k]._state != Empty)
// 		{
// 			if (_tables[k]._kv.first == key)
// 			{
// 				_tables[k]._state = Delete;	// 标记为删除状态
// 				return true;
// 			}
// 			k++;
// 			if (k == _tables.size()) k = 0;	// 到达表尾时从头开始
// 		}
// 		return false;
// 	}
// private:
// 	vector<HashData<K, V>> _tables;	// 哈希表数组
// 	size_t _n;	// 当前元素个数
// };