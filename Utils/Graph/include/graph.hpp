/**
 *  @file graph.hpp
 *
 *  Created on: 04-Aug-2015
 *  @author: Karan Talreja
 *  @details This file contains implementation of graph data structure.
 */
#ifndef UTILS_GRAPH_INCLUDE_GRAPH_HPP_
#define UTILS_GRAPH_INCLUDE_GRAPH_HPP_

#include <iostream>
#include <vector>
#include <list>
#include "GraphTraits.hpp"

using namespace std;
/**
 * @brief [General Template]: graph data structure
 * @tparam	nodeProperties	The properties of the user defined node to be encapsulated in the graph #vertex
 * @tparam	edgeProperties	The properties of the user defined edge to be encapsulated in the graph #edge
 * @tparam	graphType		To specify whether a graph is #graphTraits::directed or #graphTraits::bidirectional
 * @tparam	nodeContainer	To specify the type of storage which is to be used for the #vertex. #graphTraits::listStorage or #graphTraits::vectorStorage@n
 * @tparam	edgeContainer	To specify the type of storage which is to be used for the #edge. #graphTraits::listStorage or #graphTraits::vectorStorage@n
 * @details
 * @b Specializations @b available: @n
 * #graph<nodeProperties, edgeProperties, graphTraits::bidirectional,nodeContainer,edgeContainer> @n
 * #graph<nodeProperties*, edgeProperties*, graphTraits::bidirectional,nodeContainer,edgeContainer> @n
 * #graph<nodeProperties*, edgeProperties, graphTraits::bidirectional,nodeContainer,edgeContainer> @n 
 * #graph<nodeProperties, edgeProperties*, graphTraits::bidirectional,nodeContainer,edgeContainer> @n 
 * #graph<nodeProperties, edgeProperties, graphTraits::directed,nodeContainer,edgeContainer> @n 
 * #graph<nodeProperties*, edgeProperties*, graphTraits::directed,nodeContainer,edgeContainer> @n 
 * #graph<nodeProperties*, edgeProperties, graphTraits::directed,nodeContainer,edgeContainer> @n 
 * #graph<nodeProperties, edgeProperties*, graphTraits::directed,nodeContainer,edgeContainer> @n 
 */
template <typename nodeProperties, typename edgeProperties, typename graphType,typename nodeContainer = graphTraits::listStorage,typename edgeContainer = graphTraits::listStorage> class graph{};

/**
 * @brief [General Template]: Base class for graph data structure
 * @tparam	nodeProperties	The properties of the user defined node to be encapsulated in the graph #vertex
 * @tparam	edgeProperties	The properties of the user defined edge to be encapsulated in the graph #edge
 * @tparam	graphType	To specify whether a graph is #graphTraits::directed or #graphTraits::bidirectional
 * @tparam	nodeContainer	To specify the type of storage which is to be used for the #vertex. #graphTraits::listStorage or #graphTraits::vectorStorage@n
 * @tparam	edgeContainer	To specify the type of storage which is to be used for the #edge. #graphTraits::listStorage or #graphTraits::vectorStorage@n
 * @details
 * @b Specializations @b available: @n
 * #base_graph<nodeProperties*, edgeProperties*, graphType,nodeContainer,edgeContainer> @n 
 * #base_graph<nodeProperties*, edgeProperties, graphType,nodeContainer,edgeContainer> @n 
 * #base_graph<nodeProperties, edgeProperties*, graphType,nodeContainer,edgeContainer> @n 
 */
template <typename nodeProperties, typename edgeProperties, typename graphType,typename nodeContainer = graphTraits::listStorage,typename edgeContainer = graphTraits::listStorage>
class base_graph
{
	typedef vertex<nodeProperties,edgeProperties,graphType,edgeContainer> nodeType;	///< Type of vertex used in the graph
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListContainerType;	///< Type of list storage used to store the vertices
public:
	typedef typename nodeListContainerType::const_iterator const_iterator;	///< Constant iterator for vertex list
	typedef typename nodeListContainerType::iterator vertexDescriptor;	///< Vertex descriptor type for the vertex
	typedef typename nodeType::edgeListContainerType::iterator edgeDescriptor;	///< Edge descriptor type for the edge
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;	///< Vertex descriptor type for the vertex
	typedef typename graphTraits::decompileFlavor decompileFlavor;	///< The flavor type in which this graph is to be decompiled
protected:
	typedef typename std::pair <vertexDescriptor, vertexDescriptor> vertexPairDescriptor;	///< Pair of vertex descriptors
	typedef typename std::pair <edgeDescriptor, edgeDescriptor> edgePairDescriptor;	///< Pair of edge descriptors
	typedef edge<nodeProperties,edgeProperties,graphType, edgeContainer> edgeType;	///< Type of edge used in the graph
public:
	decompileFlavor decompileType;	///< Varaible to keep the decompile flavor of this graph
	nodeListContainerType nodeList;	///< The list of vertices in this graph

