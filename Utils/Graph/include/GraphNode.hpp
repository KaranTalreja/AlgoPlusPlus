/**
 * @file GraphNode.hpp
 *
 *  Created on: 19-Dec-2015
 * @author: Karan Talreja
 */

#ifndef UTILS_GRAPH_INCLUDE_GRAPHNODE_HPP_
#define UTILS_GRAPH_INCLUDE_GRAPHNODE_HPP_

#include "GraphTraits.hpp"

/**
 * @brief [General Template]: Class to specify the base class of #vertex type used in #graph
 * @tparam	nodeProperties	The properties of the user defined node to be encapsulated in the graph #vertex
 * @tparam	edgeProperties	The properties of the user defined edge to be encapsulated in the graph #edge
 * @tparam	graphType		To specify whether a graph is #graphTraits::directed or #graphTraits::bidirectional
 * @tparam	edgeContainer	To specify the type of storage which is to be used for the #edge. #graphTraits::listStorage or #graphTraits::vectorStorage
 * @details The user defined nodeProperties are kept in the class as a variable.@n
 * @b Specializations @b available: @n
 * #base_vertex<nodeProperties*, edgeProperties*,graphType, edgeContainer>	// Both node and edge of pointer types @n
 * #base_vertex<nodeProperties*, edgeProperties,graphType, edgeContainer>	// Node of pointer type @n
 * #base_vertex<nodeProperties, edgeProperties*,graphType, edgeContainer>	// Edge of pointer type @n
 */
template <typename nodeProperties,typename edgeProperties, typename graphType , typename edgeContainer>
class base_vertex
{
	nodeProperties internalProperties;	///< Member to store user defined node properties
public:
	///@brief Default constructor
	base_vertex(){}
	/**
	 * @brief Single argument constructor
	 * @param	v	Reference to user defined node properties to be stored in this class
	 */
	base_vertex(nodeProperties& v) : internalProperties(v){}
	typedef edge<nodeProperties, edgeProperties, graphType, edgeContainer> edgeType;	///< Type of the edge used in the vertex of graph
	typedef typename container_gen<edgeContainer,edgeType>::type edgeListContainerType;	///< Type to denote the type of memory taken by edge list
	typedef typename edgeListContainerType::iterator edgeDescriptor;	///< Descriptor type of edge
	typedef vertex<nodeProperties,edgeProperties,graphType,edgeContainer> nodeType;	///< Type of vertex used in the graph
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;	///< Descriptor of adjacent vertices to this vertex
	std::vector<nodeType*> adjVertexList;	///< Member list to store all adjacent vertices through out edges
	/**
	 * @brief Member function to provide the descriptor to first adjacent vertex
	 * @return Variable of type #adjVertexDescriptor
	 */
	adjVertexDescriptor adjVertexBegin () { return this->adjVertexList.begin(); }
	/**
	 * @brief Member function to provide the descriptor to last adjacent vertex
	 * @return Variable of type #adjVertexDescriptor
	 */
	adjVertexDescriptor adjVertexEnd () { return this->adjVertexList.end(); }
	/**
	 * @brief Decompilation support provided to be used by classes which have nodes of this class type.
	 * @param	out	ostream variable in which the output is piped.
	 * @param	bv	variable of this class type which is to be decompiled
	 * @return Reference to out input argument with filled decompilation data of the input object
	 */
	friend ostream& operator<< (ostream &out, base_vertex& bv)
	{
		out << " " << nodeProperties(bv);
		return out;
	}
	///@brief Type cast operator to user defined encapsulated type
	operator nodeProperties () {return internalProperties;}
};

/**
 * @brief [Partial Specialization]: #base_vertex which uses node and edge properties of pointer type
 * @details @copydetails base_vertex
 */
