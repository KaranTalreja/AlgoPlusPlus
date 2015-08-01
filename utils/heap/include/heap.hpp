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
using namespace std;

template<class keyT, class actual_heap_node>
class basic_heap_node
{
public:
	keyT actual_heap_node::*keyAccessor;
	basic_heap_node()
	{
		keyAccessor = NULL;
	}
	basic_heap_node (keyT actual_heap_node::*thatKeyAccessor)
	{
		keyAccessor = thatKeyAccessor;
	}
	keyT applyKeyAccessor()
	{
		return (NULL != keyAccessor) ? static_cast<actual_heap_node*>(this)->*keyAccessor : keyT();
	}
};

template <class T>
class heap
{
public:
	vector<T> _heap;
	void insert (T node)
	{
		_heap.push_back(node);
	}

	void eval ()
	{
		while (!_heap.empty())
		{
			cout << _heap.back() << comp(_heap.back()) << endl;
			_heap.pop_back();
		}
	}
	bool comp(T node)
	{
		return (node.applyKeyAccessor());
	}
};

#endif /* UTILS_HEAP_INCLUDE_HEAP_HPP_ */