	/**
	 * @brief Operator[] to provide access to user defined node properties of a vertex of this graph
	 * @param	v	The vertex descriptor of the vertex of which user defined properties are to be accessed
	 * @return	The user defined properties encapsulated in the graph's vertex
	 */
	nodeProperties& operator[] (vertexDescriptor& v) {return *v;}

	/**
	 * @brief Operator[] to provide access to user defined edge properties of a edge of this graph
	 * @param	e	The edge descriptor of the edge of which user defined properties are to be accessed
	 * @return	The user defined properties encapsulated in the graph's edge
	 */
	edgeProperties& operator[](edgeDescriptor& e) {return *e;}

	/**
	 * @brief Member function to provide access to provide descriptors to first and last vertex of this graph
	 * @return	The reference to variable of type #vertexPairDescriptor
	 */
	vertexPairDescriptor vertices (){return std::make_pair(this->nodeList.begin(), this->nodeList.end());}

	/**
	 * @brief Member function to add a vertex to this graph with the specified user defined properties
	 * @param	v	The user defined properties to be encapsulated in the graph's vertex
	 * @return	The vertex descriptor of the vertex just created
	 */
	vertexDescriptor addVertex (nodeProperties& v)
	{
		this->nodeList.push_back(v);
		vertexDescriptor retval = (this->nodeList.end());
		return --retval;
	}
	///@brief Member function to set the decompile flavor of the graph
	void setDecompileFlavor (decompileFlavor e) { this->decompileType = e;}
	///@brief Member function to get the decompile flavor of the graph
	decompileFlavor getDecompileFlavor () { return this->decompileType;}
	///@brief Member function to get the size of the graph
	size_t size() {return nodeList.size();}
};

/**
 * @brief [Partial specialization]: #base_graph where node and edge are of pointer types
 * @details @copydetails base_graph
 */
template <typename nodeProperties, typename edgeProperties, typename graphType,typename nodeContainer, typename edgeContainer>
class base_graph <nodeProperties*, edgeProperties* , graphType, nodeContainer, edgeContainer>
{
	typedef vertex<nodeProperties*,edgeProperties*,graphType,edgeContainer> nodeType;	///<@copybrief base_graph::nodeType
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListContainerType;	///<@copybrief base_graph::nodeListContainerType
public:
	typedef typename nodeListContainerType::const_iterator const_iterator;	///<@copybrief base_graph::const_iterator
	typedef typename nodeListContainerType::iterator vertexDescriptor;	///<@copybrief base_graph::vertexDescriptor
	typedef typename nodeType::edgeListContainerType::iterator edgeDescriptor;	///<@copybrief base_graph::edgeDescriptor
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;	///<@copybrief base_graph::adjVertexDescriptor
	typedef typename graphTraits::decompileFlavor decompileFlavor;	///<@copybrief base_graph::decompileFlavor
protected:
	typedef typename std::pair <vertexDescriptor, vertexDescriptor> vertexPairDescriptor;	///<@copybrief base_graph::vertexPairDescriptor
	typedef typename std::pair <edgeDescriptor, edgeDescriptor> edgePairDescriptor;	///<@copybrief base_graph::edgePairDescriptor
	typedef edge<nodeProperties*,edgeProperties*,graphType, edgeContainer> edgeType;	///<@copybrief base_graph::edgeType
public:
	decompileFlavor decompileType;	///<@copybrief base_graph::decompileType
	nodeListContainerType nodeList;	///<@copybrief base_graph::nodeList
	///@copydoc base_graph::operator[](vertexDescriptor& v)
	nodeProperties* operator[] (vertexDescriptor& v) {return *v;}
	///@copydoc base_graph::operator[](edgeDescriptor& e)
	edgeProperties* operator[](edgeDescriptor& e) {return *e;}
	///@copydoc base_graph::vertices
	vertexPairDescriptor vertices (){return std::make_pair(this->nodeList.begin(), this->nodeList.end());}
	///@copydoc base_graph::addVertex
	vertexDescriptor addVertex (nodeProperties *v)
	{
		this->nodeList.push_back(v);
		vertexDescriptor retval = (this->nodeList.end());
		return --retval;
	}
	///@copydoc base_graph::setDecompileFlavor
	void setDecompileFlavor (decompileFlavor e) { this->decompileType = e;}
	///@copydoc base_graph::getDecompileFlavor
	decompileFlavor getDecompileFlavor () { return this->decompileType;}
	///@copydoc base_graph::size
	size_t size() {return nodeList.size();}
};

