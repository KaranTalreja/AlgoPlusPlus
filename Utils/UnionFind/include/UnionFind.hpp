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


/**
 * @brief [General Template]: #UnionFind data structure
 * @tparam	nodeProperties	The properties of the user defined node to be encapsulated in the #UnionFind data structure
 * @tparam	nodeContainer	To specify the type of storage which is to be used for the #UFNode. #graphTraits::listStorage or #graphTraits::vectorStorage@n
 * @details
 * @b Specializations @b available: @n
 * #UnionFind<nodeProperties*,nodeContainer> @n
 */
template <typename nodeProperties, typename nodeContainer = graphTraits::listStorage>
class UnionFind{};

/**
 * @brief [Partial Specialization]: #UnionFind which uses node of type pointers
 * @details @copydetails UnionFind
 */
template <typename nodeProperties, typename nodeContainer>
class UnionFind <nodeProperties*,nodeContainer>
{
	typedef UFNode<nodeProperties*,nodeContainer> nodeType;	///< Node type stored in UnionFind
	typedef typename container_gen<nodeContainer,nodeType>::type nodeContainerType;	///< The type of container used to store nodes in UnionFind
	nodeContainerType m_graph;	///< Member to store all the nodes of UnionFind data structure
public:
	typedef typename nodeContainerType::iterator nodeDescriptor;	///< Descriptor of nodes stored in UnionFind data structure
	typedef typename nodeType::followerListType followerListType;	///< The type of list of followers to this UnionFind node
	typedef typename followerListType::value_type followerListValueType;	///< The type of value of list of followers to this UnionFind node
	typedef typename nodeType::followerDescriptor followerDesciptor;	///<Descriptor of follower nodes of this node
	///@brief Default constructor
	UnionFind(){}

	/**
	 * @brief Member function to add a node in this data structure
	 * @param	n	User defined properties which are to be encapsulated in the #UFNode
	 * @return The #nodeDescriptor to the node just inserted in the UnionFind data structure
	 */
	nodeDescriptor addNode(nodeProperties* n)
	{
		this->m_graph.push_back(n);
		nodeDescriptor retVal = this->m_graph.end();
		return --retVal;
	}
	/**
	 * @brief Operator[] to provide access to user defined node properties of a node of this data structure
	 * @param	v	The node descriptor of the node of which user defined properties are to be accessed
	 * @return	The user defined properties encapsulated in the UnionFind's node
	 */
	nodeProperties* operator[] (nodeDescriptor& v) { return *v; }

	/**
	 * @brief Union member function to merge two clusters given there leaders
	 * @param	firstArg	The leader of first cluster
	 * @param	secondArg	The leader of second cluster
	 * @details The function checks on the basis of rank which node will become the leader of both the clusters combined.@n
	 * If the first leader's rank is greater than second, all the followers of second cluster are added into the first one's including the
	 * second leader @n
	 * If the second leader's rank is greater than the first, same is done as above scenario. @n
	 * If both the ranks are equal, only then first is chosen as the leader and its rank is incremented by one. The same thing happens to the
	 * followers as mentioned above.
	 * @return Nothing
	 */
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

	/**
	 * @brief Find member function to find the leader of a given node.
	 * @param	child	The node of which the leader is to be found
	 * @details	The function implements a path compression algorithm for the UnionFind data structure. All the nodes which come in between
	 * the actual leader and the input child are added to a list. All the node's in this list will have their leader updated to the final one.
	 * This would make the final find queries more time effecient.
	 * @return The leader of the input child.
	 */
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
