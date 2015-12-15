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

using namespace std;

/**
 * @brief Storage representation used in #graph
 * @details This is just the type specifier which is used through #container_gen class to generate a vector of nodes to be used in the #graph
 */
struct vectorStorage{};

/**
 * @brief Base class template for accessors of node properties or edge properties used in #graph.
 * @tparam	node	Type for which the descriptor is to be created
 * @details This class is used to instantiate decriptor types which provide access to various node or edge properties in the #graph
 */
template <typename node> class descriptor{};

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
class container_gen <vectorStorage, valueType>
{
public:
	typedef std::vector<valueType> type;	///< Typedef with standard name #type to be used in #graph
};

/**
 * @brief [General Template]: #nodeWithEdges template is used to implement a graph node with edges
 * @tparam	nodeProperties	The properties of node to be stored in graph. This could a structure containing various members.
 * @tparam	edgeProperties	The properties of edge between nodes to be stored in graph. This could a structure containing various members.
 * @tparam	edgeContainer	The container type which is to be used for graph edge memory allocation
 * @tparam	nodeDescriptor	The descriptor to provide access to various properties of the node.
 * @tparam	edgeDescriptor	The descriptor to provide access to various properties of the edge.
 * @details This class wraps the nodeProperties provided by the user to the graph template. While wrapping this the class adds a list
 * of edges to the nodes. This list of edges can be array-like accessed using a edge index. Also the properties of the node can be accessed
 * by node descriptors. @n
 * @b Specializations @b available @n
 * #nodeWithEdges<nodeProperties*, edgeProperties*, edgeContainer, nodeDescriptor, edgeDescriptor> // Both node and edge of pointer types @n
 * #nodeWithEdges<nodeProperties , edgeProperties*, edgeContainer, nodeDescriptor, edgeDescriptor> // Edge of pointer type @n
 * #nodeWithEdges<nodeProperties*, edgeProperties , edgeContainer, nodeDescriptor, edgeDescriptor> // Node of pointer type @n
 */
template <typename nodeProperties, typename edgeProperties,
		  typename edgeContainer,
		  typename nodeDescriptor = descriptor<nodeProperties>,
		  typename edgeDescriptor = descriptor<edgeProperties> >
class nodeWithEdges
{
public:
	typedef typename container_gen<edgeContainer,edgeProperties>::type edgeListType;	///< Type to denote the type of memory taken by edge list
	typedef nodeDescriptor nodeDescriptorType;	///< Type of node descriptor
	typedef edgeDescriptor edgeDescriptorType;	///< Type of edge descriptor
	nodeProperties m_nodeProperties;		///< Member to hold all the content of a node which is to be stored in the graph
	edgeListType m_edgeList;			///< Member to hold all the edges which are connected to this node
	nodeDescriptorType m_nodeDescriptor;		///< Member to provide access to various members of #m_nodeProperties
	edgeDescriptorType m_edgeDescriptor;		///< Member to provide access to various members of edge

	///@brief Default constructor to initialize the members.
	nodeWithEdges():m_edgeList(0){};

	/**
	 * @brief Single argument constructor to initialize the members.
	 * @param	node	Reference to a user defined node which is to embedded in this class
	 */
	nodeWithEdges(nodeProperties &node):m_edgeList(0) {this->m_nodeProperties = node;}

	/**
	 * @brief Operator [] to provide array type access to node properties.
	 * @param	v	Reference to a nodeDescriptor type node which provides access to m_nodeProperties
	 * @return	Reference to member m_nodeProperties
	 */
	nodeProperties& operator[] (nodeDescriptor &v) {return this->m_nodeProperties;}

	/**
	 * @brief Operator [] to provide array type access to edge of a particular node.
	 * @param	edgeIdx	Index of edge which is to be accessed in the edge list of the node.
	 * @return	Reference to edge indexed edgeIdx - 1 in the m_edgeList
	 */
	edgeProperties& operator[] (size_t edgeIdx) {return this->m_edgeList[edgeIdx-1];}