/**
 * @brief [Partial specialization]: #base_graph where node is of pointer types
 * @details @copydetails base_graph
 */
template <typename nodeProperties, typename edgeProperties, typename graphType,typename nodeContainer, typename edgeContainer>
class base_graph <nodeProperties*, edgeProperties , graphType, nodeContainer, edgeContainer>
{
	typedef vertex<nodeProperties*,edgeProperties,graphType,edgeContainer> nodeType;	///<@copybrief base_graph::nodeType
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListContainerType;	///<@copybrief base_graph::nodeListContainerType
public:
	typedef typename nodeListContainerType::const_iterator const_iterator;	///<@copybrief base_graph::const_iterator
	typedef typename nodeListContainerType::iterator vertexDescriptor;	///<@copybrief base_graph::vertexDescriptor
	typedef typename nodeType::edgeListContainerType::iterator edgeDescriptor;	///<@copybrief base_graph::edgeDescriptor
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;	///<@copybrief base_graph::adjVertexDescriptor
	typedef typename graphTraits::decompileFlavor decompileFlavor;	///<@copybrief base_graph::decompileFlavor
protected:
	typedef typename std::pair <vertexDescriptor, vertexDescriptor> vertexPairDescriptor;	///<@copybrief base_graph::vertexPairDescriptor
	typedef typename std::pair <edgeDescriptor, edgeDescriptor> edgePairDescriptor;	///<@copybrief base_graph::edgePairDescriptor
	typedef edge<nodeProperties*,edgeProperties,graphType, edgeContainer> edgeType;	///<@copybrief base_graph::edgeType
public:
	decompileFlavor decompileType;	///<@copybrief base_graph::decompileType
	nodeListContainerType nodeList;	///<@copybrief base_graph::nodeList
	///@copydoc base_graph::operator[](vertexDescriptor& v)
	nodeProperties* operator[] (vertexDescriptor& v) {return *v;}
	///@copydoc base_graph::operator[](edgeDescriptor& e)
	edgeProperties& operator[](edgeDescriptor& e) {return *e;}
	///@copydoc base_graph::vertices
	vertexPairDescriptor vertices (){return std::make_pair(this->nodeList.begin(), this->nodeList.end());}
	///@copydoc base_graph::addVertex
	vertexDescriptor addVertex (nodeProperties *v)
	{
		this->nodeList.push_back(v);
		vertexDescriptor retval = (this->nodeList.end());
		return --retval;
	}
	///@copydoc base_graph::setDecompileFlavor
	void setDecompileFlavor (decompileFlavor e) { this->decompileType = e;}
	///@copydoc base_graph::getDecompileFlavor
	decompileFlavor getDecompileFlavor () { return this->decompileType;}
	///@copydoc base_graph::size
	size_t size() {return nodeList.size();}
};

/**
 * @brief [Partial specialization]: #base_graph where edge is of pointer types
 * @details @copydetails base_graph
 */
template <typename nodeProperties, typename edgeProperties, typename graphType,typename nodeContainer, typename edgeContainer>
class base_graph <nodeProperties, edgeProperties* , graphType, nodeContainer, edgeContainer>
{
	typedef vertex<nodeProperties,edgeProperties*,graphType,edgeContainer> nodeType;	///<@copybrief base_graph::nodeType
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListContainerType;	///<@copybrief base_graph::nodeListContainerType
public:
	typedef typename nodeListContainerType::const_iterator const_iterator;	///<@copybrief base_graph::const_iterator
	typedef typename nodeListContainerType::iterator vertexDescriptor;	///<@copybrief base_graph::vertexDescriptor
	typedef typename nodeType::edgeListContainerType::iterator edgeDescriptor;	///<@copybrief base_graph::edgeDescriptor
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;	///<@copybrief base_graph::adjVertexDescriptor
	typedef typename graphTraits::decompileFlavor decompileFlavor;	///<@copybrief base_graph::decompileFlavor
protected:
	typedef typename std::pair <vertexDescriptor, vertexDescriptor> vertexPairDescriptor;	///<@copybrief base_graph::vertexPairDescriptor
	typedef typename std::pair <edgeDescriptor, edgeDescriptor> edgePairDescriptor;	///<@copybrief base_graph::edgePairDescriptor
	typedef edge<nodeProperties,edgeProperties*,graphType, edgeContainer> edgeType;	///<@copybrief base_graph::edgeType
public:
	decompileFlavor decompileType;	///<@copybrief base_graph::decompileType
	nodeListContainerType nodeList;	///<@copybrief base_graph::nodeList
	///@copydoc base_graph::operator[](vertexDescriptor& v)
	nodeProperties& operator[] (vertexDescriptor& v) {return *v;}
	///@copydoc base_graph::operator[](edgeDescriptor& e)
	edgeProperties* operator[](edgeDescriptor& e) {return *e;}
	///@copydoc base_graph::vertices
	vertexPairDescriptor vertices (){return std::make_pair(this->nodeList.begin(), this->nodeList.end());}
	///@copydoc base_graph::addVertex
	vertexDescriptor addVertex (nodeProperties &v)
	{
		this->nodeList.push_back(v);
		vertexDescriptor retval = (this->nodeList.end());
		return --retval;
	}
	///@copydoc base_graph::setDecompileFlavor
	void setDecompileFlavor (decompileFlavor e) { this->decompileType = e;}
	///@copydoc base_graph::getDecompileFlavor
	decompileFlavor getDecompileFlavor () { return this->decompileType;}
	///@copydoc base_graph::size
	size_t size() {return nodeList.size();}
};

