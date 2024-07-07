#pragma once
#ifndef __NOCRT_LIST_HEADER
#define __NOCRT_LIST_HEADER

/*
* Helper functions to remove the visual Studio CRT
* Project : https://github.com/hegusung/netscan-agents
*/

#include "../lib/NoCRT.h"

// Taken from https://github.com/abulyaev/std-list-implementation/blob/master/src/List.h

template <typename T>
class Node
{
public:
	T m_node;
	Node<T>* m_next;
	Node<T>* m_prev;

	Node()
	{
		m_node;
		m_next = NULL;
		m_prev = NULL;
	}

	Node(const T data)
	{
		m_node = data;
		m_next = NULL;
		m_prev = NULL;
	}
	
	~Node()
	{}

};

template<typename T>
class Iterator
{
private:
	Node<T>* m_ptr;
public:
	Iterator()
	{
		m_ptr = NULL;
	}
	Iterator(Node<T> *p_ptr)
	{
		m_ptr = p_ptr;
	}
	Iterator(const Iterator<T>& p_iter)
	{
		m_ptr = p_iter.m_ptr;
	}
	Node<T>* getPtr()
	{
		return m_ptr;
	}
	T& operator* ()
	{
		if (m_ptr != NULL) return m_ptr->m_node;
	}
	Iterator<T>& operator ++()
	{
		if ((this->m_ptr != NULL) && (this->m_ptr->m_next != 0))
			m_ptr = m_ptr->m_next;
		return *this;
	}
	Iterator<T>& operator --()
	{
		if ((this->m_ptr != NULL) && (this->m_ptr->m_prev != 0))
			m_ptr = m_ptr->m_prev;
		return *this;
	}
	Iterator<T> operator ++(int)
	{
		Iterator l_tmp(*this);
		if ((this->m_ptr != NULL) && (this->m_ptr->m_next != 0))
			m_ptr = m_ptr->m_next;
		return l_tmp;
	}
	Iterator<T> operator --(int)
	{
		Iterator<T> l_temp(*this);
		if ((this->m_ptr != NULL) && (this->m_ptr->m_prev != 0))
			m_ptr = m_ptr->m_prev;
		return l_temp;
	}
	const bool operator == (const Iterator<T>& p_second)
	{
		return this->m_ptr == p_second.m_ptr;
	}
	const bool operator != (const Iterator<T>& p_second)
	{
		return !(*this == p_second);
	}

	Iterator<T>& operator = (Iterator<T>& p_iter)
	{
		m_ptr = p_iter.m_ptr;
		return (*this);
	}
};

template <typename T>
class list
{
private:
	int m_count;
	Node<T>* m_first;
	Node<T>* m_last;

public:
	typedef Iterator<T> iterator;

	list()
	{
		m_first = new Node<T>();
		m_last = new Node<T>();
		m_first->m_next = m_last;
		m_first->m_prev = NULL;
		m_last->m_next = NULL;
		m_last->m_prev = m_first;
		this->m_count = 0;
	}
	list(const list& p_list)
	{
		this->list<T>::list<T>();
		Iterator<T> l_iterFirst = p_list.begin();
		for (; (l_iterFirst != p_list.end()); l_iterFirst++)
		{
			this->insert(*l_iterFirst);
		}
	}
	list(int p_count, T p_data)
	{
		(this)->list<T>::list<T>();
		for (int i = 0; i < p_count; i++)
			this->insert(p_data);
	}
	list(Iterator<T> p_begin, Iterator<T> p_end)
	{
		(this)->list<T>::list<T>();
		while (p_begin != p_end)
		{

			this->insert(*p_begin);
			p_begin++;
		}
	}
	~list()
	{
		Node<T>* l_ptr;
		this->m_count = 0;
		while (m_first != NULL)
		{
			l_ptr = m_first;
			m_first = m_first->m_next;
			delete l_ptr;
		}
	}

	Iterator<T> begin()const
	{
		return Iterator<T>(m_first->m_next);
	}
	Iterator<T> end()const
	{
		return Iterator<T>(m_last);
	}

	T& operator[](size_t i)
	{
		Node<T>* buf = m_first->m_next;
		for (int j = i; j > 0; j--)
		{
			buf = buf->m_next;
		}

		return buf->m_node;
	}

