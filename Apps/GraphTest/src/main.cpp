/*
 * main.cpp
 *
 *  Created on: 01-Aug-2015
 *      Author: karan
 */
#include <graph.hpp>
#include <iostream>
#include <string>

using namespace std;

struct node
{
	size_t m_id;
};

struct edge
{
	node* first;
	node* second;
	size_t weight;
};

int main() {
	graph <node, edge> a;
	node first;
	first.m_id = 1;
	a.addNode(first);
	graph <node,edge>::nodeDescriptorType v = a.getNodeDescriptor();
	a[0][v].m_id = 2;
	cout<< a[0][v].m_id << endl;
	return 0;
}
