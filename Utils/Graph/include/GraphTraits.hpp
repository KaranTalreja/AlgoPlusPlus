/**
 * @file GraphTraits.hpp
 *
 *  Created on: 19-Dec-2015
 * @author Karan Talreja
 */

#ifndef UTILS_GRAPH_INCLUDE_GRAPHTRAITS_HPP_
#define UTILS_GRAPH_INCLUDE_GRAPHTRAITS_HPP_

#include <iostream>

using namespace std;

///@brief Class to contains basic types used in #graph
class graphTraits
{
public:
	///@brief Type to specify a bidirectional #graph
	typedef struct {} bidirectional;
	///@brief Type to specify a directed #graph
	typedef struct {} directed;
	///@brief Type to specify different decompile flavors of the #graph
	typedef enum
	{
			Nodes,		///< Type to specify node-only decompile of a graph
			AllEdges,	///< Type to specify all-edge decompile of a graph
			InEdges,	///< Type to specify only In-edge decompile of a graph
			OutEdges	///< Type to specify only Out-edge decompile of a graph
	} decompileFlavor;

	///@brief Type to specify a std::vector storage
	typedef struct {} vectorStorage;
	///@brief Type to specify a std::list storage
	typedef struct {} listStorage;

};

/**
 * @brief [General Template]: #container_gen used to create containers to be used in #graph.
 * @tparam	container_type	Type of container to be used.
 * @tparam	valueType		Type of value which is to be stored in the container.
 * @details This class is partially specialized on the basis of containers which are to be used for node or edge container memory.@n
 * @b Specialization @b available @n
 * #container_gen<graphTraits::vectorStorage,valueType>	//#graphTraits::vectorStorage used to generate container@n
 * #container_gen<graphTraits::listStorage,valueType>	//#graphTraits::listStorage used to generate container@n
 */
template <typename container_type,typename valueType>class container_gen{};

/**
 * @brief [Partial Specialization]: #container_gen to create a container using std::vector
 * @tparam	valueType	Type of nodes which are to be stored in std::vector
 * @details This partially specialized template class behaves as a wrapper to define a typedef #type which will be used in #graph.
 * This typedef is used in #graph to generate a memory container of type std::vector. Using this template helps to write general #graph
 * implementation templates.
 */
template <typename valueType>
class container_gen <graphTraits::vectorStorage, valueType>
{
public:
	typedef std::vector<valueType> type;	///< Typedef with standard name #type to be used in #graph
};

/**
 * @brief [Partial Specialization]: #container_gen to create a container using std::list
 * @tparam	valueType	Type of nodes which are to be stored in std::list
 * @details This partially specialized template class behaves as a wrapper to define a typedef #type which will be used in #graph.
 * This typedef is used in #graph to generate a memory container of type std::list. Using this template helps to write general #graph
 * implementation templates.
 */
template <typename valueType>
class container_gen <graphTraits::listStorage, valueType>
{
public:
	typedef std::list<valueType> type;	///< Typedef with standard name #type to be used in #graph
};

/**
 * @brief [General Template]: Class to specify the vertex type used in #graph
 * @tparam	nodeProperties	The properties of the user defined node to be encapsulated in the graph #vertex
 * @tparam	edgeProperties	The properties of the user defined edge to be encapsulated in the graph #edge
 * @tparam	graphType		To specify whether a graph is #graphTraits::directed or #graphTraits::bidirectional
 * @tparam	edgeContainer	To specify the type of storage which is to be used for the #edge. #graphTraits::listStorage or #graphTraits::vectorStorage@n
 * @details
 * @b Specializations @b available: @n
 * #vertex <nodeProperties, edgeProperties, graphTraits::directed, edgeContainer> @n
 * #vertex <nodeProperties*, edgeProperties*, graphTraits::directed, edgeContainer> @n
 * #vertex <nodeProperties*, edgeProperties, graphTraits::directed, edgeContainer> @n
 * #vertex <nodeProperties, edgeProperties*, graphTraits::directed, edgeContainer> @n
 * #vertex <nodeProperties, edgeProperties, graphTraits::bidirectional, edgeContainer> @n
 * #vertex <nodeProperties*, edgeProperties*, graphTraits::bidirectional, edgeContainer> @n
 * #vertex <nodeProperties*, edgeProperties, graphTraits::bidirectional, edgeContainer> @n
 * #vertex <nodeProperties, edgeProperties*, graphTraits::bidirectional, edgeContainer> @n
 */
template<typename nodeProperties, typename edgeProperties, typename graphType, typename edgeContainer> class vertex{};


template<typename nodeProperties, typename edgeProperties, typename graphType, typename edgeContainer> class edge;

#include "GraphNode.hpp"
#include "GraphEdge.hpp"

#endif /* UTILS_GRAPH_INCLUDE_GRAPHTRAITS_HPP_ */
