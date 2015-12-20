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

template <typename nodeProperties, typename nodeContainer>
class UFNode;

template <typename nodeProperties, typename nodeContainer>
class UFNode<nodeProperties*,nodeContainer>
{
	nodeProperties* internalProperty;
	typedef UFNode<nodeProperties*,nodeContainer> nodeType;
	typedef typename container_gen<nodeContainer,nodeType>::type nodeContainerType;
	typedef typename nodeContainerType::iterator nodeDescriptor;
public:
	typedef typename tr1::unordered_set<nodeDescriptor*> followerListType;
	typedef typename followerListType::iterator followerDescriptor;
	size_t rank;
	nodeDescriptor* leader;
	followerListType followers;
	UFNode():internalProperty(NULL),rank(0),leader(NULL){}
	UFNode(nodeProperties* n) : internalProperty(n),rank(0),leader(NULL){}
	void setLeader (nodeDescriptor* leader) { this->leader = leader; }
	operator nodeProperties* () { return internalProperty; }
};

#endif /* UTILS_UNIONFIND_INCLUDE_UNIONFINDNODE_HPP_ */