	/**
	 * @brief Member function to get the node descriptor of this class
	 * @return Reference to m_nodeDescriptor
	 */
	nodeDescriptor& getNodeDescriptor () {return (this->m_nodeDescriptor);}

	/**
	 * @brief Member function to get the edge descriptor of this class
	 * @return Reference to m_edgeDescriptor
	 */
	edgeDescriptor& getEdgeDescriptor () {return (this->m_edgeDescriptor);}

	/**
	 * @brief Member function to add a edge in this node's edge list.
	 * @param	edge	Reference to edge which is to be inserted in this node's edge list.
	 * @return Nothing
	 */
	void addEdge(edgeProperties& edge) {this->m_edgeList.push_back(edge);}

	///@brief Friend operator << for decompiling the node which is used from the graph decompile
	friend ostream& operator << (ostream& out, nodeWithEdges& node)
	{
		typename edgeListType::iterator edgeItr;
		for (edgeItr = node.m_edgeList.begin(); edgeItr != node.m_edgeList.end() ; edgeItr++) out << *(edgeItr);
		return out;
	}
};

/**
 * @brief [General Template]: #graph data structure
 * @tparam	nodeProperties	User defined type which is to be inserted into the graph
 * @tparam	edgeProperties	User defined type which is to be inserted into the nodes of the graph
 * @tparam	nodeContainer	The container type which is to be used for graph node memory allocation
 * @tparam	edgeContainer	The container type which is to be used for graph edge memory allocation
 * @tparam	nodeDescriptor	The descriptor which provides access to node's properties
 * @tparam	edgeDescriptor	The descriptor which provides access to edge's properties
 *
 * @details The general template only requires first two template arguments to be provided by the user. All of the rest have default
 * values assigned. The memory of nodes and edges is by default inserted into a std::vector. @n
 * @b Specializations @b available @n
 * #graph<nodeProperties*, edgeProperties*, nodeContainer, edgeContainer, nodeDescriptor, edgeDescriptor> // Both node and edge of pointer types @n
 * #graph<nodeProperties , edgeProperties*, nodeContainer, edgeContainer, nodeDescriptor, edgeDescriptor> // Edge of pointer type @n
 * #graph<nodeProperties*, edgeProperties , nodeContainer, edgeContainer, nodeDescriptor, edgeDescriptor> // Node of pointer type @n
 */
template <typename nodeProperties, typename edgeProperties,
		  typename nodeContainer = vectorStorage,
		  typename edgeContainer = vectorStorage,
		  typename nodeDescriptor = descriptor<nodeProperties>,
		  typename edgeDescriptor = descriptor<edgeProperties> >
class graph
{
public:
	typedef nodeWithEdges<nodeProperties, edgeProperties, edgeContainer> nodeType;	///< nodeProperties wrapper type which contains edges
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListType;	///< vector storage of nodeWithEdges
	typedef nodeDescriptor nodeDescriptorType;					///< Type of nodeDescriptor
	typedef edgeDescriptor edgeDescriptorType;					///< Type of edgeDescriptor
	nodeListType m_nodeList;							///< Member to hold the list of nodes in the graph

	///@brief Default constructor
	graph(){};

	/**
	 * @brief Single argument constructor to initialize the list of nodes.
	 * @param	noOfNodes	No of nodes which are to be allocated in the graph.
	 */
	graph(size_t noOfNodes) : m_nodeList(noOfNodes){};

	/**
	 * @brief Operator [] to provide array like access to the nodes at a index in the graph
	 * @param	idx	The index at which the node is required.
	 * @return	The node at index idx-1 in the m_nodeList member.
	 */
	nodeType &operator[](size_t idx) {return this->m_nodeList[idx-1];}

	///@brief Friend operator << for decompiling the graph
	friend ostream& operator<< (ostream& out, graph& graphInst)
	{
		typename nodeListType::iterator nodeItr;
		for (nodeItr = graphInst.m_nodeList.begin(); nodeItr != graphInst.m_nodeList.end() ;nodeItr++) out << *(nodeItr);
		return out;
	}
};

