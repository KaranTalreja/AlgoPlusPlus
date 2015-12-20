/**
 * @file GraphNode.hpp
 *
 *  Created on: 19-Dec-2015
 * @author: Karan Talreja
 */

#ifndef UTILS_GRAPH_INCLUDE_GRAPHNODE_HPP_
#define UTILS_GRAPH_INCLUDE_GRAPHNODE_HPP_

#include "GraphTraits.hpp"

template <typename nodeProperties,typename edgeProperties, typename graphType , typename edgeContainer>
class base_vertex
{
	nodeProperties internalProperties;
public:
	base_vertex(){}
	base_vertex(nodeProperties& v) : internalProperties(v){}
	typedef edge<nodeProperties, edgeProperties, graphType, edgeContainer> edgeType;
	typedef typename container_gen<edgeContainer,edgeType>::type edgeListContainerType;	///< Type to denote the type of memory taken by edge list
	typedef typename edgeListContainerType::iterator edgeDescriptor;
	typedef vertex<nodeProperties,edgeProperties,graphType,edgeContainer> nodeType;
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;
	std::vector<nodeType*> adjVertexList;
	adjVertexDescriptor adjVertexBegin () { return this->adjVertexList.begin(); }
	adjVertexDescriptor adjVertexEnd () { return this->adjVertexList.end(); }
	friend ostream& operator<< (ostream &out, base_vertex& bv)
	{
		out << " " << nodeProperties(bv);
		return out;
	}
	operator nodeProperties () {return internalProperties;}
};

template <typename nodeProperties,typename edgeProperties, typename graphType , typename edgeContainer>
class base_vertex<nodeProperties*,edgeProperties*,graphType,edgeContainer>
{
	nodeProperties* internalProperties;
public:
	base_vertex():internalProperties(NULL){}
	base_vertex(nodeProperties *v) : internalProperties(v){}
	typedef edge<nodeProperties*, edgeProperties*, graphType, edgeContainer> edgeType;
	typedef typename container_gen<edgeContainer,edgeType>::type edgeListContainerType;	///< Type to denote the type of memory taken by edge list
	typedef typename edgeListContainerType::iterator edgeDescriptor;
	typedef vertex<nodeProperties*,edgeProperties*,graphType,edgeContainer> nodeType;
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;
	std::vector<nodeType*> adjVertexList;
	adjVertexDescriptor adjVertexBegin () { return this->adjVertexList.begin(); }
	adjVertexDescriptor adjVertexEnd () { return this->adjVertexList.end(); }
	friend ostream& operator<< (ostream &out, base_vertex& bv)
	{
		out << " " << nodeProperties(bv);
		return out;
	}
	operator nodeProperties () {return *internalProperties;}
	operator nodeProperties* () {return internalProperties;}
};

template <typename nodeProperties,typename edgeProperties, typename graphType , typename edgeContainer>
class base_vertex<nodeProperties*,edgeProperties,graphType,edgeContainer>
{
	nodeProperties* internalProperties;
public:
	base_vertex() : internalProperties(NULL){}
	base_vertex(nodeProperties *v) : internalProperties(v){}
	typedef edge<nodeProperties*, edgeProperties, graphType, edgeContainer> edgeType;
	typedef typename container_gen<edgeContainer,edgeType>::type edgeListContainerType;	///< Type to denote the type of memory taken by edge list
	typedef typename edgeListContainerType::iterator edgeDescriptor;
	typedef vertex<nodeProperties*,edgeProperties,graphType,edgeContainer> nodeType;
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;
	std::vector<nodeType*> adjVertexList;
	adjVertexDescriptor adjVertexBegin () { return this->adjVertexList.begin(); }
	adjVertexDescriptor adjVertexEnd () { return this->adjVertexList.end(); }
	friend ostream& operator<< (ostream &out, base_vertex& bv)
	{
		out << " " << nodeProperties(bv);
		return out;
	}
	operator nodeProperties () {return *internalProperties;}
	operator nodeProperties* () {return internalProperties;}
};