/**
 * @brief [Partial Specialization]: graph data structure for bidirectional graph
 * @details @copydetails graph
 */
template <typename nodeProperties, typename edgeProperties,typename nodeContainer, typename edgeContainer>
class graph <nodeProperties, edgeProperties, graphTraits::bidirectional,nodeContainer,edgeContainer> : public base_graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer, edgeContainer> baseClass;	///< Base class
	typedef graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer, edgeContainer> thisClass;	///< This class
public:
	using typename baseClass::edgePairDescriptor;	///<@copybrief base_graph::edgePairDescriptor
	using typename baseClass::vertexPairDescriptor;	///<@copybrief base_graph::vertexPairDescriptor
	using typename baseClass::edgeDescriptor;	///<@copybrief base_graph::edgeDescriptor
	using typename baseClass::vertexDescriptor;	///<@copybrief base_graph::vertexDescriptor
	using typename baseClass::adjVertexDescriptor;	///<@copybrief base_graph::adjVertexDescriptor
	using typename baseClass::edgeType;	///<@copybrief base_graph::edgeType
	///@brief Default constructor
	graph(){}

	/**
	 * @brief Member function to give access to outgoing edges of a vertex of this graph
	 * @param	v	The vertex descriptor of which the edges are required
	 * @return 	Pair of edge descriptors, which contain value of first and last outgoing edge
	 */
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}

	/**
	 * @brief Member function to add an edge to a vertex of this graph
	 * @param	source	The vertex descriptor of the source vertex of the edge to be added
	 * @param	sink	The vertex descriptor of the sink vertex of the edge to be added
	 * @param	e		The user defined edge properties of the edge to be added
	 * @details Since this edge is added to a bidirectional graph, both source and sink receive a outgoing edge with reverse information
	 * The edge properties are the same for both edges
	 */
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties& e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addOutEdge(edgeType(&(*sink),&(*source),e));
	}

	/**
	 * @brief Decompilation support provided to be used by classes which have nodes of this class type.
	 * @param	out	ostream variable in which the output is piped.
	 * @param	g	variable of this class type which is to be decompiled
	 * @details Based on the decompilation flavor of this graph, this function decompiles this graph.@n
	 * @return Reference to out input argument with filled decompilation data of the input object
	 */
	friend ostream& operator<< (ostream& out, thisClass& g)
	{
		switch (g.decompileType)
		{
		case graphTraits::Nodes:
		{
			cout << "Bidirectional graph \"Node Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				out << *v;
				for (adjVertexDescriptor adjV = v->adjVertexBegin() ; adjV != v->adjVertexEnd() ; adjV++) out <<" "<< *(*adjV);
				out << endl;
			}
		}
		break;
		case graphTraits::AllEdges:
		case graphTraits::OutEdges:
		{
			cout << "Bidirectional graph \"All Edges\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.out_edges(v).first; e != g.out_edges(v).second ; e++)
					out  << "Out:"<< *e << endl;
			}
		}
		break;
		default:
			break;
		}
		return out;
	}
};

/**
 * @brief [Partial Specialization]: graph data structure for bidirectional graph which uses nodes and edges of pointer types
 * @details @copydetails graph
 */
