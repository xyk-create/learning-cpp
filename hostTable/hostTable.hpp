#pragma once
#include<iostream>
#include<vector>
using namespace std;
enum st
{   //哈希位置的状态
	Empty,Delete,Exist
};
template<class K,class V>
struct HashData
{
	pair<K, V> _kv;
	enum st _state;
};
template<class K,class V>
class HashTable
{
public:
	HashTable()
		:_tables(__stl_next_prime(0))
		, _n(0)
	{}
	inline unsigned long __stl_next_prime(unsigned long n)
	{
		// Note: assumes long is at least 32 bits.
		static const int __stl_num_primes = 28;
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
		const unsigned long* pos = lower_bound(first, last, n);
		return pos == last ? *(last - 1) : *pos;
	}
	bool insert(const pair<K, V>& kv)
	{
		if (Find(kv.first)) return false;
		if (_n / (double)_tables.size() >= 0.7)
		{
			HashTable<K, V> newht;
			newht._tables.resize(__stl_next_prime(_tables.size() + 1));
			for (auto val : _tables)
			{
				newht.insert(val._kv);
			}
		}
		int k = kv.first % _tables.size();
		while (_tables[k]._state == Exist)
		{
			k++;
			if (k == _tables.size()) k = 0;
		}
		_tables[k]._kv = kv;
		_tables[k]._state = Exist;
		_n++;
		return true;
	}
	bool Find(const K key)
	{
		int k = key % _tables.size();
		while (_tables[k]._state != Empty)
		{
			if (_tables[k]._kv.first == key&& _tables[k]._state==Exist) return true;
			k++;
			if (k == _tables.size()) k = 0;
		}
		return false;
	}

	bool Erase(K key)
	{
		int k = key % _tables.size();
		while (_tables[k]._state != Empty)
		{
			if (_tables[k]._kv.first == key)
			{
				_tables[k]._state = Delete;
				return true;
			}
			k++;
			if (k == _tables.size()) k = 0;
		}
		return false;
	}
private:
	vector<HashData<K, V>> _tables;
	size_t _n;
};