template <typename nodeProperties,typename edgeProperties, typename graphType , typename edgeContainer>
class base_vertex<nodeProperties,edgeProperties*,graphType,edgeContainer>
{
	nodeProperties internalProperties;
public:
	base_vertex(){}
	base_vertex(nodeProperties& v) : internalProperties(v){}
	typedef edge<nodeProperties, edgeProperties*, graphType, edgeContainer> edgeType;
	typedef typename container_gen<edgeContainer,edgeType>::type edgeListContainerType;	///< Type to denote the type of memory taken by edge list
	typedef typename edgeListContainerType::iterator edgeDescriptor;
	typedef vertex<nodeProperties,edgeProperties*,graphType,edgeContainer> nodeType;
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;
	std::vector<nodeType*> adjVertexList;
	adjVertexDescriptor adjVertexBegin () { return this->adjVertexList.begin(); }
	adjVertexDescriptor adjVertexEnd () { return this->adjVertexList.end(); }
	friend ostream& operator<< (ostream &out, base_vertex& bv)
	{
		out << " " << nodeProperties(bv);
		return out;
	}
	operator nodeProperties () {return internalProperties;}
};

template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties, edgeProperties, graphTraits::directed, edgeContainer> : public base_vertex<nodeProperties,edgeProperties,graphTraits::directed, edgeContainer>
{
	typedef base_vertex<nodeProperties,edgeProperties,graphTraits::directed, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;
	using typename baseClass::edgeType;
private:
	edgeListContainerType in_edges;
	edgeListContainerType out_edges;
public:
	vertex(){}
	vertex(nodeProperties& v) : base_vertex<nodeProperties,edgeProperties,graphTraits::directed,edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;
	edgeDescriptor inBegin() {return in_edges.begin();}
	edgeDescriptor inEnd() {return in_edges.end();}
	edgeDescriptor outBegin() {return out_edges.begin();}
	edgeDescriptor outEnd() {return out_edges.end();}
	void addInEdge(edgeType e) { this->in_edges.push_back(e); }
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};

template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties*, edgeProperties*, graphTraits::directed, edgeContainer> : public base_vertex<nodeProperties*,edgeProperties*,graphTraits::directed, edgeContainer>
{
	typedef base_vertex<nodeProperties*,edgeProperties*,graphTraits::directed, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;
	using typename baseClass::edgeType;
private:
	edgeListContainerType in_edges;
	edgeListContainerType out_edges;
public:
	vertex(){}
	vertex(nodeProperties *v) : base_vertex<nodeProperties*,edgeProperties*,graphTraits::directed,edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;
	edgeDescriptor inBegin() {return in_edges.begin();}
	edgeDescriptor inEnd() {return in_edges.end();}
	edgeDescriptor outBegin() {return out_edges.begin();}
	edgeDescriptor outEnd() {return out_edges.end();}
	void addInEdge(edgeType e) { this->in_edges.push_back(e); }
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};

template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties*, edgeProperties, graphTraits::directed, edgeContainer> : public base_vertex<nodeProperties*,edgeProperties,graphTraits::directed, edgeContainer>
{
	typedef base_vertex<nodeProperties*,edgeProperties,graphTraits::directed, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;
	using typename baseClass::edgeType;
private:
	edgeListContainerType in_edges;
	edgeListContainerType out_edges;
public:
	vertex(){}
	vertex(nodeProperties *v) : base_vertex<nodeProperties*,edgeProperties,graphTraits::directed,edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;
	edgeDescriptor inBegin() {return in_edges.begin();}
	edgeDescriptor inEnd() {return in_edges.end();}
	edgeDescriptor outBegin() {return out_edges.begin();}
	edgeDescriptor outEnd() {return out_edges.end();}
	void addInEdge(edgeType e) { this->in_edges.push_back(e); }
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};

