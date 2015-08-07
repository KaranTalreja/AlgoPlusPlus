/*
 * graph.hpp
 *
 *  Created on: 04-Aug-2015
 *      Author: karan
 */

#ifndef UTILS_GRAPH_INCLUDE_GRAPH_HPP_
#define UTILS_GRAPH_INCLUDE_GRAPH_HPP_

#include <iostream>
#include <vector>

struct vectorStorage{};

template <typename node> class properties{};

template <typename container_type,typename valueType>class container_gen{};

template <typename valueType>
class container_gen <vectorStorage, valueType>
{
public:
	typedef std::vector<valueType> type;
};

template <typename nodeProperties, typename edgeProperties,
		  typename edgeContainer,
		  typename nodeDescriptor = properties<nodeProperties> >
class nodeWithEdges
{
public:
	nodeProperties m_nodeProperties;
	typedef typename container_gen<edgeContainer,edgeProperties>::type edgeListType;
	edgeListType m_edgeList;
	nodeWithEdges(){};
	nodeWithEdges(nodeProperties &node) {this->m_nodeProperties = node;}
	nodeProperties& operator[] (nodeDescriptor &v) {return this->m_nodeProperties;}
};

template <typename nodeProperties, typename edgeProperties,
		  typename nodeContainer = vectorStorage,
		  typename edgeContainer = vectorStorage,
		  typename nodeDescriptor = properties<nodeProperties>,
		  typename edgeDescriptor = properties<edgeProperties> >
class graph
{
public:
	typedef nodeWithEdges<nodeProperties, edgeProperties, edgeContainer> nodeType;
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListType;
	nodeListType m_nodeList;
	typedef nodeDescriptor nodeDescriptorType;
	nodeDescriptorType m_nodeDescriptor;
	nodeType &operator[](size_t idx) {return this->m_nodeList[idx];}
	void addNode (nodeProperties &node) { this->m_nodeList.push_back(nodeType(node));}
	nodeDescriptor& getNodeDescriptor () {return (this->m_nodeDescriptor);}
};

#endif /* UTILS_GRAPH_INCLUDE_GRAPH_HPP_ */
