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
	node():m_id(0){};
	node(size_t id):m_id(id){};
	friend ostream& operator<< (ostream& out, node& nodeArg)
	{
		out << nodeArg.m_id;
		return out;
	}
};

struct edge
{
	node* m_first;
	node* m_second;
	int m_weight;
	edge():m_first(NULL),m_second(NULL),m_weight(0){};
	edge(node* first, node* second, int weight):m_first(first),m_second(second),m_weight(weight){};
	friend ostream& operator<< (ostream& out, edge& edgeNode)
	{
		out << *(edgeNode.m_first) << "--";
		if (0 > edgeNode.m_weight) out << "(" << edgeNode.m_weight << ")";
		else out << edgeNode.m_weight;
		out << "-->" << *(edgeNode.m_second) << "\n";
		return out;
	}
};

int main() {
	graph <node,edge> a(500);
	node firstNode(1);
	node secondNode(2);
	edge tempEdge(&firstNode,&secondNode,10);
	edge revTempEdge(&secondNode,&firstNode,-10);
	a[1] = firstNode;
	a[2] = secondNode;
	a[1].addEdge(tempEdge);
	a[2].addEdge(revTempEdge);
	using graphNodeDesc = graph<node,edge>::nodeDescriptorType;
	graphNodeDesc v;
	cout << a << endl << a[1][v].m_id <<" "<< a[2][v].m_id <<" "<< a[1][1].m_weight <<" "<< a[2][1].m_weight << endl;
	return 0;
}