/**
 * @brief [Partial Specialization]: #nodeWithEdges template is used to implement a graph node with edges where both node and edge
 *  type are pointers
 * @tparam	nodeProperties	The properties of node to be stored in graph. This could a structure containing various members.
 * @tparam	edgeProperties	The properties of edge between nodes to be stored in graph. This could a structure containing various members.
 * @tparam	edgeContainer	The container type which is to be used for graph edge memory allocation
 * @tparam	nodeDescriptor	The descriptor to provide access to various properties of the node.
 * @tparam	edgeDescriptor	The descriptor to provide access to various properties of the edge.
 * @details This class wraps the nodeProperties provided by the user to the graph template. While wrapping this the class adds a list
 * of edges to the nodes. This list of edges can be array-like accessed using a edge index. Also the properties of the node can be accessed
 * by node descriptors.
 */
template <typename nodeProperties, typename edgeProperties,
		  typename edgeContainer,
		  typename nodeDescriptor,
		  typename edgeDescriptor>
class nodeWithEdges <nodeProperties*, edgeProperties*, edgeContainer, nodeDescriptor, edgeDescriptor>
{
public:
	typedef typename container_gen<edgeContainer,edgeProperties*>::type edgeListType;	///< Type to denote the type of memory taken by edge list
	typedef nodeDescriptor nodeDescriptorType;	///< Type of node descriptor
	typedef edgeDescriptor edgeDescriptorType;      ///< Type of edge descriptor
	nodeProperties *m_nodeProperties;               ///< Member to hold all the content of a node which is to be stored in the graph
	edgeListType m_edgeList;                        ///< Member to hold all the edges which are connected to this node
	nodeDescriptorType m_nodeDescriptor;            ///< Member to provide access to various members of #m_nodeProperties
	edgeDescriptorType m_edgeDescriptor;            ///< Member to provide access to various members of edge

	///@brief Default constructor to initialize the members.
	nodeWithEdges():m_nodeProperties(NULL),m_edgeList(0){};

	/**
	 * @brief Single argument constructor to initialize the members.
	 * @param	node	Reference to a user defined node which is to embedded in this class
	 */
	nodeWithEdges(nodeProperties* node):m_edgeList(0) {this->m_nodeProperties = node;}

	/**
	 * @brief Operator [] to provide array type access to node properties.
	 * @param	v	Reference to a nodeDescriptor type node which provides access to m_nodeProperties
	 * @return	Reference to member m_nodeProperties
	 */
	nodeProperties& operator[] (nodeDescriptor &v) {return *(this->m_nodeProperties);}

	/**
	 * @brief Operator [] to provide array type access to edge of a particular node.
	 * @param	edgeIdx	Index of edge which is to be accessed in the edge list of the node.
	 * @return	Reference to edge indexed edgeIdx - 1 in the m_edgeList
	 */
	edgeProperties& operator[] (size_t edgeIdx) {return *(this->m_edgeList[edgeIdx-1]);}

	/**
	 * @brief Member function to get the node descriptor of this class
	 * @return Reference to m_nodeDescriptor
	 */
	nodeDescriptor& getNodeDescriptor () {return (this->m_nodeDescriptor);}

	/**
	 * @brief Member function to get the edge descriptor of this class
	 * @return Reference to m_edgeDescriptor
	 */
	edgeDescriptor& getEdgeDescriptor () {return (this->m_edgeDescriptor);}

	/**
	 * @brief Member function to add a edge in this node's edge list.
	 * @param	edge	Reference to edge which is to be inserted in this node's edge list.
	 * @return Nothing
	 */
	void addEdge(edgeProperties* edge) {this->m_edgeList.push_back(edge);}

