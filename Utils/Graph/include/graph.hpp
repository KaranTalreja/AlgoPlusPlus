/**
 *  @file graph.cpp
 *
 *  Created on: 04-Aug-2015
 *  @author: Karan Talreja
 *  @details This file contains implementation of graph data structure.
 */
#ifndef UTILS_GRAPH_INCLUDE_GRAPH_HPP_
#define UTILS_GRAPH_INCLUDE_GRAPH_HPP_

#include <iostream>
#include <vector>

using namespace std;

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
		  typename nodeDescriptor = properties<nodeProperties>,
		  typename edgeDescriptor = properties<edgeProperties> >
class nodeWithEdges
{
public:
	nodeProperties m_nodeProperties;
	typedef typename container_gen<edgeContainer,edgeProperties>::type edgeListType;
	edgeListType m_edgeList;
	typedef nodeDescriptor nodeDescriptorType;
	nodeDescriptorType m_nodeDescriptor;
	typedef edgeDescriptor edgeDescriptorType;
	edgeDescriptorType m_edgeDescriptor;
	nodeWithEdges():m_edgeList(0){};
	nodeWithEdges(nodeProperties &node):m_edgeList(0) {this->m_nodeProperties = node;}
	nodeProperties& operator[] (nodeDescriptor &v) {return this->m_nodeProperties;}
	edgeProperties& operator[] (size_t edgeIdx) {return this->m_edgeList[edgeIdx-1];}
	nodeDescriptor& getNodeDescriptor () {return (this->m_nodeDescriptor);}
	edgeDescriptor& getEdgeDescriptor () {return (this->m_edgeDescriptor);}
	void addEdge(edgeProperties& edge) {this->m_edgeList.push_back(edge);}
	friend ostream& operator << (ostream& out, nodeWithEdges& node)
	{
		typename edgeListType::iterator edgeItr;
		for (edgeItr = node.m_edgeList.begin(); edgeItr != node.m_edgeList.end() ; edgeItr++) out << *(edgeItr);
		return out;
	}
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
	typedef edgeDescriptor edgeDescriptorType;
	graph(){};
	graph(size_t noOfNodes) : m_nodeList(noOfNodes){};
	nodeType &operator[](size_t idx) {return this->m_nodeList[idx-1];}
	friend ostream& operator<< (ostream& out, graph& graphInst)
	{
		typename nodeListType::iterator nodeItr;
		for (nodeItr = graphInst.m_nodeList.begin(); nodeItr != graphInst.m_nodeList.end() ;nodeItr++) out << *(nodeItr);
		return out;
	}
};

template <typename nodeProperties, typename edgeProperties,
		  typename edgeContainer,
		  typename nodeDescriptor,
		  typename edgeDescriptor>
class nodeWithEdges <nodeProperties*, edgeProperties*, edgeContainer, nodeDescriptor, edgeDescriptor>
{
public:
	nodeProperties *m_nodeProperties;
	typedef typename container_gen<edgeContainer,edgeProperties*>::type edgeListType;
	edgeListType m_edgeList;
	typedef nodeDescriptor nodeDescriptorType;
	nodeDescriptorType m_nodeDescriptor;
	typedef edgeDescriptor edgeDescriptorType;
	edgeDescriptorType m_edgeDescriptor;
	nodeWithEdges():m_nodeProperties(NULL),m_edgeList(0){};
	nodeWithEdges(nodeProperties* node):m_edgeList(0) {this->m_nodeProperties = node;}
	nodeProperties& operator[] (nodeDescriptor &v) {return *(this->m_nodeProperties);}
	edgeProperties& operator[] (size_t edgeIdx) {return *(this->m_edgeList[edgeIdx-1]);}
	nodeDescriptor& getNodeDescriptor () {return (this->m_nodeDescriptor);}
	edgeDescriptor& getEdgeDescriptor () {return (this->m_edgeDescriptor);}
	void addEdge(edgeProperties* edge) {this->m_edgeList.push_back(edge);}
	friend ostream& operator << (ostream& out, nodeWithEdges& node)
	{
		typename edgeListType::iterator edgeItr;
		for (edgeItr = node.m_edgeList.begin(); edgeItr != node.m_edgeList.end() ; edgeItr++) out << *(*(edgeItr));
		return out;
	}
};

template <typename nodeProperties, typename edgeProperties, typename nodeContainer ,
		  typename edgeContainer ,typename nodeDescriptor,typename edgeDescriptor >
class graph<nodeProperties*, edgeProperties*, nodeContainer, edgeContainer, nodeDescriptor, edgeDescriptor>
{
public:
	typedef nodeWithEdges<nodeProperties*, edgeProperties*, edgeContainer> nodeType;
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListType;
	nodeListType m_nodeList;
	typedef nodeDescriptor nodeDescriptorType;
	typedef edgeDescriptor edgeDescriptorType;
	graph(){};
	graph(size_t noOfNodes) : m_nodeList(noOfNodes){};
	nodeType& operator[](size_t idx) {return this->m_nodeList[idx-1];}
	friend ostream& operator<< (ostream& out, graph& graphInst)
	{
		typename nodeListType::iterator nodeItr;
		for (nodeItr = graphInst.m_nodeList.begin(); nodeItr != graphInst.m_nodeList.end() ;nodeItr++) out << *(nodeItr);
		return out;
	}
};

template <typename nodeProperties, typename edgeProperties,
		  typename edgeContainer,
		  typename nodeDescriptor,
		  typename edgeDescriptor>
