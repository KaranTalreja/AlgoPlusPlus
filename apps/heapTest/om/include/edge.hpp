/*
 * heap.hpp
 *
 *  Created on: 01-Aug-2015
 *      Author: karan
 */
#ifndef APPS_HEAPTEST_INCLUDE_EDGE_HPP_
#define APPS_HEAPTEST_INCLUDE_EDGE_HPP_

#include<heap.hpp>

template <typename keyT>
class edge : public basic_heap_node<keyT, edge<keyT> >
{
public:
	typedef keyT key_type;
	key_type weight;
	static int count;
	edge() : basic_heap_node<keyT,edge<keyT> >(&edge<keyT>::weight)
	{
		weight = count++;
	}
	friend ostream& operator << (ostream& out , edge<keyT> &a)
	{
		return out << (a.weight);
	}
};

template <typename keyT> int edge<keyT>::count = 0;

#endif /* APPS_HEAPTEST_INCLUDE_EDGE_HPP_ */
