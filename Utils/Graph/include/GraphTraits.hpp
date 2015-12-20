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

class graphTraits
{
public:
	typedef struct {} bidirectional;	//Undirected graph
	typedef struct {} directed;			//Directed graph

	typedef enum
	{
			Nodes,
			AllEdges,
			InEdges,
			OutEdges
	} decompileFlavor;

	typedef struct {} vectorStorage;
	typedef struct {} listStorage;

};

/**
 * @brief [General Template]: #container_gen used to create containers to be used in #graph.
 * @tparam	container_type	Type of container to be used.
 * @tparam	valueType		Type of value which is to be stored in the container.
 * @details This class is partially specialized on the basis of containers which are to be used for node or edge container memory.@n
 * @b Specialization @b available @n
 * #container_gen<vectorStorage,valueType>	//#vectorStorage used to generate container@n
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

template<typename nodeProperties, typename edgeProperties, typename graphType, typename edgeContainer> class vertex;

template<typename nodeProperties, typename edgeProperties, typename graphType, typename edgeContainer> class edge;

#include "GraphNode.hpp"
#include "GraphEdge.hpp"

#endif /* UTILS_GRAPH_INCLUDE_GRAPHTRAITS_HPP_ */
