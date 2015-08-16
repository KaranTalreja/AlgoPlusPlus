/*
 * main.cpp
 *
 *  Created on: 09-Aug-2015
 *      Author: karan
 */

#include <graph.hpp>
#include <iostream>
#include <string>
#include <fstream>

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
		out << *(edgeNode.m_first) << " ";
		out << *(edgeNode.m_second) << " " ;
		if (0 > edgeNode.m_weight) out << "(" << edgeNode.m_weight << ")";
		else out << edgeNode.m_weight;
		cout << "\n";
		return out;
	}
};

int main(int argc , char* argv[])
{
	ifstream *infile = NULL;;
	if (1 == argc) infile = new ifstream("/dev/stdin");
	else infile = new ifstream(argv[1]);
	int noOfNodes;
	*infile >> noOfNodes;
	graph<node*,edge*> Graph(noOfNodes);
	size_t tempNodeStartVal,tempNodeEndVal;
	int tempWeight;
	using graphNodeDesc = graph<node*,edge*>::nodeDescriptorType;
	graphNodeDesc v;
	while (*infile >> tempNodeStartVal >> tempNodeEndVal >> tempWeight)
	{
		edge *tempEdge;
		node *tempNodeStart,*tempNodeEnd;
		tempNodeStart = (NULL == &Graph[tempNodeStartVal][v]) ? new node(tempNodeStartVal) : &Graph[tempNodeStartVal][v];
		tempNodeEnd = (NULL == &Graph[tempNodeEndVal][v]) ? new node(tempNodeEndVal) : &Graph[tempNodeEndVal][v];
		tempEdge = new edge(tempNodeStart,tempNodeEnd,tempWeight);
		if (NULL == &Graph[tempNodeStartVal][v]) Graph[tempNodeStartVal] = tempNodeStart;
		if (NULL == &Graph[tempNodeEndVal][v]) Graph[tempNodeEndVal] = tempNodeEnd;
		Graph[tempNodeStartVal].addEdge(tempEdge);
	}
	cout << noOfNodes <<endl <<Graph;
	return 0;
}
