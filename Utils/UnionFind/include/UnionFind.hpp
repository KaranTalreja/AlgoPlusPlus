/**
 * @file UnionFind.hpp
 *
 * Created on: 02-Aug-2015
 * @author: Karan Talreja
 */

#ifndef UTILS_UNIONFIND_INCLUDE_UNIONFIND_HPP_
#define UTILS_UNIONFIND_INCLUDE_UNIONFIND_HPP_

#include "GraphTraits.hpp"
#include "UnionFindNode.hpp"

template <typename nodeProperties, typename nodeContainer = graphTraits::listStorage>
class UnionFind;

template <typename nodeProperties, typename nodeContainer>
class UnionFind <nodeProperties*,nodeContainer>
{
	typedef UFNode<nodeProperties*,nodeContainer> nodeType;
	typedef typename container_gen<nodeContainer,nodeType>::type nodeContainerType;
	nodeContainerType m_graph;
public:
	typedef typename nodeContainerType::iterator nodeDescriptor;
	typedef typename nodeType::followerListType followerListType;
	typedef typename followerListType::value_type followerListValueType;
	typedef typename nodeType::followerDescriptor followerDesciptor;
	UnionFind(){}
	int decompile(bool toPrint = false);
	nodeDescriptor addNode(nodeProperties* n)
	{
		this->m_graph.push_back(n);
		nodeDescriptor retVal = this->m_graph.end();
		return --retVal;
	}
	nodeProperties* operator[] (nodeDescriptor& v) { return *v; }
	void Union(nodeDescriptor *firstArg,nodeDescriptor *secondArg)
	{
		nodeDescriptor first = *firstArg;
		nodeDescriptor second = *secondArg;
		if(first->rank > second->rank)
		{
			second->leader = firstArg;
			followerDesciptor itr = second->followers.begin();
			for( ;itr!= second->followers.end(); itr++) first->followers.insert(followerListValueType(*itr));
			first->followers.insert(followerListValueType(secondArg));
		}
		else if(first->rank == second->rank)
		{
			second->leader = firstArg;
			followerDesciptor itr = second->followers.begin();
			for( ; itr != second->followers.end(); itr++ )	first->followers.insert(followerListValueType(*itr));
			first->followers.insert(followerListValueType(secondArg));
			first->rank++;
		}
		else
		{
			first->leader = secondArg;
			followerDesciptor itr = first->followers.begin();
			for(;itr!=first->followers.end();itr++) second->followers.insert(followerListValueType(*itr));
			second->followers.insert(followerListValueType(firstArg));
		}
	}
	nodeDescriptor* Find(nodeDescriptor *child)
	{
		nodeDescriptor* startNode = child;
		std::vector<nodeDescriptor*> listOfNodesToUpdate;
		while((*startNode)->leader != startNode)
		{
			listOfNodesToUpdate.push_back(startNode);
			startNode = (*startNode)->leader;
		}
		nodeDescriptor* leader = (*startNode)->leader;
		for(unsigned int i = 0; i < listOfNodesToUpdate.size();i++)	(*listOfNodesToUpdate[i])->leader = leader;
		return startNode;
	}
};

#endif /* UTILS_UNIONFIND_INCLUDE_UNIONFIND_HPP_ */