	///@brief Friend operator << for decompiling the node which is used from the graph decompile
	friend ostream& operator << (ostream& out, nodeWithEdges& node)
	{
		typename edgeListType::iterator edgeItr;
		for (edgeItr = node.m_edgeList.begin(); edgeItr != node.m_edgeList.end() ; edgeItr++) out << *(*(edgeItr));
		return out;
	}
};

/**
 * @brief [Partial Specialization]: #graph data structure for node and edge of pointer types
 * @tparam	nodeProperties	User defined type which is to be inserted into the graph
 * @tparam	edgeProperties	User defined type which is to be inserted into the nodes of the graph
 * @tparam	nodeContainer	The container type which is to be used for graph node memory allocation
 * @tparam	edgeContainer	The container type which is to be used for graph edge memory allocation
 * @tparam	nodeDescriptor	The descriptor which provides access to node's properties
 * @tparam	edgeDescriptor	The descriptor which provides access to edge's properties
 *
 * @details The general template only requires first two template arguments to be provided by the user. All of the rest have default
 * values assigned. The memory of nodes and edges is by default inserted into a std::vector. @n
 */
template <typename nodeProperties, typename edgeProperties, typename nodeContainer ,
		  typename edgeContainer ,typename nodeDescriptor,typename edgeDescriptor >
class graph<nodeProperties*, edgeProperties*, nodeContainer, edgeContainer, nodeDescriptor, edgeDescriptor>
{
public:
	typedef nodeWithEdges<nodeProperties*, edgeProperties*, edgeContainer> nodeType;	///< nodeProperties wrapper type which contains edges
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListType;         ///< vector storage of nodeWithEdges
	typedef nodeDescriptor nodeDescriptorType;                                         ///< Type of nodeDescriptor
	typedef edgeDescriptor edgeDescriptorType;                                         ///< Type of edgeDescriptor
	nodeListType m_nodeList;                                                           ///< Member to hold the list of nodes in the graph

	///@brief Default constructor
	graph(){};

	/**
	 * @brief Single argument constructor to initialize the list of nodes.
	 * @param	noOfNodes	No of nodes which are to be allocated in the graph.
	 */
	graph(size_t noOfNodes) : m_nodeList(noOfNodes){};

	/**
	 * @brief Operator [] to provide array like access to the nodes at a index in the graph
	 * @param	idx	The index at which the node is required.
	 * @return	The node at index idx-1 in the m_nodeList member.
	 */
	nodeType& operator[](size_t idx) {return this->m_nodeList[idx-1];}

	///@brief Friend operator << for decompiling the graph
	friend ostream& operator<< (ostream& out, graph& graphInst)
	{
		typename nodeListType::iterator nodeItr;
		for (nodeItr = graphInst.m_nodeList.begin(); nodeItr != graphInst.m_nodeList.end() ;nodeItr++) out << *(nodeItr);
		return out;
	}
};

/**
 * @brief [Partial Specialization]: #nodeWithEdges template is used to implement a graph node with edges where only node type is pointer.
 * @tparam	nodeProperties	The properties of node to be stored in graph. This could a structure containing various members.
 * @tparam	edgeProperties	The properties of edge between nodes to be stored in graph. This could a structure containing various members.
 * @tparam	edgeContainer	The container type which is to be used for graph edge memory allocation
 * @tparam	nodeDescriptor	The descriptor to provide access to various properties of the node.
 * @tparam	edgeDescriptor	The descriptor to provide access to various properties of the edge.
 * @details This class wraps the nodeProperties provided by the user to the graph template. While wrapping this the class adds a list
 * of edges to the nodes. This list of edges can be array-like accessed using a edge index. Also the properties of the node can be accessed
 * by node descriptors.
 */
template <typename nodeProperties, typename edgeProperties,
		  typename edgeContainer,
		  typename nodeDescriptor,
		  typename edgeDescriptor>
