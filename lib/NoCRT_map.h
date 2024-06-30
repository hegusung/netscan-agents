#pragma once
#ifndef __NOCRT_MAP_HEADER
#define __NOCRT_MAP_HEADER

#include "../lib/NoCRT.h"
#include "../lib/NoCRT_list.h"

/*
* Helper functions to remove the visual Studio CRT
* Project : https://github.com/hegusung/netscan-agents
*/


template <typename K, typename V>
class Key_Value
{
public:
	K first;
	V second;

	Key_Value()
	{
		first;
		second;
	}

	Key_Value(const K key)
	{
		first = key;
		second;
	}

	Key_Value(const K key, const V value)
	{
		first = key;
		second = value;
	}
	
	~Key_Value()
	{}

};

template <typename K, typename V>
class map
{
private:
	list<Key_Value<K, V>> items;

public:
	typedef Iterator<Key_Value<K, V>> iterator;

	map()
	{
	}
	map(const map& p_map)
	{
		this->map<K, V>::map<K, V>();
		Iterator<Key_Value<K, V>> l_iterFirst = p_map.begin();
		for (; (l_iterFirst != p_map.end()); l_iterFirst++)
		{
			this->insert((*l_iterFirst).first, (*l_iterFirst).second);
		}
	}
	map(Iterator<Key_Value<K, V>> p_begin, Iterator<Key_Value<K, V>> p_end)
	{
		// TODO
		this->map<K, V>::map<K, V>();
		while (p_begin != p_end)
		{
			this->insert((*p_begin).first, (*p_begin).second);
			p_begin++;
		}
	}
	~map()
	{

	}

	Iterator<Key_Value<K, V>> begin()const
	{
		return items.begin();
	}
	Iterator<Key_Value<K, V>> end()const
	{
		return items.end();
	}
	size_t size()
	{
		return items.size();
	}
	Iterator<Key_Value<K, V>> find(K key)const
	{
		Iterator<Key_Value<K, V>> l_iterFirst = items.begin();
		for (; (l_iterFirst != items.end()); l_iterFirst++)
		{
			if ((*l_iterFirst).first == key)
				break;
		}

		return l_iterFirst;
	}
	bool exists(K key)
	{
		return find(key) != items.end();
	}

	V& operator[](K key)
	{
		Iterator<Key_Value<K, V>> l_iterFirst = items.begin();
		for (; (l_iterFirst != items.end()); l_iterFirst++)
		{
			if ((*l_iterFirst).first == key)
				return (*l_iterFirst).second;
		}

		// Not found, create the key
		items.insert(Key_Value<K, V>(key));

		return this->operator[](key);
	}

	void insert(K f, V s)
	{
		items.insert(Key_Value<K, V>(f, s));
	}

	bool empty()
	{
		if (begin() == end())
			return 1;
		else return 0;
	}

};

#endif