template <typename nodeProperties,typename edgeProperties, typename graphType , typename edgeContainer>
class base_vertex<nodeProperties*,edgeProperties*,graphType,edgeContainer>
{
	nodeProperties* internalProperties; 	///<@copybrief base_vertex::internalProperties
public:
	base_vertex():internalProperties(NULL){}	///<@copybrief base_vertex::base_vertex
	base_vertex(nodeProperties *v) : internalProperties(v){}	///<@copybrief base_vertex::base_vertex(nodeProperties& v)
	typedef edge<nodeProperties*, edgeProperties*, graphType, edgeContainer> edgeType;	///<@copybrief base_vertex::edgeType
	typedef typename container_gen<edgeContainer,edgeType>::type edgeListContainerType;	///<@copybrief base_vertex::edgeListContainerType
	typedef typename edgeListContainerType::iterator edgeDescriptor;	///<@copybrief base_vertex::edgeDescriptor
	typedef vertex<nodeProperties*,edgeProperties*,graphType,edgeContainer> nodeType;	///<@copybrief base_vertex::nodeType
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;	///<@copybrief base_vertex::adjVertexDescriptor
	std::vector<nodeType*> adjVertexList;	///<@copybrief base_vertex::adjVertexList
	///@copydoc base_vertex::adjVertexBegin
	adjVertexDescriptor adjVertexBegin () { return this->adjVertexList.begin(); }
	///@copydoc base_vertex::adjVertexEnd
	adjVertexDescriptor adjVertexEnd () { return this->adjVertexList.end(); }
	///@copydoc base_vertex::operator<<
	friend ostream& operator<< (ostream &out, base_vertex& bv)
	{
		out << " " << nodeProperties(bv);
		return out;
	}
	///@brief Type cast operator to user defined encapsulated type
	operator nodeProperties () {return *internalProperties;}
	///@brief Type cast operator to user defined encapsulated type
	operator nodeProperties* () {return internalProperties;}
};

/**
 * @brief [Partial Specialization]: #base_vertex which uses node properties of pointer type
 * @details @copydetails base_vertex
 */
template <typename nodeProperties,typename edgeProperties, typename graphType , typename edgeContainer>
class base_vertex<nodeProperties*,edgeProperties,graphType,edgeContainer>
{
	nodeProperties* internalProperties;	///<@copybrief base_vertex::internalProperties
public:
	base_vertex() : internalProperties(NULL){}///<@copybrief base_vertex::base_vertex
	base_vertex(nodeProperties *v) : internalProperties(v){}	///<@copybrief base_vertex::base_vertex(nodeProperties& v)
	typedef edge<nodeProperties*, edgeProperties, graphType, edgeContainer> edgeType;	///<@copybrief base_vertex::edgeType
	typedef typename container_gen<edgeContainer,edgeType>::type edgeListContainerType;	///<@copybrief base_vertex::edgeListContainerType
	typedef typename edgeListContainerType::iterator edgeDescriptor;	///<@copybrief base_vertex::edgeDescriptor
	typedef vertex<nodeProperties*,edgeProperties,graphType,edgeContainer> nodeType;	///<@copybrief base_vertex::nodeType
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;	///<@copybrief base_vertex::adjVertexDescriptor
	std::vector<nodeType*> adjVertexList;	///<@copybrief base_vertex::adjVertexList
	///@copydoc base_vertex::adjVertexBegin
	adjVertexDescriptor adjVertexBegin () { return this->adjVertexList.begin(); }
	///@copydoc base_vertex::adjVertexEnd
	adjVertexDescriptor adjVertexEnd () { return this->adjVertexList.end(); }
	///@copydoc base_vertex::operator<<
	friend ostream& operator<< (ostream &out, base_vertex& bv)
	{
		out << " " << nodeProperties(bv);
		return out;
	}
	///@brief Type cast operator to user defined encapsulated type
	operator nodeProperties () {return *internalProperties;}
	///@brief Type cast operator to user defined encapsulated type
	operator nodeProperties* () {return internalProperties;}
};

/**
 * @brief [Partial Specialization]: #base_vertex which uses edge properties of pointer type
 * @details @copydetails base_vertex
 */
