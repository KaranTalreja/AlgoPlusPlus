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
	node firstNode(1);
	node secondNode(2);
	edge tempEdge(&firstNode,&secondNode,10);
	edge revTempEdge(&secondNode,&firstNode,-10);

	//Both normal input templates
	graph <node,edge> a(500);
	a[1] = firstNode;
	a[2] = secondNode;
	a[1].addEdge(tempEdge);
	a[2].addEdge(revTempEdge);
	using graphNodeDesc = graph<node,edge>::nodeDescriptorType;
	graphNodeDesc v;
	cout << a << a[1][v].m_id <<" "<< a[2][v].m_id <<" "<< a[1][1].m_weight <<" "<< a[2][1].m_weight << endl <<endl;

	//Both pointer input templates
	graph <node*,edge*> b(500);
	b[1] = &firstNode;
	b[2] = &secondNode;
	b[1].addEdge(&tempEdge);
	b[2].addEdge(&revTempEdge);
	using graphNodeDesc1 = graph<node*,edge*>::nodeDescriptorType;
	graphNodeDesc1 v1;
	cout << b << b[1][v1]->m_id <<" "<< b[2][v1]->m_id <<" "<< b[1][1]->m_weight <<" "<< b[2][1]->m_weight << endl <<endl;

	//node pointer input template only
	graph <node*,edge> c(500);
	c[1] = &firstNode;
	c[2] = &secondNode;
	c[1].addEdge(tempEdge);
	c[2].addEdge(revTempEdge);
	using graphNodeDesc2 = graph<node*,edge>::nodeDescriptorType;
	graphNodeDesc2 v2;
	cout << c << c[1][v2]->m_id <<" "<< c[2][v2]->m_id <<" "<< c[1][1].m_weight <<" "<< c[2][1].m_weight << endl <<endl;

	//edge pointer input template only
	graph <node,edge*> d(500);
	d[1] = firstNode;
	d[2] = secondNode;
	d[1].addEdge(&tempEdge);
	d[2].addEdge(&revTempEdge);
	using graphNodeDesc3 = graph<node,edge*>::nodeDescriptorType;
	graphNodeDesc3 v3;
	cout << d << d[1][v3].m_id <<" "<< d[2][v3].m_id <<" "<< d[1][1]->m_weight <<" "<< d[2][1]->m_weight << endl <<endl;
	return 0;
}
