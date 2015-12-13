/**
 *  @file GraphTest/src/main.cpp
 *
 *  Created on: 01-Aug-2015
 *  @author: Karan Talreja
 *  @details This file contains a sample testing scenario for the graph data structure. All the data structures present in the file
 *  are in a namespace called GraphTest. The test tries to instantiate graphs of various types and test basic operations
 */
#include <graph.hpp>
#include <iostream>
#include <string>

using namespace std;
/**
 * @brief GraphTest to wrap the object model specific to this testing suite.
 */
namespace GraphTest
{
/**
 * @brief Vertex OM for the graph
 * @details This class has a single member to signify the ID of the graph vertex
 */
struct node
{
	size_t m_id;	///< Member to store the ID of the graph node

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
		out << *(edgeNode.m_first) << "--";
		if (0 > edgeNode.m_weight) out << "(" << edgeNode.m_weight << ")";
		else out << edgeNode.m_weight;
		out << "-->" << *(edgeNode.m_second) << "\n";
		return out;
	}
};
}
using namespace GraphTest;

/**
 * @brief Main function to test various types of graph instantiations and basic usages.
 * @details The testing function first creates two nodes and two edges between them of both directions. The use case if the graph is similar
 * in all the scenarios where the template arguments are either pointers or non-pointers in any combination.
 * To access the vertex properties a nodeDescriptorType variable is created. This variable provides access to the nodes members. To access the
 * edges of the nodes another [] operator is written after the selected node.
 * Sample output of all test scenarios
 *
 * 1--10-->2
 * 2--(-10)-->1
 * 1 2 10 -10
 *
 */
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
	cout << b << b[1][v1].m_id <<" "<< b[2][v1].m_id <<" "<< b[1][1].m_weight <<" "<< b[2][1].m_weight << endl <<endl;

	//node pointer input template only
	graph <node*,edge> c(500);
	c[1] = &firstNode;
	c[2] = &secondNode;
	c[1].addEdge(tempEdge);
	c[2].addEdge(revTempEdge);
	using graphNodeDesc2 = graph<node*,edge>::nodeDescriptorType;
	graphNodeDesc2 v2;
	cout << c << c[1][v2].m_id <<" "<< c[2][v2].m_id <<" "<< c[1][1].m_weight <<" "<< c[2][1].m_weight << endl <<endl;

	//edge pointer input template only
	graph <node,edge*> d(500);
	d[1] = firstNode;
	d[2] = secondNode;
	d[1].addEdge(&tempEdge);
	d[2].addEdge(&revTempEdge);
	using graphNodeDesc3 = graph<node,edge*>::nodeDescriptorType;
	graphNodeDesc3 v3;
	cout << d << d[1][v3].m_id <<" "<< d[2][v3].m_id <<" "<< d[1][1].m_weight <<" "<< d[2][1].m_weight << endl <<endl;
	return 0;
}