template <typename nodeProperties,typename edgeProperties, typename graphType , typename edgeContainer>
class base_vertex<nodeProperties,edgeProperties*,graphType,edgeContainer>
{
	nodeProperties internalProperties;	///<@copybrief base_vertex::internalProperties
public:
	base_vertex(){}
	base_vertex(nodeProperties& v) : internalProperties(v){}	///<@copybrief base_vertex::base_vertex(nodeProperties& v)
	typedef edge<nodeProperties, edgeProperties*, graphType, edgeContainer> edgeType;	///<@copybrief base_vertex::edgeType
	typedef typename container_gen<edgeContainer,edgeType>::type edgeListContainerType;	///<@copybrief base_vertex::edgeListContainerType
	typedef typename edgeListContainerType::iterator edgeDescriptor;	///<@copybrief base_vertex::edgeDescriptor
	typedef vertex<nodeProperties,edgeProperties*,graphType,edgeContainer> nodeType;	///<@copybrief base_vertex::nodeType
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;	///<@copybrief base_vertex::adjVertexDescriptor
	std::vector<nodeType*> adjVertexList;	///<@copybrief base_vertex::adjVertexList
	///@copydoc base_vertex::adjVertexBegin
	adjVertexDescriptor adjVertexBegin () { return this->adjVertexList.begin(); }
	///@copydoc base_vertex::adjVertexEnd
	adjVertexDescriptor adjVertexEnd () { return this->adjVertexList.end(); }
	///@copydoc base_vertex::operator<<
	friend ostream& operator<< (ostream &out, base_vertex& bv)
	{
		out << " " << nodeProperties(bv);
		return out;
	}
	///@brief Type cast operator to user defined encapsulated type
	operator nodeProperties () {return internalProperties;}
};

/**
 * @brief [Partial Specialization]: #vertex which is for directed graph
 * @details @copydetails vertex
 */
template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties, edgeProperties, graphTraits::directed, edgeContainer> : public base_vertex<nodeProperties,edgeProperties,graphTraits::directed, edgeContainer>
{
	typedef base_vertex<nodeProperties,edgeProperties,graphTraits::directed, edgeContainer> baseClass;	///< Base class type
public:
	using typename baseClass::edgeListContainerType;	///< @copybrief base_vertex::edgeListContainerType
	using typename baseClass::edgeType;	///< @copybrief base_vertex::edgeType
private:
	edgeListContainerType in_edges;	///< Incoming edges to this vertex
	edgeListContainerType out_edges;	///< Outgoing edges to this vertex
public:
	///@brief Default constructor
	vertex(){}
	/**
	 * @brief Single argument constructor
	 * @param	v	Reference to user defined node properties to be stored in this class
	 */
	vertex(nodeProperties& v) : base_vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;	///< @copybrief base_vertex::edgeDescriptor

	/**
	 * @brief Member function to provide the descriptor to first incoming edge
	 * @return Variable of type #edgeDescriptor
	 */
	edgeDescriptor inBegin() {return in_edges.begin();}

	/**
	 * @brief Member function to provide the descriptor to last incoming edge
	 * @return Variable of type #edgeDescriptor
	 */
	edgeDescriptor inEnd() {return in_edges.end();}

	/**
	 * @brief Member function to provide the descriptor to first outgoing edge
	 * @return Variable of type #edgeDescriptor
	 */
	edgeDescriptor outBegin() {return out_edges.begin();}

	/**
	 * @brief Member function to provide the descriptor to last outgoing edge
	 * @return Variable of type #edgeDescriptor
	 */
	edgeDescriptor outEnd() {return out_edges.end();}

	/**
	 * @brief Member function to add incoming edge to this vertex
	 * @param	e	The edge to be added to this vertex
	 * @return Nothing
	 */
	void addInEdge(edgeType e) { this->in_edges.push_back(e); }

	/**
	 * @brief Member function to add outgoing edge to this vertex
	 * @param	e	The edge to be added to this vertex
	 * @return Nothing
	 */
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};

/**
 * @brief [Partial Specialization]: #vertex which is for directed graph and node and edge of pointer types
 * @details @copydetails vertex
 */
