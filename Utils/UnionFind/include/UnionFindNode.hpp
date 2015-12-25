/**
 * @file UnionFindNode.hpp
 *
 *  Created on: 20-Dec-2015
 * @author: Karan Talreja
 */

#ifndef UTILS_UNIONFIND_INCLUDE_UNIONFINDNODE_HPP_
#define UTILS_UNIONFIND_INCLUDE_UNIONFINDNODE_HPP_

#include <iostream>
#include "GraphTraits.hpp"
#include <tr1/unordered_set>

/**
 * @brief [General Template]: Class to specify the node type used in #UnionFind
 * @tparam	nodeProperties	The properties of the user defined node to be encapsulated in the #UnionFind data structure
 * @tparam	nodeContainer	To specify the type of storage which is to be used for the #UFNode. #graphTraits::listStorage or #graphTraits::vectorStorage@n
 * @details
 * @b Specializations @b available: @n
 * #UFNode<nodeProperties*,nodeContainer> @n
 */
template <typename nodeProperties, typename nodeContainer>
class UFNode{};

/**
 * @brief [Partial Specialization]: Class to specify the node type used in #UnionFind which uses node of type pointers
 * @details @copydetails UFNode
 */
template <typename nodeProperties, typename nodeContainer>
class UFNode<nodeProperties*,nodeContainer>
{
	nodeProperties* internalProperty;	///< User defined node properties to be encapsulated in UnionFind data structure
	typedef UFNode<nodeProperties*,nodeContainer> nodeType;	///< Node type stored in UnionFind
	typedef typename container_gen<nodeContainer,nodeType>::type nodeContainerType;	///< The type of container used to store nodes in UnionFind
	typedef typename nodeContainerType::iterator nodeDescriptor;	///< Descriptor of nodes stored in UnionFind data structure
public:
	typedef typename tr1::unordered_set<nodeDescriptor*> followerListType;	///< The type of list of followers to this UnionFind node
	typedef typename followerListType::iterator followerDescriptor;	///<Descriptor of follower nodes of this node
	size_t rank;	///< Rank of this UnionFind node
	nodeDescriptor* leader;	///< The leader of this UnionFind node
	followerListType followers;	///< The followers of this UnionFind node
	///@brief Default constructor
	UFNode():internalProperty(NULL),rank(0),leader(NULL){}
	///@brief Single argument constructor
	UFNode(nodeProperties* n) : internalProperty(n),rank(0),leader(NULL){}
	/**
	 * @brief Member function to set leader of this node
	 * @param	leader	The node which is to be set as leader of this node
	 */
	void setLeader (nodeDescriptor* leader) { this->leader = leader; }
	///@brief Type cast operator to provide access to user defined encapsulated property
	operator nodeProperties* () { return internalProperty; }
};

#endif /* UTILS_UNIONFIND_INCLUDE_UNIONFINDNODE_HPP_ */
