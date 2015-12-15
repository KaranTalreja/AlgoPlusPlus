/**
 *  @file GraphRead/src/main.cpp
 *
 *  Created on: 09-Aug-2015
 *  @author: Karan Talreja
 *  @details This file contains a sample testing scenario for the graph creation after reading a file. All the data structures present in the file
 *  are in a namespace called GraphRead.
 */
#include <graph.hpp>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/**
 * @brief GraphRead to wrap the object model specific to this testing suite.
 */
namespace GraphRead
{
/**
 * @brief Vertex OM for the graph
 * @details This class has a single member to signify the ID of the graph vertex
 */
struct node
{
	size_t m_id;///< Member to store the ID of the graph node

	///@brief Default constructor for initializing class members
	node():m_id(0){};

	///@brief Single argument constructor to initialize class member m_id
	node(size_t id):m_id(id){};

	///@brief Friend operator << for decompiling the node which is used from the graph decompile
	friend ostream& operator<< (ostream& out, node& nodeArg)
	{
		out << nodeArg.m_id;
		return out;
	}
};

/**
 * @brief Edge OM for the graph
 * @details This class contains pointers to two graph nodes between which the edge is to be represented. It also has a weight member
 * to signify the weight of the edge.
 */
struct edge
{
	node* m_first;		///< Pointer to first node of the edge.
	node* m_second;		///< Pointer to second node of the edge.
	int m_weight;		///< Weight of the edge.

	///@brief Default constructor for initializing class members
	edge():m_first(NULL),m_second(NULL),m_weight(0){};

	///@brief Triple argument constructor to initialize class members
	edge(node* first, node* second, int weight):m_first(first),m_second(second),m_weight(weight){};

	///@brief Friend operator << for decompiling the edge which is used from the graph decompile
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
}
using namespace GraphRead;

/**
 * @brief Main function to test creation of graph data structure after reading a file
 * @details The testing function reads data from a file or stdin depending on the arguments passed to the binary on command line.
 * The input is considerd of the following format.@n
 * number of nodes @n
 * (Node1) (Node2) (Weight of edge between them) @n
 * .... @n
 * (NodeN) (NodeN) (Weight of edge between them) @n
 * A graph is first created for noOfNodes. Then nodes are inserted into the graph using a node descriptor and the edges are inserted into
 * nodes list using the addEdge method.
 * In the end the graph and noOfNodes are decompiled.@n
 *
 * @b Testing @b Command @n
 * make test @n
 */
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
