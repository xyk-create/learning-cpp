
#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
enum Status
{
	EMPTY,
	DELETE,
	EXIST
};
template <class K,class V>
class HashData
{
public:
	std::pair<K,V> _kv;
	enum Status _state;
};

template <class K,class V>
class HashTable
{
public:
	HashTable()
	:_tables(__stl_next_prime(0)),
	_count(0){}
	bool insert(const std::pair<K,V>& kv)
	{
		if(Find(kv.first)!=-1) return false;
		if(_count/((double)_tables.size()*1.0)>=0.7)
		{
			HashTable<K,V> newht;
			newht._tables.resize(__stl_next_prime(_tables.size()+1));
			for(auto val:_tables)
			{
				newht.insert(val._kv);
			}
			_tables.swap(newht._tables);
		}
		int k = kv.first%_tables.size();
		while(_tables[k]._state == EXIST)
		{
			k++;
			if(k == _tables.size()) k = 0;
		}
		_tables[k]._kv = kv;
		_tables[k]._state = EXIST;
		_count++;
		return true;
	}
	// 获取下一个素数（用于哈希表扩容）
	inline unsigned long __stl_next_prime(unsigned long n)
	{
		// 注意：假设long至少32位
		static const int __stl_num_primes = 28;	// 素数个数
		// 预定义的素数列表
		static const unsigned long __stl_prime_list[__stl_num_primes] = {
			53, 97, 193, 389, 769,
			1543, 3079, 6151, 12289, 24593,
			49157, 98317, 196613, 393241, 786433,
			1572869, 3145739, 6291469, 12582917, 25165843,
			50331653, 100663319, 201326611, 402653189, 805306457,
			1610612741, 3221225473, 4294967291
		};
		const unsigned long* first = __stl_prime_list;
		const unsigned long* last = __stl_prime_list + __stl_num_primes;
		const unsigned long* pos = std::lower_bound(first, last, n);
		return pos == last ? *(last - 1) : *pos;
	}
	int Find(const K key)
	{
		int k = key%_tables.size();
		while(_tables[k]._state!=EMPTY)
		{
			if(_tables[k]._state == EXIST&&_tables[k]._kv.first == key)
			{
				return k;
			}
			k++;
			if(k == _tables.size()) k = 0;
			if(k == key%_tables.size()) return -1;
		}
		return -1;
	}
	V operator[](const K key)
	{
		int k = key%_tables.size();
		while(_tables[k]._state!=EMPTY)
		{
			if(_tables[k]._state == EXIST&&_tables[k]._kv.first == key)
			{
				return _tables[k]._kv.second;
			}
			k++;
			if(k == _tables.size()) k = 0;
			if(k == key%_tables.size()) return V();
		}
		return V();
	}
	bool Erase(const K key)
	{
		int ret = Find(key);
		if(ret == -1) return false;
		_tables[ret]._state = DELETE;
		return true;
	}
private:
	std::vector<HashData<K,V>> _tables;
	int _count;
};