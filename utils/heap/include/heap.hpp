/*
 * heap.hpp
 *
 *  Created on: 01-Aug-2015
 *      Author: karan
 */

#ifndef UTILS_HEAP_INCLUDE_HEAP_HPP_
#define UTILS_HEAP_INCLUDE_HEAP_HPP_

#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;

/**
 * @brief basic_heap_traits provides
 * @tparam T template parameter to tell type
 */
template<class T>
class basic_heap_traits
{
public:
	///@brief Member function to provide == operator support.
	static bool eq (T& a, T& b);
	static bool lt (T& a, T& b);
};

template <class T, bool isFundamental = std::is_fundamental< typename std::remove_pointer<T>::type >::value > class basic_heap_min_traits;
template <class T, bool isFundamental = std::is_fundamental< typename std::remove_pointer<T>::type >::value > class basic_heap_max_traits;

template <class T>
class basic_heap_min_traits<T,true> : public basic_heap_traits <T>
{
public:
	static bool eq (T& a, T& b) {return a == b ? true : false;}
	static bool lt (T& a, T& b) {return a < b ? true : false;}
	static bool lte (T& a, T& b)
	{
		if (true == basic_heap_min_traits<T>::eq(a,b)) return true;
		return basic_heap_min_traits<T>::lt(a,b);
	}
};

template <class T>
class basic_heap_max_traits<T,true> : public basic_heap_traits <T>
{
public:
	static bool eq (T& a, T& b) {return a == b ? true : false;}
	static bool lt (T& a, T& b) {return a > b ? true : false;}
	static bool lte (T& a, T& b)
	{
		if (true == basic_heap_max_traits<T>::eq(a,b)) return true;
		return basic_heap_max_traits<T>::lt(a,b);
	}
};

template <class T>
class basic_heap_min_traits<T*,true> : public basic_heap_traits <T>
{
public:
	static bool eq (T* &a, T* &b) {return *a == *b ? true : false;}
	static bool lt (T* &a, T* &b) {return *a < *b ? true : false;}
	static bool lte (T* &a, T* &b)
	{
		if (true == basic_heap_min_traits<T*>::eq(a,b)) return true;
		return basic_heap_min_traits<T*>::lt(a,b);
	}
};

template <class T>
class basic_heap_max_traits<T*,true> : public basic_heap_traits <T>
{
public:
	static bool eq (T* &a, T* &b) {return *a == *b ? true : false;}
	static bool lt (T* &a, T* &b) {return *a > *b ? true : false;}
	static bool lte (T* &a, T* &b)
	{
		if (true == basic_heap_max_traits<T*>::eq(a,b)) return true;
		return basic_heap_max_traits<T*>::lt(a,b);
	}
};

template <class T, class traits = basic_heap_traits<T> >
class heap
{
	vector<T> m_heap;
	size_t m_size;
public:
	heap()
	{
		m_size=0;
	}
	void insert(T);
	T extractTop();
	void decompile();
	size_t getSize()
	{return m_size;}
};

template <class T, class traits>
void heap<T,traits>::insert(T node)
{
	size_t parent,child;
	T tempNode;
	m_heap.push_back(node);
	m_size++;
	child = m_size;
	parent = (child)/2;
	while((parent >=1) && (false == traits::lt(m_heap[parent-1],m_heap[child-1])))
	{
		tempNode = m_heap[child-1];
		m_heap[child-1] = m_heap[parent-1];
		m_heap[parent-1] = tempNode;
		child = parent;
		parent = parent/2;
	}
}

template <class T, class traits>
T heap<T,traits>::extractTop(void)
{
	T retVal = m_heap[0],tempNode;
	tempNode = m_heap[0];
	m_heap[0] = m_heap[m_size-1];
	m_heap[m_size-1] = tempNode;
	typename vector<T>::iterator itr = m_heap.begin();
	itr = itr + m_size -1;
	m_heap.erase(itr);
	m_size--;
	int parent = 1;
	int child = parent;
	while(2*parent < m_size)
	{
		child = (true == traits::lte(m_heap[(2*parent)-1],m_heap[(2*parent)])) ? 2*parent : 2*parent + 1;
		if(false == traits::lt(m_heap[parent-1],m_heap[child-1]))
		{
			tempNode = m_heap[child -1];
			m_heap[child - 1] = m_heap[parent - 1];
			m_heap[parent - 1] = tempNode;
			parent = child;
		}
		else
			break;
	}
	return retVal;
}

template <class T, class traits>
void heap<T,traits>::decompile()
{
	for(typename vector<T>::iterator itr = m_heap.begin(); itr != m_heap.end() ;itr++) cout<< *itr <<" ";
	cout<<endl;
}

template <class T, class traits>
class heap<T*,traits>
{
	vector<T*> m_heap;
	size_t m_size;
public:
	heap()
	{
		m_size=0;
	}
	void insert(T*);
	T* extractTop();
	void decompile();
	size_t getSize()
	{return m_size;}
};

template <class T, class traits>
void heap<T*,traits>::insert(T* node)
{
	size_t parent,child;
	T* tempNode;
	m_heap.push_back(node);
	m_size++;
	child = m_size;
	parent = (child)/2;
	while((parent >=1) && (false == traits::lt(m_heap[parent-1],m_heap[child-1])))
	{
		tempNode = m_heap[child-1];
		m_heap[child-1] = m_heap[parent-1];
		m_heap[parent-1] = tempNode;
		child = parent;
		parent = parent/2;
	}
}

template <class T, class traits>
T* heap<T*,traits>::extractTop(void)
{
	T* retVal = m_heap[0],*tempNode;
	tempNode = m_heap[0];
	m_heap[0] = m_heap[m_size-1];
	m_heap[m_size-1] = tempNode;
	typename vector<T*>::iterator itr = m_heap.begin();
	itr = itr + m_size -1;
	m_heap.erase(itr);
	m_size--;
	int parent = 1;
	int child = parent;
	while(2*parent < m_size)
	{
		child = (true == traits::lte(m_heap[(2*parent)-1],m_heap[(2*parent)])) ? 2*parent : 2*parent + 1;
		if(false == traits::lt(m_heap[parent-1],m_heap[child-1]))
		{
			tempNode = m_heap[child -1];
			m_heap[child - 1] = m_heap[parent - 1];
			m_heap[parent - 1] = tempNode;
			parent = child;
		}
		else
			break;
	}
	return retVal;
}

template <class T, class traits>
void heap<T*,traits>::decompile()
{
	for(typename vector<T*>::iterator itr = m_heap.begin(); itr != m_heap.end() ;itr++) cout<< *(*itr) <<" ";
	cout<<endl;
}

#endif /* UTILS_HEAP_INCLUDE_HEAP_HPP_ */
