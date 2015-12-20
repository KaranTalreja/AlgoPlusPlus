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
	friend ostream& operator<< (ostream& out, node nodeArg)
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
	int m_weight;		///< Weight of the edge.

	///@brief Default constructor for initializing class members
	edge():m_weight(0){};

	///@brief Single argument constructor to initialize class members
	edge(int weight):m_weight(weight){};

	///@brief Friend operator << for decompiling the edge which is used from the graph decompile
	friend ostream& operator<< (ostream& out, edge edgeNode)
	{
		if (0 > edgeNode.m_weight) out << "(" << edgeNode.m_weight << ")";
		else out << " " << edgeNode.m_weight;
		return out;
	}
};
}

/**
 * @brief Main function to test various types of graph instantiations and basic usages.
 * @details The testing function first creates two nodes and two edges between them of both directions. The use case of the graph is similar
 * in all the scenarios where the template arguments are either pointers or non-pointers in any combination.
 * To access the vertex properties a nodeDescriptorType variable is created. This variable provides access to the nodes members. To access the
 * edges of the nodes another [] operator is written after the selected node.
 * Sample output of all test scenarios
 *@n
 * 1--10-->2 @n
 * 2--(-10)-->1 @n
 * 1 2 10 -10 @n
 *
 */
int main() {
	GraphTest::node firstNode(1);
	GraphTest::node secondNode(2);
	GraphTest::edge Edge(10);

	cout << "/**********************************************************/" << endl;
	cout << "/*Both non-pointer template args, bidirectional graph     */" << endl;
	cout << "/**********************************************************/" << endl;
	{
		typedef graph < GraphTest::node, GraphTest::edge, graphTraits::bidirectional> map;
		map a;
		map::vertexDescriptor v = a.addVertex(firstNode);
		map::vertexDescriptor v2 = a.addVertex(secondNode);
		a.addEdge(v,v2,Edge);
		a.setDecompileFlavor(graphTraits::AllEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::Nodes);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
	}
	cout << "/**********************************************************/" << endl;
	cout << "/*Both non-pointer template args, directed graph          */" << endl;
	cout << "/**********************************************************/" << endl;
	{
		//Both normal input templates
		typedef graph < GraphTest::node, GraphTest::edge, graphTraits::directed> map;
		map a;
		map::vertexDescriptor v = a.addVertex(firstNode);
		map::vertexDescriptor v2 = a.addVertex(secondNode);
		a.addEdge(v,v2,Edge);
		a.setDecompileFlavor(graphTraits::AllEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::InEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::OutEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::Nodes);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
	}
	cout << "/**********************************************************/" << endl;
	cout << "/*Both pointer template args, bidirectional graph         */" << endl;
	cout << "/**********************************************************/" << endl;
	{
		typedef graph < GraphTest::node*, GraphTest::edge*, graphTraits::bidirectional> map;
		map a;
		map::vertexDescriptor v = a.addVertex(&firstNode);
		map::vertexDescriptor v2 = a.addVertex(&secondNode);
		a.addEdge(v,v2,&Edge);
		a.setDecompileFlavor(graphTraits::AllEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::Nodes);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
	}
	cout << "/**********************************************************/" << endl;
	cout << "/*Both pointer template args, directed graph              */" << endl;
	cout << "/**********************************************************/" << endl;
	{
		typedef graph < GraphTest::node*, GraphTest::edge*, graphTraits::directed> map;
		map a;
		map::vertexDescriptor v = a.addVertex(&firstNode);
		map::vertexDescriptor v2 = a.addVertex(&secondNode);
		a.addEdge(v,v2,&Edge);
		a.setDecompileFlavor(graphTraits::AllEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::InEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::OutEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::Nodes);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
	}
	cout << "/**********************************************************/" << endl;
	cout << "/*Node*,Edge template args, bidirectional graph           */" << endl;
	cout << "/**********************************************************/" << endl;
	{
		typedef graph < GraphTest::node*, GraphTest::edge, graphTraits::bidirectional> map;
		map a;
		map::vertexDescriptor v = a.addVertex(&firstNode);
		map::vertexDescriptor v2 = a.addVertex(&secondNode);
		a.addEdge(v,v2,Edge);
		a.setDecompileFlavor(graphTraits::AllEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::Nodes);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
	}
	cout << "/**********************************************************/" << endl;
	cout << "/*Node*,Edge template args, directed graph                */" << endl;
	cout << "/**********************************************************/" << endl;
	{
		typedef graph < GraphTest::node*, GraphTest::edge, graphTraits::directed> map;
		map a;
		map::vertexDescriptor v = a.addVertex(&firstNode);
		map::vertexDescriptor v2 = a.addVertex(&secondNode);
		a.addEdge(v,v2,Edge);
		a.setDecompileFlavor(graphTraits::AllEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::InEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::OutEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::Nodes);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
	}
	cout << "/**********************************************************/" << endl;
	cout << "/*Node,Edge* template args, bidirectional graph           */" << endl;
	cout << "/**********************************************************/" << endl;
	{
		typedef graph < GraphTest::node, GraphTest::edge*, graphTraits::bidirectional> map;
		map a;
		map::vertexDescriptor v = a.addVertex(firstNode);
		map::vertexDescriptor v2 = a.addVertex(secondNode);
		a.addEdge(v,v2,&Edge);
		a.setDecompileFlavor(graphTraits::AllEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::Nodes);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
	}
	cout << "/**********************************************************/" << endl;
	cout << "/*Node,Edge* template args, directed graph                */" << endl;
	cout << "/**********************************************************/" << endl;
	{
		typedef graph < GraphTest::node, GraphTest::edge*, graphTraits::directed> map;
		map a;
		map::vertexDescriptor v = a.addVertex(firstNode);
		map::vertexDescriptor v2 = a.addVertex(secondNode);
		a.addEdge(v,v2,&Edge);
		a.setDecompileFlavor(graphTraits::AllEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::InEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::OutEdges);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
		a.setDecompileFlavor(graphTraits::Nodes);
		cout << "No of vertices: "<< a.size()  << endl << a <<endl;
	}

	return 0;
}
