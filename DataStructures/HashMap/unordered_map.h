#pragma once
#include "hash.h"
#include <iostream>
#include <list>

template <typename KeyType, typename ValueType, typename Hash = hash<KeyType>>
class unordered_map
{
private:
	std::list<std::pair<KeyType, ValueType>> m_data;
	struct m_bucket
	{
		size_t m_bucketSize = 0;
		typename std::list<std::pair<KeyType, ValueType>>::iterator m_start;
	};
	m_bucket* m_table;
	size_t m_capacity = 0;
	size_t m_size = 0;

	bool sizeIncrease()
	{
		m_bucket* oldTable = m_table;
		std::list<std::pair<KeyType, ValueType>> oldData = m_data;
		delete[] m_table;
		m_data.clear();
		m_table = new m_bucket[m_capacity * 2 - 1];
		if (!m_table) {
			std::cout << "Memory allocation unsuccessful.\n";
			return false;
		}
		m_capacity = m_capacity * 2 - 1;
		m_size = 0;
		for (auto& oldValues : oldData)
		{
			insert(oldValues);
		}
		return true;
	}

public:

	using iterator = typename std::list<std::pair<KeyType, ValueType>>::iterator;
	iterator begin() {
		return m_data.begin();
	}

	iterator end() {
		return m_data.end();
	}

	iterator find(const KeyType& keyValue)
	{
		m_bucket& findBucket = m_table[hashFunction(keyValue) % m_capacity];
		if (findBucket.m_bucketSize == 0) return end();
		else
		{
			iterator it = m_table[hashFunction(keyValue) % m_capacity].m_start;
			for (size_t cnt = 0; cnt < findBucket.m_bucketSize; cnt++)
			{
				if (it->first == keyValue) return it;
				it++;
			}
			return end();
		}
	}

	iterator insert(const std::pair<KeyType, ValueType>& value)
	{
		if (m_size >= m_capacity) sizeIncrease();
		if (this->find(value.first) != end()) return end();
		m_bucket& insertBucket = m_table[hashFunction(value.first) % m_capacity];
		if (insertBucket.m_bucketSize == 0)
		{
			m_data.push_back(value);
			insertBucket.m_start = std::prev(end());
			insertBucket.m_bucketSize++;
			m_size++;
			return insertBucket.m_start;
		}
		insertBucket.m_start = m_data.insert(insertBucket.m_start, value);
		insertBucket.m_bucketSize++;
		m_size++;
		return insertBucket.m_start;
	}

	void erase(const KeyType& keyValue)
	{
		m_bucket& eraseBucket = m_table[hashFunction(keyValue) % m_capacity];
		if (eraseBucket.m_bucketSize == 0) return;
		else
			if (eraseBucket.m_bucketSize == 1)
			{
				m_data.erase(eraseBucket.m_start);
				eraseBucket.m_bucketSize = 0;
				eraseBucket.m_start = end();
			}
			else
			{
				iterator it = eraseBucket.m_start;
				for (size_t cnt = 0; cnt < eraseBucket.m_bucketSize; cnt++)
				{
					if (it->first == keyValue)
					{
						m_data.erase(it);
						eraseBucket.m_bucketSize--;
						return;
					}
					it++;
				}
				return;
			}
	}

	ValueType& operator[](const KeyType& keyValue)
	{
		iterator it = this->find(keyValue);
		if (it != end()) return it->second;
		else
		{
			return insert(std::pair<KeyType, ValueType>(keyValue, ValueType()))->second;
		}
	}

	size_t bucket(const KeyType& key)
	{
		if (find(key) == end()) return 0;
		return Hash{}(key) % m_capacity;
	}
	size_t hashFunction(const KeyType& key) const
	{
		return Hash{}(key);
	}
	bool empty()
	{
		return m_size == 0;
	}


	unordered_map()
	{
		m_table = new m_bucket[11];
		if (!m_table) {
			std::cout << "Memory allocation unsuccessful.\n";
			return;
		}
		m_capacity = 11;
		m_size = 0;
	}

	unordered_map(unordered_map<KeyType, ValueType, Hash>& copy)
	{
		m_table = new m_bucket[copy.m_capacity];
		if (!m_table) {
			std::cout << "Memory allocation unsuccessful.\n";
			return;
		}
		m_capacity = copy.m_capacity;
		m_size = 0;
		for (auto& value : copy)
		{
			this->insert(value);
		}
	}

	unordered_map<KeyType, ValueType, Hash> operator=(unordered_map<KeyType, ValueType, Hash>& copy)
	{
		for (auto& value : copy)
		{
			this->insert(value);
		}
		return *this;
	}

	~unordered_map()
	{
		delete[] m_table;
		m_data.clear();
	}
};