template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties, edgeProperties*, graphTraits::directed, edgeContainer> : public base_vertex<nodeProperties,edgeProperties*,graphTraits::directed, edgeContainer>
{
	typedef base_vertex<nodeProperties,edgeProperties*,graphTraits::directed, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;
	using typename baseClass::edgeType;
private:
	edgeListContainerType in_edges;
	edgeListContainerType out_edges;
public:
	vertex(){}
	vertex(nodeProperties& v) : base_vertex<nodeProperties,edgeProperties*,graphTraits::directed,edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;
	edgeDescriptor inBegin() {return in_edges.begin();}
	edgeDescriptor inEnd() {return in_edges.end();}
	edgeDescriptor outBegin() {return out_edges.begin();}
	edgeDescriptor outEnd() {return out_edges.end();}
	void addInEdge(edgeType e) { this->in_edges.push_back(e); }
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};

template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties, edgeProperties, graphTraits::bidirectional, edgeContainer> : public base_vertex<nodeProperties,edgeProperties,graphTraits::bidirectional , edgeContainer>
{
	typedef base_vertex<nodeProperties,edgeProperties,graphTraits::bidirectional, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;
	using typename baseClass::edgeType;
private:
	edgeListContainerType out_edges;
public:
	vertex(){}
	vertex(nodeProperties& v) : base_vertex<nodeProperties,edgeProperties,graphTraits::bidirectional, edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;
	edgeDescriptor outBegin() {return out_edges.begin();}
	edgeDescriptor outEnd() {return out_edges.end();}
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};

template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties*, edgeProperties*, graphTraits::bidirectional, edgeContainer> : public base_vertex<nodeProperties*,edgeProperties*,graphTraits::bidirectional , edgeContainer>
{
	typedef base_vertex<nodeProperties*,edgeProperties*,graphTraits::bidirectional, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;
	using typename baseClass::edgeType;
private:
	edgeListContainerType out_edges;
public:
	vertex(){}
	vertex(nodeProperties *v) : base_vertex<nodeProperties*,edgeProperties*,graphTraits::bidirectional, edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;
	edgeDescriptor outBegin() {return out_edges.begin();}
	edgeDescriptor outEnd() {return out_edges.end();}
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};

template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties*, edgeProperties, graphTraits::bidirectional, edgeContainer> : public base_vertex<nodeProperties*,edgeProperties,graphTraits::bidirectional , edgeContainer>
{
	typedef base_vertex<nodeProperties*,edgeProperties,graphTraits::bidirectional, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;
	using typename baseClass::edgeType;
private:
	edgeListContainerType out_edges;
public:
	vertex(){}
	vertex(nodeProperties *v) : base_vertex<nodeProperties*,edgeProperties,graphTraits::bidirectional, edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;
	edgeDescriptor outBegin() {return out_edges.begin();}
	edgeDescriptor outEnd() {return out_edges.end();}
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};

template <typename nodeProperties, typename edgeProperties, typename edgeContainer>
class vertex <nodeProperties, edgeProperties*, graphTraits::bidirectional, edgeContainer> : public base_vertex<nodeProperties,edgeProperties*,graphTraits::bidirectional , edgeContainer>
{
	typedef base_vertex<nodeProperties,edgeProperties*,graphTraits::bidirectional, edgeContainer> baseClass;
public:
	using typename baseClass::edgeListContainerType;
	using typename baseClass::edgeType;
private:
	edgeListContainerType out_edges;
public:
	vertex(){}
	vertex(nodeProperties& v) : base_vertex<nodeProperties,edgeProperties*,graphTraits::bidirectional, edgeContainer>(v){}
	using typename baseClass::edgeDescriptor;
	edgeDescriptor outBegin() {return out_edges.begin();}
	edgeDescriptor outEnd() {return out_edges.end();}
	void addOutEdge(edgeType e)
	{
		this->adjVertexList.push_back(e.sink);
		this->out_edges.push_back(e);
	}
};
#endif /* UTILS_GRAPH_INCLUDE_GRAPHNODE_HPP_ */