class nodeWithEdges <nodeProperties*, edgeProperties, edgeContainer, nodeDescriptor, edgeDescriptor>
{
public:
	typedef typename container_gen<edgeContainer,edgeProperties>::type edgeListType;	///< Type to denote the type of memory taken by edge list
	typedef nodeDescriptor nodeDescriptorType;	///< Type of node descriptor
	typedef edgeDescriptor edgeDescriptorType;      ///< Type of edge descriptor
	nodeProperties *m_nodeProperties;               ///< Member to hold all the content of a node which is to be stored in the graph
	edgeListType m_edgeList;                        ///< Member to hold all the edges which are connected to this node
	nodeDescriptorType m_nodeDescriptor;            ///< Member to provide access to various members of #m_nodeProperties
	edgeDescriptorType m_edgeDescriptor;            ///< Member to provide access to various members of edge

	///@brief Default constructor to initialize the members.
	nodeWithEdges():m_nodeProperties(NULL),m_edgeList(0){};

	/**
	 * @brief Single argument constructor to initialize the members.
	 * @param	node	Reference to a user defined node which is to embedded in this class
	 */
	nodeWithEdges(nodeProperties* node):m_edgeList(0) {this->m_nodeProperties = node;}

	/**
	 * @brief Operator [] to provide array type access to node properties.
	 * @param	v	Reference to a nodeDescriptor type node which provides access to m_nodeProperties
	 * @return	Reference to member m_nodeProperties
	 */
	nodeProperties& operator[] (nodeDescriptor &v) {return *(this->m_nodeProperties);}

	/**
	 * @brief Operator [] to provide array type access to edge of a particular node.
	 * @param	edgeIdx	Index of edge which is to be accessed in the edge list of the node.
	 * @return	Reference to edge indexed edgeIdx - 1 in the m_edgeList
	 */
	edgeProperties& operator[] (size_t edgeIdx) {return this->m_edgeList[edgeIdx-1];}

	/**
	 * @brief Member function to get the node descriptor of this class
	 * @return Reference to m_nodeDescriptor
	 */
	nodeDescriptor& getNodeDescriptor () {return (this->m_nodeDescriptor);}

	/**
	 * @brief Member function to get the edge descriptor of this class
	 * @return Reference to m_edgeDescriptor
	 */
	edgeDescriptor& getEdgeDescriptor () {return (this->m_edgeDescriptor);}

	/**
	 * @brief Member function to add a edge in this node's edge list.
	 * @param	edge	Reference to edge which is to be inserted in this node's edge list.
	 * @return Nothing
	 */
	void addEdge(edgeProperties &edge) {this->m_edgeList.push_back(edge);}

	///@brief Friend operator << for decompiling the node which is used from the graph decompile
	friend ostream& operator << (ostream& out, nodeWithEdges& node)
	{
		typename edgeListType::iterator edgeItr;
		for (edgeItr = node.m_edgeList.begin(); edgeItr != node.m_edgeList.end() ; edgeItr++) out << *(edgeItr);
		return out;
	}
};

/**
 * @brief [Partial Specialization]: #graph data structure for node of pointer type
 * @tparam	nodeProperties	User defined type which is to be inserted into the graph
 * @tparam	edgeProperties	User defined type which is to be inserted into the nodes of the graph
 * @tparam	nodeContainer	The container type which is to be used for graph node memory allocation
 * @tparam	edgeContainer	The container type which is to be used for graph edge memory allocation
 * @tparam	nodeDescriptor	The descriptor which provides access to node's properties
 * @tparam	edgeDescriptor	The descriptor which provides access to edge's properties
 *
 * @details The general template only requires first two template arguments to be provided by the user. All of the rest have default
 * values assigned. The memory of nodes and edges is by default inserted into a std::vector. @n
 */
template <typename nodeProperties, typename edgeProperties, typename nodeContainer ,
		  typename edgeContainer ,typename nodeDescriptor,typename edgeDescriptor >