template <typename nodeProperties, typename edgeProperties,typename nodeContainer, typename edgeContainer>
class graph <nodeProperties*, edgeProperties*, graphTraits::bidirectional,nodeContainer,edgeContainer> : public base_graph<nodeProperties*,edgeProperties*,graphTraits::bidirectional,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties*,edgeProperties*,graphTraits::bidirectional,nodeContainer, edgeContainer> baseClass;	///< Base class
	typedef graph<nodeProperties*,edgeProperties*,graphTraits::bidirectional,nodeContainer, edgeContainer> thisClass;	///< This class
public:
	using typename baseClass::edgePairDescriptor;	///<@copybrief base_graph::edgePairDescriptor
	using typename baseClass::vertexPairDescriptor;	///<@copybrief base_graph::vertexPairDescriptor
	using typename baseClass::edgeDescriptor;	///<@copybrief base_graph::edgeDescriptor
	using typename baseClass::vertexDescriptor;	///<@copybrief base_graph::vertexDescriptor
	using typename baseClass::adjVertexDescriptor;	///<@copybrief base_graph::adjVertexDescriptor
	using typename baseClass::edgeType;	///<@copybrief base_graph::edgeType
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::graph
	graph(){}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::out_edges
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::addEdge
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties *e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addOutEdge(edgeType(&(*sink),&(*source),e));
	}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::operator<<
	friend ostream& operator<< (ostream& out, thisClass& g)
	{
		switch (g.decompileType)
		{
		case graphTraits::Nodes:
		{
			cout << "Bidirectional graph \"Node Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				out << *v;
				for (adjVertexDescriptor adjV = v->adjVertexBegin() ; adjV != v->adjVertexEnd() ; adjV++) out <<" "<< *(*adjV);
				out << endl;
			}
		}
		break;
		case graphTraits::AllEdges:
		case graphTraits::OutEdges:
		{
			cout << "Bidirectional graph \"All Edges\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.out_edges(v).first; e != g.out_edges(v).second ; e++)
					out  << "Out:"<< *e << endl;
			}
		}
		break;
		default:
			break;
		}
		return out;
	}
};

/**
 * @brief [Partial Specialization]: graph data structure for bidirectional graph which uses nodes of pointer types
 * @details @copydetails graph
 */
template <typename nodeProperties, typename edgeProperties,typename nodeContainer, typename edgeContainer>
class graph <nodeProperties*, edgeProperties, graphTraits::bidirectional,nodeContainer,edgeContainer> : public base_graph<nodeProperties*,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties*,edgeProperties,graphTraits::bidirectional,nodeContainer, edgeContainer> baseClass;	///< Base class
	typedef graph<nodeProperties*,edgeProperties,graphTraits::bidirectional,nodeContainer, edgeContainer> thisClass;	///< This class
public:
	using typename baseClass::edgePairDescriptor;	///<@copybrief base_graph::edgePairDescriptor
	using typename baseClass::vertexPairDescriptor;	///<@copybrief base_graph::vertexPairDescriptor
	using typename baseClass::edgeDescriptor;	///<@copybrief base_graph::edgeDescriptor
	using typename baseClass::vertexDescriptor;	///<@copybrief base_graph::vertexDescriptor
	using typename baseClass::adjVertexDescriptor;	///<@copybrief base_graph::adjVertexDescriptor
	using typename baseClass::edgeType;	///<@copybrief base_graph::edgeType
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::graph
	graph(){}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::out_edges
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::addEdge
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties& e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addOutEdge(edgeType(&(*sink),&(*source),e));
	}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::operator<<
	friend ostream& operator<< (ostream& out, thisClass& g)
	{
		switch (g.decompileType)
		{
		case graphTraits::Nodes:
		{
			cout << "Bidirectional graph \"Node Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				out << *v;
				for (adjVertexDescriptor adjV = v->adjVertexBegin() ; adjV != v->adjVertexEnd() ; adjV++) out <<" "<< *(*adjV);
				out << endl;
			}
		}
		break;
		case graphTraits::AllEdges:
		case graphTraits::OutEdges:
		{
			cout << "Bidirectional graph \"All Edges\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.out_edges(v).first; e != g.out_edges(v).second ; e++)
					out  << "Out:"<< *e << endl;
			}
		}
		break;
		default:
			break;
		}
		return out;
	}
};

/**
 * @brief [Partial Specialization]: graph data structure for bidirectional graph which uses edges of pointer types
 * @details @copydetails graph
 */
template <typename nodeProperties, typename edgeProperties,typename nodeContainer, typename edgeContainer>
class graph <nodeProperties, edgeProperties*, graphTraits::bidirectional,nodeContainer,edgeContainer> : public base_graph<nodeProperties,edgeProperties*,graphTraits::bidirectional,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties,edgeProperties*,graphTraits::bidirectional,nodeContainer, edgeContainer> baseClass;	///< Base class
	typedef graph<nodeProperties,edgeProperties*,graphTraits::bidirectional,nodeContainer, edgeContainer> thisClass;	///< This class