template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties*, edgeProperties*, graphTraits::directed, edgeContainer> : public base_vertex<nodeProperties*,edgeProperties*,graphTraits::directed, edgeContainer>
{
	typedef base_vertex<nodeProperties*,edgeProperties*,graphTraits::directed, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;	///< @copybrief base_vertex::edgeListContainerType
	using typename baseClass::edgeType;	///< @copybrief base_vertex::edgeType
private:
	edgeListContainerType in_edges;	///< @copybrief vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::in_edges
	edgeListContainerType out_edges;	///< @copybrief vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::out_edges
public:
	///@brief Default constructor
	vertex(){}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::vertex(nodeProperties& v)
	vertex(nodeProperties *v) : base_vertex<nodeProperties*,edgeProperties*,graphTraits::directed,edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;	///< @copybrief base_vertex::edgeDescriptor
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::inBegin
	edgeDescriptor inBegin() {return in_edges.begin();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::inEnd
	edgeDescriptor inEnd() {return in_edges.end();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::outBegin
	edgeDescriptor outBegin() {return out_edges.begin();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::outEnd
	edgeDescriptor outEnd() {return out_edges.end();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::addInEdge
	void addInEdge(edgeType e) { this->in_edges.push_back(e); }
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::addOutEdge
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};

/**
 * @brief [Partial Specialization]: #vertex which is for directed graph and node of pointer types
 * @details @copydetails vertex
 */
template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties*, edgeProperties, graphTraits::directed, edgeContainer> : public base_vertex<nodeProperties*,edgeProperties,graphTraits::directed, edgeContainer>
{
	typedef base_vertex<nodeProperties*,edgeProperties,graphTraits::directed, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;	///< @copybrief base_vertex::edgeListContainerType
	using typename baseClass::edgeType;	///< @copybrief base_vertex::edgeType
private:
	edgeListContainerType in_edges;	///< @copybrief vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::in_edges
	edgeListContainerType out_edges;	///< @copybrief vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::out_edges
public:
	///@brief Default constructor
	vertex(){}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::vertex(nodeProperties& v)
	vertex(nodeProperties *v) : base_vertex<nodeProperties*,edgeProperties,graphTraits::directed,edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;	///< @copybrief base_vertex::edgeDescriptor
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::inBegin
	edgeDescriptor inBegin() {return in_edges.begin();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::inEnd
	edgeDescriptor inEnd() {return in_edges.end();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::outBegin
	edgeDescriptor outBegin() {return out_edges.begin();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::outEnd
	edgeDescriptor outEnd() {return out_edges.end();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::addInEdge
	void addInEdge(edgeType e) { this->in_edges.push_back(e); }
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::addOutEdge
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};

/**
 * @brief [Partial Specialization]: #vertex which is for directed graph and edge of pointer types
 * @details @copydetails vertex
 */
template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties, edgeProperties*, graphTraits::directed, edgeContainer> : public base_vertex<nodeProperties,edgeProperties*,graphTraits::directed, edgeContainer>
{
	typedef base_vertex<nodeProperties,edgeProperties*,graphTraits::directed, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;	///< @copybrief base_vertex::edgeListContainerType
	using typename baseClass::edgeType;	///< @copybrief base_vertex::edgeType
private:
	edgeListContainerType in_edges;	///< @copybrief vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::in_edges
	edgeListContainerType out_edges;	///< @copybrief vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::out_edges
public:
	///@brief Default constructor
	vertex(){}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::vertex(nodeProperties& v)
	vertex(nodeProperties& v) : base_vertex<nodeProperties,edgeProperties*,graphTraits::directed,edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;	///< @copybrief base_vertex::edgeDescriptor
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::inBegin
	edgeDescriptor inBegin() {return in_edges.begin();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::inEnd
	edgeDescriptor inEnd() {return in_edges.end();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::outBegin
	edgeDescriptor outBegin() {return out_edges.begin();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::outEnd
	edgeDescriptor outEnd() {return out_edges.end();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::addInEdge
	void addInEdge(edgeType e) { this->in_edges.push_back(e); }
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::addOutEdge
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};

/**
 * @brief [Partial Specialization]: #vertex which is for bidirectional graph
 * @details @copydetails vertex
 */
template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties, edgeProperties, graphTraits::bidirectional, edgeContainer> : public base_vertex<nodeProperties,edgeProperties,graphTraits::bidirectional , edgeContainer>
{
	typedef base_vertex<nodeProperties,edgeProperties,graphTraits::bidirectional, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;	///< @copybrief base_vertex::edgeListContainerType
	using typename baseClass::edgeType;	///< @copybrief base_vertex::edgeType
private:
	edgeListContainerType out_edges;	///< @copybrief vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::out_edges
public:
	///@brief Default constructor
	vertex(){}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::vertex(nodeProperties& v)
	vertex(nodeProperties& v) : base_vertex<nodeProperties,edgeProperties,graphTraits::bidirectional, edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;	///< @copybrief base_vertex::edgeDescriptor
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::outBegin
	edgeDescriptor outBegin() {return out_edges.begin();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::outEnd
	edgeDescriptor outEnd() {return out_edges.end();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::addOutEdge
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};

/**
 * @brief [Partial Specialization]: #vertex which is for bidirectional graph and node and edge of pointer types
 * @details @copydetails vertex
 */
template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties*, edgeProperties*, graphTraits::bidirectional, edgeContainer> : public base_vertex<nodeProperties*,edgeProperties*,graphTraits::bidirectional , edgeContainer>
{
	typedef base_vertex<nodeProperties*,edgeProperties*,graphTraits::bidirectional, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;	///< @copybrief base_vertex::edgeListContainerType
	using typename baseClass::edgeType;	///< @copybrief base_vertex::edgeType
private:
	edgeListContainerType out_edges;	///< @copybrief vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::out_edges
public:
	///@brief Default constructor
	vertex(){}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::vertex(nodeProperties& v)
	vertex(nodeProperties *v) : base_vertex<nodeProperties*,edgeProperties*,graphTraits::bidirectional, edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;	///< @copybrief base_vertex::edgeDescriptor
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::outBegin
	edgeDescriptor outBegin() {return out_edges.begin();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::outEnd
	edgeDescriptor outEnd() {return out_edges.end();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::addOutEdge
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};

/**
 * @brief [Partial Specialization]: #vertex which is for bidirectional graph and node of pointer types
 * @details @copydetails vertex
 */
template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties*, edgeProperties, graphTraits::bidirectional, edgeContainer> : public base_vertex<nodeProperties*,edgeProperties,graphTraits::bidirectional , edgeContainer>
{
	typedef base_vertex<nodeProperties*,edgeProperties,graphTraits::bidirectional, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;	///< @copybrief base_vertex::edgeListContainerType
	using typename baseClass::edgeType;	///< @copybrief base_vertex::edgeType
private:
	edgeListContainerType out_edges;	///< @copybrief vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::out_edges
public:
	///@brief Default constructor
	vertex(){}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::vertex(nodeProperties& v)
	vertex(nodeProperties *v) : base_vertex<nodeProperties*,edgeProperties,graphTraits::bidirectional, edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;	///< @copybrief base_vertex::edgeDescriptor
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::outBegin
	edgeDescriptor outBegin() {return out_edges.begin();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::outEnd
	edgeDescriptor outEnd() {return out_edges.end();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::addOutEdge
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};

/**
 * @brief [Partial Specialization]: #vertex which is for bidirectional graph and edge of pointer types
 * @details @copydetails vertex
 */
template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties, edgeProperties*, graphTraits::bidirectional, edgeContainer> : public base_vertex<nodeProperties,edgeProperties*,graphTraits::bidirectional , edgeContainer>
{
	typedef base_vertex<nodeProperties,edgeProperties*,graphTraits::bidirectional, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;	///< @copybrief base_vertex::edgeListContainerType
	using typename baseClass::edgeType;	///< @copybrief base_vertex::edgeType
private:
	edgeListContainerType out_edges;	///< @copybrief vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::out_edges
public:
	///@brief Default constructor
	vertex(){}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::vertex(nodeProperties& v)
	vertex(nodeProperties& v) : base_vertex<nodeProperties,edgeProperties*,graphTraits::bidirectional, edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;	///< @copybrief base_vertex::edgeDescriptor
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::outBegin
	edgeDescriptor outBegin() {return out_edges.begin();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::outEnd
	edgeDescriptor outEnd() {return out_edges.end();}
	///@copydoc vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>::addOutEdge
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};
#endif /* UTILS_GRAPH_INCLUDE_GRAPHNODE_HPP_ */
