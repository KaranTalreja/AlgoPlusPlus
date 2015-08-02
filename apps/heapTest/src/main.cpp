/*
 * main.cpp
 *
 *  Created on: 01-Aug-2015
 *      Author: karan
 */
#include <heap.hpp>
#include <type_traits>

int main()
{
	heap<size_t,basic_heap_min_traits<size_t> > a;
	for (size_t i = 1; i <= 10 ; i++) a.insert(i);
	a.decompile();
	a.extractTop();
	a.decompile();
	a.insert(1);
	a.decompile();
	return 0;
}
