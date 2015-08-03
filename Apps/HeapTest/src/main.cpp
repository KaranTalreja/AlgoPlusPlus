/*
 * main.cpp
 *
 *  Created on: 01-Aug-2015
 *      Author: karan
 */
#include <heap.hpp>
#include <type_traits>

class heapNode
{
	int weight;
public:
	static int getKey(heapNode& a) {return a.weight;}
	friend ostream& operator << (ostream& out, heapNode& a) { return out << a.weight;}
	heapNode(){weight = 0;}
	heapNode(int n) {weight = n;}
};

int main()
{
	heap<size_t*,basic_heap_max_traits<size_t*> > a;
	for (size_t i = 1; i <= 10 ; i++) a.insert(new size_t(i));
	a.decompile();
	a.extractTop();
	a.decompile();
	a.insert(new size_t(1));
	a.decompile();

	heap<heapNode*,basic_heap_max_traits<heapNode*> > aNf1;
	for (int i = 1; i <= 10 ; i++) aNf1.insert(new heapNode(i));
	aNf1.decompile();
	aNf1.extractTop();
	aNf1.decompile();
	aNf1.insert(new heapNode(1));
	aNf1.decompile();

	heap<heapNode,basic_heap_max_traits<heapNode> > aNf;
	for (int i = 1; i <= 10 ; i++) aNf.insert(*new heapNode(i));
	aNf.decompile();
	aNf.extractTop();
	aNf.decompile();
	aNf.insert(*new heapNode(1));
	aNf.decompile();
	return 0;
}
