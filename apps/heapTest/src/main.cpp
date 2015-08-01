/*
 * main.cpp
 *
 *  Created on: 01-Aug-2015
 *      Author: karan
 */
#include <heap.hpp>
#include <edge.hpp>

int main()
{
	heap <edge<size_t> > b;
	b.insert(*(new edge<size_t>()));
	b.insert(*(new edge<size_t>()));
	b.eval();
	heap <edge<int> > c;
	c.insert(*(new edge<int>()));
	c.insert(*(new edge<int>()));
	c.eval();
	return 0;
}