public:
	using typename baseClass::edgePairDescriptor;	///<@copybrief base_graph::edgePairDescriptor
	using typename baseClass::vertexPairDescriptor;	///<@copybrief base_graph::vertexPairDescriptor
	using typename baseClass::edgeDescriptor;	///<@copybrief base_graph::edgeDescriptor
	using typename baseClass::vertexDescriptor;	///<@copybrief base_graph::vertexDescriptor
	using typename baseClass::adjVertexDescriptor;	///<@copybrief base_graph::adjVertexDescriptor
	using typename baseClass::edgeType;	///<@copybrief base_graph::edgeType
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::graph
	graph(){}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::out_edges
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::addEdge
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties *e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addOutEdge(edgeType(&(*sink),&(*source),e));
	}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::operator<<
	friend ostream& operator<< (ostream& out, thisClass& g)
	{
		switch (g.decompileType)
		{
		case graphTraits::Nodes:
		{
			cout << "Bidirectional graph \"Node Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				out << *v;
				for (adjVertexDescriptor adjV = v->adjVertexBegin() ; adjV != v->adjVertexEnd() ; adjV++) out <<" "<< *(*adjV);
				out << endl;
			}
		}
		break;
		case graphTraits::AllEdges:
		case graphTraits::OutEdges:
		{
			cout << "Bidirectional graph \"All Edges\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.out_edges(v).first; e != g.out_edges(v).second ; e++)
					out  << "Out:"<< *e << endl;
			}
		}
		break;
		default:
			break;
		}
		return out;
	}
};

/**
 * @brief [Partial Specialization]: graph data structure for directed graph
 * @details @copydetails graph
 */
template <typename nodeProperties, typename edgeProperties, typename nodeContainer, typename edgeContainer>
class graph <nodeProperties, edgeProperties, graphTraits::directed,nodeContainer,edgeContainer> : public base_graph<nodeProperties,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer> baseClass;	///< Base class
	typedef graph<nodeProperties,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer> thisClass;	///< This class
public:
	using typename baseClass::edgePairDescriptor;	///<@copybrief base_graph::edgePairDescriptor
	using typename baseClass::vertexPairDescriptor;	///<@copybrief base_graph::vertexPairDescriptor
	using typename baseClass::edgeDescriptor;	///<@copybrief base_graph::edgeDescriptor
	using typename baseClass::vertexDescriptor;	///<@copybrief base_graph::vertexDescriptor
	using typename baseClass::adjVertexDescriptor;	///<@copybrief base_graph::adjVertexDescriptor
	using typename baseClass::edgeType;	///<@copybrief base_graph::edgeType
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::graph
	graph(){}

	/**
	 * @brief Member function to give access to incoming edges of a vertex of this graph
	 * @param	v	The vertex descriptor of which the edges are required
	 * @return 	Pair of edge descriptors, which contain value of first and last incoming edge
	 */
	edgePairDescriptor in_edges(vertexDescriptor& v){return std::make_pair(v->inBegin(),v->inEnd());}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::out_edges
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}

	/**
	 * @brief Member function to add an edge to a vertex of this graph
	 * @param	source	The vertex descriptor of the source vertex of the edge to be added
	 * @param	sink	The vertex descriptor of the sink vertex of the edge to be added
	 * @param	e		The user defined edge properties of the edge to be added
	 * @details Since this edge is added to a directed graph, source receives a outgoing edge, while sink receives an incoming edge
	 */
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties& e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addInEdge(edgeType(&(*source),&(*sink),e));
	}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::operator<<
	friend ostream& operator<< (ostream& out, thisClass& g)
	{
		switch (g.decompileType)
		{
		case graphTraits::Nodes:
		{
			cout << "Directed graph \"Node Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				out << *v;
				for (adjVertexDescriptor adjV = v->adjVertexBegin() ; adjV != v->adjVertexEnd() ; adjV++) out <<" "<< *(*adjV);
				out << endl;
			}
		}
		break;
		case graphTraits::AllEdges:
		{
			cout << "Directed graph \"All edges\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.out_edges(v).first; e != g.out_edges(v).second ; e++)
					out << "Out:"<<*e << endl;
				for (edgeDescriptor e = g.in_edges(v).first; e != g.in_edges(v).second ; e++)
					out <<"In :"<< *e << endl;
			}
		}
		break;
		case graphTraits::OutEdges:
		{
			cout << "Directed graph \"Out Edges Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.out_edges(v).first; e != g.out_edges(v).second ; e++)
					out <<"Out:"<< *e << endl;
			}
		}
		break;
		case graphTraits::InEdges:
		{
			cout << "Directed graph \"In Edges Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.in_edges(v).first; e != g.in_edges(v).second ; e++)
					out <<"In :"<< *e << endl;
			}
		}
		break;
		default:
			break;
		}
		return out;
	}
};