class graph<nodeProperties*, edgeProperties, nodeContainer, edgeContainer, nodeDescriptor, edgeDescriptor>
{
public:
	typedef nodeWithEdges<nodeProperties*, edgeProperties, edgeContainer> nodeType; 	///< nodeProperties wrapper type which contains edges
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListType;         ///< vector storage of nodeWithEdges
	typedef nodeDescriptor nodeDescriptorType;                                         ///< Type of nodeDescriptor
	typedef edgeDescriptor edgeDescriptorType;                                         ///< Type of edgeDescriptor
	nodeListType m_nodeList;                                                           ///< Member to hold the list of nodes in the graph

	///@brief Default constructor
	graph(){};

	/**
	 * @brief Single argument constructor to initialize the list of nodes.
	 * @param	noOfNodes	No of nodes which are to be allocated in the graph.
	 */
	graph(size_t noOfNodes) : m_nodeList(noOfNodes){};

	/**
	 * @brief Operator [] to provide array like access to the nodes at a index in the graph
	 * @param	idx	The index at which the node is required.
	 * @return	The node at index idx-1 in the m_nodeList member.
	 */
	nodeType& operator[](size_t idx) {return this->m_nodeList[idx-1];}

	///@brief Friend operator << for decompiling the graph
	friend ostream& operator<< (ostream& out, graph& graphInst)
	{
		typename nodeListType::iterator nodeItr;
		for (nodeItr = graphInst.m_nodeList.begin(); nodeItr != graphInst.m_nodeList.end() ;nodeItr++) out << *(nodeItr);
		return out;
	}
};

/**
 * @brief [Partial Specialization]: #nodeWithEdges template is used to implement a graph node with edges where only edge
 *  type is pointer
 * @tparam	nodeProperties	The properties of node to be stored in graph. This could a structure containing various members.
 * @tparam	edgeProperties	The properties of edge between nodes to be stored in graph. This could a structure containing various members.
 * @tparam	edgeContainer	The container type which is to be used for graph edge memory allocation
 * @tparam	nodeDescriptor	The descriptor to provide access to various properties of the node.
 * @tparam	edgeDescriptor	The descriptor to provide access to various properties of the edge.
 * @details This class wraps the nodeProperties provided by the user to the graph template. While wrapping this the class adds a list
 * of edges to the nodes. This list of edges can be array-like accessed using a edge index. Also the properties of the node can be accessed
 * by node descriptors.
 */
template <typename nodeProperties, typename edgeProperties,
		  typename edgeContainer,
		  typename nodeDescriptor,
		  typename edgeDescriptor>
class nodeWithEdges <nodeProperties, edgeProperties*, edgeContainer, nodeDescriptor, edgeDescriptor>
{
public:
	typedef typename container_gen<edgeContainer,edgeProperties*>::type edgeListType;	///< Type to denote the type of memory taken by edge list
	typedef nodeDescriptor nodeDescriptorType;	///< Type of node descriptor
	typedef edgeDescriptor edgeDescriptorType;      ///< Type of edge descriptor
	nodeProperties m_nodeProperties;                ///< Member to hold all the content of a node which is to be stored in the graph
	edgeListType m_edgeList;                        ///< Member to hold all the edges which are connected to this node
	nodeDescriptorType m_nodeDescriptor;            ///< Member to provide access to various members of #m_nodeProperties
	edgeDescriptorType m_edgeDescriptor;            ///< Member to provide access to various members of edge

	///@brief Default constructor to initialize the members.
	nodeWithEdges():m_edgeList(0){};

	/**
	 * @brief Single argument constructor to initialize the members.
	 * @param	node	Reference to a user defined node which is to embedded in this class
	 */
	nodeWithEdges(nodeProperties &node):m_edgeList(0) {this->m_nodeProperties = node;}

	/**
	 * @brief Operator [] to provide array type access to node properties.
	 * @param	v	Reference to a nodeDescriptor type node which provides access to m_nodeProperties
	 * @return	Reference to member m_nodeProperties
	 */
	nodeProperties& operator[] (nodeDescriptor &v) {return this->m_nodeProperties;}

