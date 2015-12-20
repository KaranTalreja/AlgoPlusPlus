/**
 *  @file Clustering/src/main.cpp
 *
 *  Created on: 16-Aug-2015
 *  @author: Karan Talreja
 *  @details This file contains Clustering application. All the data structures present in the file
 *  are in a namespace called Clustering.
 */
#include <graph.hpp>
#include <UnionFind.hpp>
#include <heap.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

/**
 * @brief Clustering to wrap the object model specific to this testing suite.
 */
namespace Clustering
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
	int m_weight;		///< Weight of the edge.
	typedef UnionFind<Clustering::node*>::nodeDescriptor* nodeType;
	nodeType first;
	nodeType second;

	///@brief Default constructor for initializing class members
	edge():m_weight(0),first(NULL),second(NULL){};

	///@brief Triple argument constructor to initialize class members
	edge(int weight, nodeType first, nodeType second):m_weight(weight),first(first),second(second){};

	static int getKey(edge &that) { return that.m_weight; }

	///@brief Friend operator << for decompiling the edge which is used from the graph decompile
	friend ostream& operator<< (ostream& out, edge& edgeNode)
	{
		if (0 > edgeNode.m_weight) out << "(" << edgeNode.m_weight << ")";
		else out << " "<<edgeNode.m_weight;
		return out;
	}
};
}
/**
 * @brief Main function to test
 * @details The testing function
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
	typedef UnionFind<Clustering::node*> UF;
	typedef heap<Clustering::edge*,basic_heap_min_traits<Clustering::edge*> > Heap;
	std::vector <UF::nodeDescriptor*> idToDescriptorMap(noOfNodes);
	size_t tempNodeStartVal,tempNodeEndVal;
	int tempWeight;
	UF u;
	Heap h;
	Clustering::edge *tempEdge;
	while (*infile >> tempNodeStartVal >> tempNodeEndVal >> tempWeight)
	{

		Clustering::node *tempNodeStart,*tempNodeEnd;
		tempNodeStart = (NULL == idToDescriptorMap[tempNodeStartVal-1]) ? new Clustering::node(tempNodeStartVal) : u[*(idToDescriptorMap[tempNodeStartVal-1])];
		tempNodeEnd = (NULL == idToDescriptorMap[tempNodeEndVal-1]) ? new Clustering::node(tempNodeEndVal) : u[*(idToDescriptorMap[tempNodeEndVal-1])];
		if (NULL == idToDescriptorMap[tempNodeStartVal-1]) idToDescriptorMap[tempNodeStartVal-1] = new UF::nodeDescriptor(u.addNode(tempNodeStart));
		if (NULL == idToDescriptorMap[tempNodeEndVal-1]) idToDescriptorMap[tempNodeEndVal-1] = new UF::nodeDescriptor(u.addNode(tempNodeEnd));
		(*idToDescriptorMap[tempNodeStartVal-1])->setLeader(idToDescriptorMap[tempNodeStartVal-1]);
		(*idToDescriptorMap[tempNodeEndVal-1])->setLeader(idToDescriptorMap[tempNodeEndVal-1]);
		tempEdge = new Clustering::edge(tempWeight,idToDescriptorMap[tempNodeStartVal-1],idToDescriptorMap[tempNodeEndVal-1]);
		h.insert(tempEdge);
	}
	int noOfClusters = noOfNodes;
	int requiredClusters = 4;
	while(noOfClusters != requiredClusters)
	{
		tempEdge = h.extractTop();
		UF::nodeDescriptor* firstLeader = u.Find(tempEdge->first);
		UF::nodeDescriptor* secondLeader = u.Find(tempEdge->second);
		if(firstLeader != secondLeader)
		{
			u.Union(firstLeader,secondLeader);
			noOfClusters --;
		}
		delete tempEdge;
	}
	int maxSpacing;
	while(1)
	{
		tempEdge = h.extractTop();
		if(u.Find(tempEdge->first) != u.Find(tempEdge->second))
		{
			maxSpacing = tempEdge->m_weight;
			delete tempEdge;
			break;
		}
		delete tempEdge;
	}
	cout << maxSpacing << endl;
	return 0;
}