class nodeWithEdges <nodeProperties*, edgeProperties, edgeContainer, nodeDescriptor, edgeDescriptor>
{
public:
	nodeProperties *m_nodeProperties;
	typedef typename container_gen<edgeContainer,edgeProperties>::type edgeListType;
	edgeListType m_edgeList;
	typedef nodeDescriptor nodeDescriptorType;
	nodeDescriptorType m_nodeDescriptor;
	typedef edgeDescriptor edgeDescriptorType;
	edgeDescriptorType m_edgeDescriptor;
	nodeWithEdges():m_nodeProperties(NULL),m_edgeList(0){};
	nodeWithEdges(nodeProperties* node):m_edgeList(0) {this->m_nodeProperties = node;}
	nodeProperties& operator[] (nodeDescriptor &v) {return *(this->m_nodeProperties);}
	edgeProperties& operator[] (size_t edgeIdx) {return this->m_edgeList[edgeIdx-1];}
	nodeDescriptor& getNodeDescriptor () {return (this->m_nodeDescriptor);}
	edgeDescriptor& getEdgeDescriptor () {return (this->m_edgeDescriptor);}
	void addEdge(edgeProperties &edge) {this->m_edgeList.push_back(edge);}
	friend ostream& operator << (ostream& out, nodeWithEdges& node)
	{
		typename edgeListType::iterator edgeItr;
		for (edgeItr = node.m_edgeList.begin(); edgeItr != node.m_edgeList.end() ; edgeItr++) out << *(edgeItr);
		return out;
	}
};

template <typename nodeProperties, typename edgeProperties, typename nodeContainer ,
		  typename edgeContainer ,typename nodeDescriptor,typename edgeDescriptor >
class graph<nodeProperties*, edgeProperties, nodeContainer, edgeContainer, nodeDescriptor, edgeDescriptor>
{
public:
	typedef nodeWithEdges<nodeProperties*, edgeProperties, edgeContainer> nodeType;
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListType;
	nodeListType m_nodeList;
	typedef nodeDescriptor nodeDescriptorType;
	typedef edgeDescriptor edgeDescriptorType;
	graph(){};
	graph(size_t noOfNodes) : m_nodeList(noOfNodes){};
	nodeType& operator[](size_t idx) {return this->m_nodeList[idx-1];}
	friend ostream& operator<< (ostream& out, graph& graphInst)
	{
		typename nodeListType::iterator nodeItr;
		for (nodeItr = graphInst.m_nodeList.begin(); nodeItr != graphInst.m_nodeList.end() ;nodeItr++) out << *(nodeItr);
		return out;
	}
};

template <typename nodeProperties, typename edgeProperties,
		  typename edgeContainer,
		  typename nodeDescriptor,
		  typename edgeDescriptor>
class nodeWithEdges <nodeProperties, edgeProperties*, edgeContainer, nodeDescriptor, edgeDescriptor>
{
public:
	nodeProperties m_nodeProperties;
	typedef typename container_gen<edgeContainer,edgeProperties*>::type edgeListType;
	edgeListType m_edgeList;
	typedef nodeDescriptor nodeDescriptorType;
	nodeDescriptorType m_nodeDescriptor;
	typedef edgeDescriptor edgeDescriptorType;
	edgeDescriptorType m_edgeDescriptor;
	nodeWithEdges():m_edgeList(0){};
	nodeWithEdges(nodeProperties &node):m_edgeList(0) {this->m_nodeProperties = node;}
	nodeProperties& operator[] (nodeDescriptor &v) {return this->m_nodeProperties;}
	edgeProperties& operator[] (size_t edgeIdx) {return *(this->m_edgeList[edgeIdx-1]);}
	nodeDescriptor& getNodeDescriptor () {return (this->m_nodeDescriptor);}
	edgeDescriptor& getEdgeDescriptor () {return (this->m_edgeDescriptor);}
	void addEdge(edgeProperties* edge) {this->m_edgeList.push_back(edge);}
	friend ostream& operator << (ostream& out, nodeWithEdges& node)
	{
		typename edgeListType::iterator edgeItr;
		for (edgeItr = node.m_edgeList.begin(); edgeItr != node.m_edgeList.end() ; edgeItr++) out << *(*(edgeItr));
		return out;
	}
};

template <typename nodeProperties, typename edgeProperties, typename nodeContainer ,
		  typename edgeContainer ,typename nodeDescriptor,typename edgeDescriptor >
class graph<nodeProperties, edgeProperties*, nodeContainer, edgeContainer, nodeDescriptor, edgeDescriptor>
{
public:
	typedef nodeWithEdges<nodeProperties, edgeProperties*, edgeContainer> nodeType;
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListType;
	nodeListType m_nodeList;
	typedef nodeDescriptor nodeDescriptorType;
	typedef edgeDescriptor edgeDescriptorType;
	graph(){};
	graph(size_t noOfNodes) : m_nodeList(noOfNodes){};
	nodeType& operator[](size_t idx) {return this->m_nodeList[idx-1];}
	friend ostream& operator<< (ostream& out, graph& graphInst)
	{
		typename nodeListType::iterator nodeItr;
		for (nodeItr = graphInst.m_nodeList.begin(); nodeItr != graphInst.m_nodeList.end() ;nodeItr++) out << *(nodeItr);
		return out;
	}
};
#endif /* UTILS_GRAPH_INCLUDE_GRAPH_HPP_ */