	/**
	 * @brief Operator [] to provide array type access to edge of a particular node.
	 * @param	edgeIdx	Index of edge which is to be accessed in the edge list of the node.
	 * @return	Reference to edge indexed edgeIdx - 1 in the m_edgeList
	 */
	edgeProperties& operator[] (size_t edgeIdx) {return *(this->m_edgeList[edgeIdx-1]);}

	/**
	 * @brief Member function to get the node descriptor of this class
	 * @return Reference to m_nodeDescriptor
	 */
	nodeDescriptor& getNodeDescriptor () {return (this->m_nodeDescriptor);}

	/**
	 * @brief Member function to get the edge descriptor of this class
	 * @return Reference to m_edgeDescriptor
	 */
	edgeDescriptor& getEdgeDescriptor () {return (this->m_edgeDescriptor);}

	/**
	 * @brief Member function to add a edge in this node's edge list.
	 * @param	edge	Reference to edge which is to be inserted in this node's edge list.
	 * @return Nothing
	 */
	void addEdge(edgeProperties* edge) {this->m_edgeList.push_back(edge);}

	///@brief Friend operator << for decompiling the node which is used from the graph decompile
	friend ostream& operator << (ostream& out, nodeWithEdges& node)
	{
		typename edgeListType::iterator edgeItr;
		for (edgeItr = node.m_edgeList.begin(); edgeItr != node.m_edgeList.end() ; edgeItr++) out << *(*(edgeItr));
		return out;
	}
};

/**
 * @brief [Partial Specialization]: #graph data structure for edge of pointer type
 * @tparam	nodeProperties	User defined type which is to be inserted into the graph
 * @tparam	edgeProperties	User defined type which is to be inserted into the nodes of the graph
 * @tparam	nodeContainer	The container type which is to be used for graph node memory allocation
 * @tparam	edgeContainer	The container type which is to be used for graph edge memory allocation
 * @tparam	nodeDescriptor	The descriptor which provides access to node's properties
 * @tparam	edgeDescriptor	The descriptor which provides access to edge's properties
 *
 * @details The general template only requires first two template arguments to be provided by the user. All of the rest have default
 * values assigned. The memory of nodes and edges is by default inserted into a std::vector. @n
 */
template <typename nodeProperties, typename edgeProperties, typename nodeContainer ,
		  typename edgeContainer ,typename nodeDescriptor,typename edgeDescriptor >
class graph<nodeProperties, edgeProperties*, nodeContainer, edgeContainer, nodeDescriptor, edgeDescriptor>
{
public:
	typedef nodeWithEdges<nodeProperties, edgeProperties*, edgeContainer> nodeType;		///< nodeProperties wrapper type which contains edges
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListType;         ///< vector storage of nodeWithEdges
	typedef nodeDescriptor nodeDescriptorType;                                         ///< Type of nodeDescriptor
	typedef edgeDescriptor edgeDescriptorType;                                         ///< Type of edgeDescriptor
	nodeListType m_nodeList;                                                           ///< Member to hold the list of nodes in the graph

	///@brief Default constructor
	graph(){};

	/**
	 * @brief Single argument constructor to initialize the list of nodes.
	 * @param	noOfNodes	No of nodes which are to be allocated in the graph.
	 */
	graph(size_t noOfNodes) : m_nodeList(noOfNodes){};

	/**
	 * @brief Operator [] to provide array like access to the nodes at a index in the graph
	 * @param	idx	The index at which the node is required.
	 * @return	The node at index idx-1 in the m_nodeList member.
	 */
	nodeType& operator[](size_t idx) {return this->m_nodeList[idx-1];}

	///@brief Friend operator << for decompiling the graph
	friend ostream& operator<< (ostream& out, graph& graphInst)
	{
		typename nodeListType::iterator nodeItr;
		for (nodeItr = graphInst.m_nodeList.begin(); nodeItr != graphInst.m_nodeList.end() ;nodeItr++) out << *(nodeItr);
		return out;
	}
};
#endif /* UTILS_GRAPH_INCLUDE_GRAPH_HPP_ */