/**
 * @brief [Partial Specialization]: graph data structure for directed graph which uses nodes and edges of pointer types
 * @details @copydetails graph
 */
template <typename nodeProperties, typename edgeProperties, typename nodeContainer, typename edgeContainer>
class graph <nodeProperties*, edgeProperties*, graphTraits::directed,nodeContainer,edgeContainer> : public base_graph<nodeProperties*,edgeProperties*,graphTraits::directed,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties*,edgeProperties*,graphTraits::directed,nodeContainer,edgeContainer> baseClass;	///< Base class
	typedef graph<nodeProperties*,edgeProperties*,graphTraits::directed,nodeContainer,edgeContainer> thisClass;	///< This class
public:
	using typename baseClass::edgePairDescriptor;	///<@copybrief base_graph::edgePairDescriptor
	using typename baseClass::vertexPairDescriptor;	///<@copybrief base_graph::vertexPairDescriptor
	using typename baseClass::edgeDescriptor;	///<@copybrief base_graph::edgeDescriptor
	using typename baseClass::vertexDescriptor;	///<@copybrief base_graph::vertexDescriptor
	using typename baseClass::adjVertexDescriptor;	///<@copybrief base_graph::adjVertexDescriptor
	using typename baseClass::edgeType;	///<@copybrief base_graph::edgeType
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::graph
	graph(){}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer>::in_edges
	edgePairDescriptor in_edges(vertexDescriptor& v){return std::make_pair(v->inBegin(),v->inEnd());}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::out_edges
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer>::addEdge
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties *e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addInEdge(edgeType(&(*source),&(*sink),e));
	}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::operator<<
	friend ostream& operator<< (ostream& out, thisClass& g)
	{
		switch (g.decompileType)
		{
		case graphTraits::Nodes:
		{
			cout << "Directed graph \"Node Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				out << *v;
				for (adjVertexDescriptor adjV = v->adjVertexBegin() ; adjV != v->adjVertexEnd() ; adjV++) out <<" "<< *(*adjV);
				out << endl;
			}
		}
		break;
		case graphTraits::AllEdges:
		{
			cout << "Directed graph \"All Edges\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.out_edges(v).first; e != g.out_edges(v).second ; e++)
					out << "Out:"<<*e << endl;
				for (edgeDescriptor e = g.in_edges(v).first; e != g.in_edges(v).second ; e++)
					out <<"In :"<< *e << endl;
			}
		}
		break;
		case graphTraits::OutEdges:
		{
			cout << "Directed graph \"Out Edges Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.out_edges(v).first; e != g.out_edges(v).second ; e++)
					out <<"Out:"<< *e << endl;
			}
		}
		break;
		case graphTraits::InEdges:
		{
			cout << "Directed graph \"In Edges Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.in_edges(v).first; e != g.in_edges(v).second ; e++)
					out <<"In :"<< *e << endl;
			}
		}
		break;
		default:
			break;
		}
		return out;
	}
};

/**
 * @brief [Partial Specialization]: graph data structure for directed graph which uses nodes of pointer types
 * @details @copydetails graph
 */
template <typename nodeProperties, typename edgeProperties, typename nodeContainer, typename edgeContainer>
class graph <nodeProperties*, edgeProperties, graphTraits::directed,nodeContainer,edgeContainer> : public base_graph<nodeProperties*,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties*,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer> baseClass;	///< Base class
	typedef graph<nodeProperties*,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer> thisClass;	///< This class