	list<T>& operator=(const list<T>& p_list)
	{
		if (this != &p_list)
		{
			//(this)->clear();

			(this)->~list<T>();
			//new (this) list<T>(p_list);
			this->list<T>::list<T>(p_list);
			//list<T> l = list<T>(p_list);

			return *this;
		}
		else
			return *this;
	}
	void swap(list<T>& p_list)
	{
		Node<T>* l_firstTemp, * l_lastTemp;
		l_firstTemp = m_first;
		l_lastTemp = m_last;
		m_first = p_list.m_first;
		m_last = p_list.m_last;
		p_list.m_first = l_firstTemp;
		p_list.m_last = l_lastTemp;
	}
	int size() const
	{
		return this->m_count;
	}
	void insert(T p_node)
	{
		Node<T>* to_add = new Node<T>(p_node);
		Node<T>* buf = m_first->m_next;
		while (buf != m_last)
		{
			buf = buf->m_next;
		}
		buf->m_prev->m_next = to_add;
		to_add->m_next = buf;
		to_add->m_prev = buf->m_prev;
		buf->m_prev = to_add;
		m_count++;
	}
	void push_back(T p_node)
	{
		this->insert(p_node);
	}
	bool remove(T p_data)
	{
		return this->erase(p_data);
	}
	int clear(int p_num)
	{
		if (p_num > m_count) return -1;
		Node<T>* buf = m_first;
		for (int i = 1; i <= p_num; i++)
			buf = buf->m_next;
		buf->m_prev->m_next = buf->m_next;
		buf->m_next->m_prev = buf->m_prev;
		m_count--;
		return m_count;
	}
	void clear_memory()
	{
		Node<T>* buf = m_first;
		Node<T>* to_del = m_first;
		while (to_del != m_last)
		{
			buf = buf->m_next;
			delete to_del;
			to_del = buf;
		}
		m_count = 0;
	}
	bool empty()
	{
		if (begin() == end())
			return 1;
		else return 0;
	}
	bool erase(T p_data)
	{
		Node<T>* l_temp;
		Node<T>* l_iter = m_first->m_next;
		if (this->m_count == 0) { return 0; }
		while ((l_iter->m_node != p_data) && (l_iter->m_next != m_last))
			l_iter = l_iter->m_next;
		if (l_iter->m_node == p_data)
		{
			l_temp = l_iter;
			l_iter->m_next->m_prev = l_temp->m_prev;
			l_iter->m_prev->m_next = l_temp->m_next;
			delete l_iter;
			this->m_count--;
			return 1;
		}
		return 0;
	}
	bool erase(T p_dataFirst, T p_dataSecond)
	{
		Node<T>* l_temp;
		Node<T>* l_iter = m_first->m_next;
		if (this->m_count == 0) { return 0; }
		while ((l_iter->m_node < p_dataFirst) && (l_iter->m_next != m_last))
			l_iter = l_iter->m_next;
		while ((l_iter != m_last) && l_iter->m_node < p_dataSecond)
		{
			l_temp = l_iter;
			l_iter->m_next->m_prev = l_temp->m_prev;
			l_iter->m_prev->m_next = l_temp->m_next;
			l_temp = l_iter->m_next;
			delete l_iter;
			l_iter = l_temp;
			this->m_count--;
		}

		return 1;
	}
	T& front()
	{
		return this->m_first->m_next->m_node;
	}
	T& back()
	{
		return this->m_last->m_prev->m_node;
	}
	void pop_front()
	{
		Node<T>* buf;
		buf = m_first->m_next;
		m_first->m_next = buf->m_next;
		buf->m_next->m_prev = m_first;
	}
	void pop_back()
	{
		Node<T>* buf;
		buf = m_last->m_prev;
		m_last->m_prev = buf->m_prev;
		buf->m_prev->m_next = m_last;
	}
	const bool operator == (const list<T>& p_listSecond)
	{
		if (this->size() != p_listSecond.size())
			return 0;

		Iterator<T> l_iterFirst = this->begin();
		Iterator<T> l_iterSecond = p_listSecond.begin();
		for (; (l_iterFirst != this->end()) && (l_iterSecond != p_listSecond.end()) && (*l_iterFirst == *l_iterSecond); l_iterFirst++, l_iterSecond++);
		return (l_iterSecond == p_listSecond.end() && l_iterFirst == this->end());
	}
	const bool operator != (const list<T>& p_listSecond)
	{
		return !(*this == p_listSecond);
	}
};

#endif
