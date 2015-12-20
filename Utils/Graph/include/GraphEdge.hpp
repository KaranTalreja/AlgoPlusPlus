/**
 * @file GraphEdge.hpp
 *
 *  Created on: 19-Dec-2015
 *  @author: Karan Talreja
 *  @details This file contains the templated code of edge used in #graph .
 */

#ifndef UTILS_GRAPH_INCLUDE_GRAPHEDGE_HPP_
#define UTILS_GRAPH_INCLUDE_GRAPHEDGE_HPP_

#include "GraphTraits.hpp"

template<typename nodeProperties, typename edgeProperties, typename edgeContainer>
class edge <nodeProperties, edgeProperties, graphTraits::directed, edgeContainer> : public edgeProperties
{
	typedef vertex<nodeProperties,edgeProperties,graphTraits::directed, edgeContainer> nodeType;
	typedef edge <nodeProperties, edgeProperties, graphTraits::directed, edgeContainer> thisClass;
public:
	nodeType* source;
	nodeType* sink;
	edge() : source(NULL),sink(NULL){}
	edge(nodeType *source, nodeType *sink, edgeProperties& e) : edgeProperties(e),source(source),sink(sink){}

	friend ostream& operator << (ostream &out, thisClass& e)
	{
		out << *e.source << edgeProperties(e) << *e.sink;
		return out;
	}
};

template<typename nodeProperties, typename edgeProperties, typename edgeContainer>
class edge <nodeProperties*, edgeProperties*, graphTraits::directed, edgeContainer> : public edgeProperties
{
	typedef vertex<nodeProperties*,edgeProperties*,graphTraits::directed, edgeContainer> nodeType;
	typedef edge <nodeProperties*, edgeProperties*, graphTraits::directed, edgeContainer> thisClass;
public:
	nodeType* source;
	nodeType* sink;
	edge() : source(NULL),sink(NULL){}
	edge(nodeType *source, nodeType *sink, edgeProperties *e) : edgeProperties(*e),source(source),sink(sink){}

	friend ostream& operator << (ostream &out, thisClass& e)
	{
		out << *e.source << edgeProperties(e) << *e.sink;
		return out;
	}
};

template<typename nodeProperties, typename edgeProperties, typename edgeContainer>
class edge <nodeProperties*, edgeProperties, graphTraits::directed, edgeContainer> : public edgeProperties
{
	typedef vertex<nodeProperties*,edgeProperties,graphTraits::directed, edgeContainer> nodeType;
	typedef edge <nodeProperties*, edgeProperties, graphTraits::directed, edgeContainer> thisClass;
public:
	nodeType* source;
	nodeType* sink;
	edge() : source(NULL),sink(NULL){}
	edge(nodeType *source, nodeType *sink, edgeProperties& e) : edgeProperties(e),source(source),sink(sink){}

	friend ostream& operator << (ostream &out, thisClass& e)
	{
		out << *e.source << edgeProperties(e) << *e.sink;
		return out;
	}
};

template<typename nodeProperties, typename edgeProperties, typename edgeContainer>
class edge <nodeProperties, edgeProperties*, graphTraits::directed, edgeContainer> : public edgeProperties
{
	typedef vertex<nodeProperties,edgeProperties*,graphTraits::directed, edgeContainer> nodeType;
	typedef edge <nodeProperties, edgeProperties*, graphTraits::directed, edgeContainer> thisClass;
public:
	nodeType* source;
	nodeType* sink;
	edge() : source(NULL),sink(NULL){}
	edge(nodeType *source, nodeType *sink, edgeProperties *e) : edgeProperties(*e),source(source),sink(sink){}

	friend ostream& operator << (ostream &out, thisClass& e)
	{
		out << *e.source << edgeProperties(e) << *e.sink;
		return out;
	}
};

template<typename nodeProperties, typename edgeProperties, typename edgeContainer>
class edge <nodeProperties, edgeProperties, graphTraits::bidirectional, edgeContainer> : public edgeProperties
{
	typedef vertex<nodeProperties,edgeProperties,graphTraits::bidirectional, edgeContainer> nodeType;
	typedef edge <nodeProperties, edgeProperties, graphTraits::bidirectional, edgeContainer> thisClass;
public:
	nodeType* source;
	nodeType* sink;
	edge():source(NULL),sink(NULL){}
	edge(nodeType *source, nodeType *sink, edgeProperties& e) : edgeProperties(e),source(source),sink(sink){}

	friend ostream& operator<< (ostream &out, thisClass& e)
	{
		out << *e.source << edgeProperties(e) << *e.sink;
		return out;
	}
};

template<typename nodeProperties, typename edgeProperties, typename edgeContainer>
class edge <nodeProperties*, edgeProperties*, graphTraits::bidirectional, edgeContainer> : public edgeProperties
{
	typedef vertex<nodeProperties*,edgeProperties*,graphTraits::bidirectional, edgeContainer> nodeType;
	typedef edge <nodeProperties*, edgeProperties*, graphTraits::bidirectional, edgeContainer> thisClass;
public:
	nodeType* source;
	nodeType* sink;
	edge():source(NULL),sink(NULL){}
	edge(nodeType *source, nodeType *sink, edgeProperties *e) : edgeProperties(*e),source(source),sink(sink){}

	friend ostream& operator<< (ostream &out, thisClass& e)
	{
		out << *e.source << edgeProperties(e) << *e.sink;
		return out;
	}
};

template<typename nodeProperties, typename edgeProperties, typename edgeContainer>
class edge <nodeProperties*, edgeProperties, graphTraits::bidirectional, edgeContainer> : public edgeProperties
{
	typedef vertex<nodeProperties*,edgeProperties,graphTraits::bidirectional, edgeContainer> nodeType;
	typedef edge <nodeProperties*, edgeProperties, graphTraits::bidirectional, edgeContainer> thisClass;
public:
	nodeType* source;
	nodeType* sink;
	edge():source(NULL),sink(NULL){}
	edge(nodeType *source, nodeType *sink, edgeProperties& e) : edgeProperties(e),source(source),sink(sink){}

	friend ostream& operator<< (ostream &out, thisClass& e)
	{
		out << *e.source << edgeProperties(e) << *e.sink;
		return out;
	}
};

template<typename nodeProperties, typename edgeProperties, typename edgeContainer>
class edge <nodeProperties, edgeProperties*, graphTraits::bidirectional, edgeContainer> : public edgeProperties
{
	typedef vertex<nodeProperties,edgeProperties*,graphTraits::bidirectional, edgeContainer> nodeType;
	typedef edge <nodeProperties, edgeProperties*, graphTraits::bidirectional, edgeContainer> thisClass;
public:
	nodeType* source;
	nodeType* sink;
	edge():source(NULL),sink(NULL){}
	edge(nodeType *source, nodeType *sink, edgeProperties *e) : edgeProperties(*e),source(source),sink(sink){}

	friend ostream& operator<< (ostream &out, thisClass& e)
	{
		out << *e.source << edgeProperties(e) << *e.sink;
		return out;
	}
};
#endif /* UTILS_GRAPH_INCLUDE_GRAPHEDGE_HPP_ */
