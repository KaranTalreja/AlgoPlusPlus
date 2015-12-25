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

/**
 * @brief [General Template]: Class to specify the edge type used in #graph
 * @tparam	nodeProperties	The properties of the user defined node to be encapsulated in the graph #vertex
 * @tparam	edgeProperties	The properties of the user defined edge to be encapsulated in the graph #edge
 * @tparam	graphType		To specify whether a graph is #graphTraits::directed or #graphTraits::bidirectional
 * @tparam	edgeContainer	To specify the type of storage which is to be used for the edge. #graphTraits::listStorage or #graphTraits::vectorStorage@n
 * @details This class encapsulates the user defined edgeProperties as a member variable. Also it adds to it the source and sink
 * properties of the vertices in the graph between which this edge is created.@n
 * @b Specializations @b available: @n
 * #edge<nodeProperties*, edgeProperties*,graphType, edgeContainer>	// Both node and edge of pointer types @n
 * #edge<nodeProperties*, edgeProperties,graphType, edgeContainer>	// Node of pointer type @n
 * #edge<nodeProperties, edgeProperties*,graphType, edgeContainer>	// Edge of pointer type @n
 */
template<typename nodeProperties, typename edgeProperties, typename graphType, typename edgeContainer>
class edge
{
public:
	typedef edge <nodeProperties, edgeProperties,graphType, edgeContainer> thisClass; ///< Member type to describe this class type
	typedef vertex<nodeProperties,edgeProperties,graphType, edgeContainer> nodeType;  ///< Member type to describe vertex type used by this class
	nodeType* source; 	///< Member variable which is the source of this edge
	nodeType* sink;		///< Member variable which is the sink of this edge
	edgeProperties internalProperties;		///< Member of user defined edgeProperties to be encapsulated in this class
	///@brief Default Constructor
	edge() : source(NULL),sink(NULL){}
	///@brief Triple Argument Constructor
	edge(nodeType *source, nodeType *sink, edgeProperties& e) :source(source),sink(sink), internalProperties(e){}
	/**
	 * @brief Decompilation support provided to be used by classes which have nodes of this class type.
	 * @param	out	ostream variable in which the output is piped.
	 * @param	e	variable of this class type which is to be decompiled
	 * @return Reference to out input argument with filled decompilation data of the input object
	 */
	friend ostream& operator << (ostream &out, thisClass& e)
	{
		out << *e.source << edgeProperties(e.internalProperties) << *e.sink;
		return out;
	}
};

/**
 * @brief [Partial Specialization]: #edge which uses node and edge properties of pointer types
 * @details @copydetails edge
 */
template<typename nodeProperties, typename edgeProperties, typename graphType, typename edgeContainer>
class edge<nodeProperties*, edgeProperties*,graphType, edgeContainer>
{
public:
	typedef edge <nodeProperties*, edgeProperties*, graphType, edgeContainer> thisClass;	///<@copybrief edge::thisClass
	typedef vertex<nodeProperties*, edgeProperties*, graphType, edgeContainer> nodeType;	///<@copybrief edge::nodeType
	nodeType* source;	///<@copybrief edge::source
	nodeType* sink;	///<@copybrief edge::sink
	edgeProperties *internalProperties;	///<@copybrief edge::internalProperties
	edge() : source(NULL),sink(NULL),internalProperties(NULL){}	///<@copybrief edge::edge
	edge(nodeType *source, nodeType *sink, edgeProperties *e) :source(source),sink(sink), internalProperties(e){}	///<@copybrief edge::edge(nodeType *source, nodeType *sink, edgeProperties& e)
	///@brief Type cast operator to user defined encapsulated type
	operator edgeProperties* () { return internalProperties; }
	///@copydoc edge::operator <<
	friend ostream& operator << (ostream &out, thisClass& e)
	{
		out << *e.source << edgeProperties(*e.internalProperties) << *e.sink;
		return out;
	}
};

/**
 * @brief [Partial Specialization]: #edge which uses node properties of pointer type
 * @details @copydetails edge
 */
template<typename nodeProperties, typename edgeProperties, typename graphType, typename edgeContainer>
class edge<nodeProperties*, edgeProperties,graphType, edgeContainer>
{
public:
	typedef edge <nodeProperties*, edgeProperties,graphType, edgeContainer> thisClass;	///<@copybrief edge::thisClass
	typedef vertex<nodeProperties*, edgeProperties,graphType, edgeContainer> nodeType;	///<@copybrief edge::nodeType
	nodeType* source;	///<@copybrief edge::source
	nodeType* sink;	///<@copybrief edge::sink
	edgeProperties internalProperties;	///<@copybrief edge::internalProperties
	edge() : source(NULL),sink(NULL){}	///<@copybrief edge::edge
	edge(nodeType *source, nodeType *sink, edgeProperties& e) : source(source),sink(sink), internalProperties(e){}	///<@copybrief edge::edge(nodeType *source, nodeType *sink, edgeProperties& e)
	///@copydoc edge::operator <<
	friend ostream& operator << (ostream &out, thisClass& e)
	{
		out << *e.source << edgeProperties(e.internalProperties) << *e.sink;
		return out;
	}
};

/**
 * @brief [Partial Specialization]: #edge which uses edge properties of pointer types
 * @details @copydetails edge
 */
template<typename nodeProperties, typename edgeProperties, typename graphType, typename edgeContainer>
class edge<nodeProperties, edgeProperties*,graphType, edgeContainer>
{
public:
	typedef edge <nodeProperties, edgeProperties*, graphType, edgeContainer> thisClass;	///<@copybrief edge::thisClass
	typedef vertex<nodeProperties,edgeProperties*, graphType, edgeContainer> nodeType;	///<@copybrief edge::nodeType
	nodeType* source;	///<@copybrief edge::source
	nodeType* sink;	///<@copybrief edge::sink
	edgeProperties *internalProperties;	///<@copybrief edge::internalProperties
	edge() : source(NULL),sink(NULL),internalProperties(NULL){}	///<@copybrief edge::edge
	edge(nodeType *source, nodeType *sink, edgeProperties *e) : source(source),sink(sink), internalProperties(e){}	///<@copybrief edge::edge(nodeType *source, nodeType *sink, edgeProperties& e)
	///@brief Type cast operator to user defined encapsulated type
	operator edgeProperties* () { return internalProperties; }
	///@copydoc edge::operator <<
	friend ostream& operator << (ostream &out, thisClass& e)
	{
		out << *e.source << edgeProperties(*e.internalProperties) << *e.sink;
		return out;
	}
};

#endif /* UTILS_GRAPH_INCLUDE_GRAPHEDGE_HPP_ */