public:
	using typename baseClass::edgePairDescriptor;	///<@copybrief base_graph::edgePairDescriptor
	using typename baseClass::vertexPairDescriptor;	///<@copybrief base_graph::vertexPairDescriptor
	using typename baseClass::edgeDescriptor;	///<@copybrief base_graph::edgeDescriptor
	using typename baseClass::vertexDescriptor;	///<@copybrief base_graph::vertexDescriptor
	using typename baseClass::adjVertexDescriptor;	///<@copybrief base_graph::adjVertexDescriptor
	using typename baseClass::edgeType;	///<@copybrief base_graph::edgeType
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::graph
	graph(){}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer>::in_edges
	edgePairDescriptor in_edges(vertexDescriptor& v){return std::make_pair(v->inBegin(),v->inEnd());}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::out_edges
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer>::addEdge
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties& e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addInEdge(edgeType(&(*source),&(*sink),e));
	}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::operator<<
	friend ostream& operator<< (ostream& out, thisClass& g)
	{
		switch (g.decompileType)
		{
		case graphTraits::Nodes:
		{
			cout << "Directed graph \"Node Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				out << *v;
				for (adjVertexDescriptor adjV = v->adjVertexBegin() ; adjV != v->adjVertexEnd() ; adjV++) out <<" "<< *(*adjV);
				out << endl;
			}
		}
		break;
		case graphTraits::AllEdges:
		{
			cout << "Directed graph \"All Edges\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.out_edges(v).first; e != g.out_edges(v).second ; e++)
					out << "Out:"<<*e << endl;
				for (edgeDescriptor e = g.in_edges(v).first; e != g.in_edges(v).second ; e++)
					out <<"In :"<< *e << endl;
			}
		}
		break;
		case graphTraits::OutEdges:
		{
			cout << "Directed graph \"Out Edges Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.out_edges(v).first; e != g.out_edges(v).second ; e++)
					out <<"Out:"<< *e << endl;
			}
		}
		break;
		case graphTraits::InEdges:
		{
			cout << "Directed graph \"In Edges Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.in_edges(v).first; e != g.in_edges(v).second ; e++)
					out <<"In :"<< *e << endl;
			}
		}
		break;
		default:
			break;
		}
		return out;
	}
};

/**
 * @brief [Partial Specialization]: graph data structure for directed graph which uses edges of pointer types
 * @details @copydetails graph
 */
template <typename nodeProperties, typename edgeProperties, typename nodeContainer, typename edgeContainer>
class graph <nodeProperties, edgeProperties*, graphTraits::directed,nodeContainer,edgeContainer> : public base_graph<nodeProperties,edgeProperties*,graphTraits::directed,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties,edgeProperties*,graphTraits::directed,nodeContainer,edgeContainer> baseClass;	///< Base class
	typedef graph<nodeProperties,edgeProperties*,graphTraits::directed,nodeContainer,edgeContainer> thisClass;	///< This class
public:
	using typename baseClass::edgePairDescriptor;	///<@copybrief base_graph::edgePairDescriptor
	using typename baseClass::vertexPairDescriptor;	///<@copybrief base_graph::vertexPairDescriptor
	using typename baseClass::edgeDescriptor;	///<@copybrief base_graph::edgeDescriptor
	using typename baseClass::vertexDescriptor;	///<@copybrief base_graph::vertexDescriptor
	using typename baseClass::adjVertexDescriptor;	///<@copybrief base_graph::adjVertexDescriptor
	using typename baseClass::edgeType;	///<@copybrief base_graph::edgeType
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::graph
	graph(){}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer>::in_edges
	edgePairDescriptor in_edges(vertexDescriptor& v){return std::make_pair(v->inBegin(),v->inEnd());}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::out_edges
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer>::addEdge
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties *e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addInEdge(edgeType(&(*source),&(*sink),e));
	}
	///@copydoc graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>::operator<<
	friend ostream& operator<< (ostream& out, thisClass& g)
	{
		switch (g.decompileType)
		{
		case graphTraits::Nodes:
		{
			cout << "Directed graph \"Node Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				out << *v;
				for (adjVertexDescriptor adjV = v->adjVertexBegin() ; adjV != v->adjVertexEnd() ; adjV++) out <<" "<< *(*adjV);
				out << endl;
			}
		}
		break;
		case graphTraits::AllEdges:
		{
			cout << "Directed graph \"All Edges\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.out_edges(v).first; e != g.out_edges(v).second ; e++)
					out << "Out:"<<*e << endl;
				for (edgeDescriptor e = g.in_edges(v).first; e != g.in_edges(v).second ; e++)
					out <<"In :"<< *e << endl;
			}
		}
		break;
		case graphTraits::OutEdges:
		{
			cout << "Directed graph \"Out Edges Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.out_edges(v).first; e != g.out_edges(v).second ; e++)
					out <<"Out:"<< *e << endl;
			}
		}
		break;
		case graphTraits::InEdges:
		{
			cout << "Directed graph \"In Edges Only\" decompile"<< endl;
			vertexDescriptor v = g.vertices().first;
			for ( ; v != g.vertices().second ; v++)
			{
				for (edgeDescriptor e = g.in_edges(v).first; e != g.in_edges(v).second ; e++)
					out <<"In :"<< *e << endl;
			}
		}
		break;
		default:
			break;
		}
		return out;
	}
};
#endif /* UTILS_GRAPH_INCLUDE_GRAPH_HPP_ */
