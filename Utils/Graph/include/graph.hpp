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

template <typename nodeProperties, typename edgeProperties, typename graphType,typename nodeContainer = graphTraits::listStorage,typename edgeContainer = graphTraits::listStorage> class graph;

template <typename nodeProperties, typename edgeProperties, typename graphType,typename nodeContainer = graphTraits::listStorage,typename edgeContainer = graphTraits::listStorage>
class base_graph
{
	typedef vertex<nodeProperties,edgeProperties,graphType,edgeContainer> nodeType;
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListContainerType;
public:
	typedef typename nodeListContainerType::const_iterator const_iterator;
	typedef typename nodeListContainerType::iterator vertexDescriptor;
	typedef typename nodeType::edgeListContainerType::iterator edgeDescriptor;
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;
	typedef typename graphTraits::decompileFlavor decompileFlavor;
protected:
	typedef typename std::pair <vertexDescriptor, vertexDescriptor> vertexPairDescriptor;
	typedef typename std::pair <edgeDescriptor, edgeDescriptor> edgePairDescriptor;
	typedef edge<nodeProperties,edgeProperties,graphType, edgeContainer> edgeType;
public:
	decompileFlavor decompileType;
	nodeListContainerType nodeList;
	nodeProperties& operator[] (vertexDescriptor& v) {return *v;}
	edgeProperties& operator[](edgeDescriptor& e) {return *e;}
	vertexPairDescriptor vertices (){return std::make_pair(this->nodeList.begin(), this->nodeList.end());}
	vertexDescriptor addVertex (nodeProperties& v)
	{
		this->nodeList.push_back(v);
		vertexDescriptor retval = (this->nodeList.end());
		return --retval;
	}
	void setDecompileFlavor (decompileFlavor e) { this->decompileType = e;}
	decompileFlavor getDecompileFlavor () { return this->decompileType;}
	size_t size() {return nodeList.size();}
};

template <typename nodeProperties, typename edgeProperties, typename graphType,typename nodeContainer, typename edgeContainer>
class base_graph <nodeProperties*, edgeProperties* , graphType, nodeContainer, edgeContainer>
{
	typedef vertex<nodeProperties*,edgeProperties*,graphType,edgeContainer> nodeType;
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListContainerType;
public:
	typedef typename nodeListContainerType::const_iterator const_iterator;
	typedef typename nodeListContainerType::iterator vertexDescriptor;
	typedef typename nodeType::edgeListContainerType::iterator edgeDescriptor;
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;
	typedef typename graphTraits::decompileFlavor decompileFlavor;
protected:
	typedef typename std::pair <vertexDescriptor, vertexDescriptor> vertexPairDescriptor;
	typedef typename std::pair <edgeDescriptor, edgeDescriptor> edgePairDescriptor;
	typedef edge<nodeProperties*,edgeProperties*,graphType, edgeContainer> edgeType;
public:
	decompileFlavor decompileType;
	nodeListContainerType nodeList;
	nodeProperties* operator[] (vertexDescriptor& v) {return *v;}
	edgeProperties* operator[](edgeDescriptor& e) {return *e;}
	vertexPairDescriptor vertices (){return std::make_pair(this->nodeList.begin(), this->nodeList.end());}
	vertexDescriptor addVertex (nodeProperties *v)
	{
		this->nodeList.push_back(v);
		vertexDescriptor retval = (this->nodeList.end());
		return --retval;
	}
	void setDecompileFlavor (decompileFlavor e) { this->decompileType = e;}
	decompileFlavor getDecompileFlavor () { return this->decompileType;}
	size_t size() {return nodeList.size();}
};

template <typename nodeProperties, typename edgeProperties, typename graphType,typename nodeContainer, typename edgeContainer>
class base_graph <nodeProperties*, edgeProperties , graphType, nodeContainer, edgeContainer>
{
	typedef vertex<nodeProperties*,edgeProperties,graphType,edgeContainer> nodeType;
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListContainerType;
public:
	typedef typename nodeListContainerType::const_iterator const_iterator;
	typedef typename nodeListContainerType::iterator vertexDescriptor;
	typedef typename nodeType::edgeListContainerType::iterator edgeDescriptor;
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;
	typedef typename graphTraits::decompileFlavor decompileFlavor;
protected:
	typedef typename std::pair <vertexDescriptor, vertexDescriptor> vertexPairDescriptor;
	typedef typename std::pair <edgeDescriptor, edgeDescriptor> edgePairDescriptor;
	typedef edge<nodeProperties*,edgeProperties,graphType, edgeContainer> edgeType;
public:
	decompileFlavor decompileType;
	nodeListContainerType nodeList;
	nodeProperties* operator[] (vertexDescriptor& v) {return *v;}
	edgeProperties* operator[](edgeDescriptor& e) {return *e;}
	vertexPairDescriptor vertices (){return std::make_pair(this->nodeList.begin(), this->nodeList.end());}
	vertexDescriptor addVertex (nodeProperties *v)
	{
		this->nodeList.push_back(v);
		vertexDescriptor retval = (this->nodeList.end());
		return --retval;
	}
	void setDecompileFlavor (decompileFlavor e) { this->decompileType = e;}
	decompileFlavor getDecompileFlavor () { return this->decompileType;}
	size_t size() {return nodeList.size();}
};

template <typename nodeProperties, typename edgeProperties, typename graphType,typename nodeContainer, typename edgeContainer>
class base_graph <nodeProperties, edgeProperties* , graphType, nodeContainer, edgeContainer>
{
	typedef vertex<nodeProperties,edgeProperties*,graphType,edgeContainer> nodeType;
	typedef typename container_gen<nodeContainer,nodeType>::type nodeListContainerType;
public:
	typedef typename nodeListContainerType::const_iterator const_iterator;
	typedef typename nodeListContainerType::iterator vertexDescriptor;
	typedef typename nodeType::edgeListContainerType::iterator edgeDescriptor;
	typedef typename std::vector<nodeType*>::iterator adjVertexDescriptor;
	typedef typename graphTraits::decompileFlavor decompileFlavor;
protected:
	typedef typename std::pair <vertexDescriptor, vertexDescriptor> vertexPairDescriptor;
	typedef typename std::pair <edgeDescriptor, edgeDescriptor> edgePairDescriptor;
	typedef edge<nodeProperties,edgeProperties*,graphType, edgeContainer> edgeType;
public:
	decompileFlavor decompileType;
	nodeListContainerType nodeList;
	nodeProperties& operator[] (vertexDescriptor& v) {return *v;}
	edgeProperties& operator[](edgeDescriptor& e) {return *e;}
	vertexPairDescriptor vertices (){return std::make_pair(this->nodeList.begin(), this->nodeList.end());}
	vertexDescriptor addVertex (nodeProperties &v)
	{
		this->nodeList.push_back(v);
		vertexDescriptor retval = (this->nodeList.end());
		return --retval;
	}
	void setDecompileFlavor (decompileFlavor e) { this->decompileType = e;}
	decompileFlavor getDecompileFlavor () { return this->decompileType;}
	size_t size() {return nodeList.size();}
};

template <typename nodeProperties, typename edgeProperties,
typename nodeContainer, typename edgeContainer>
class graph <nodeProperties, edgeProperties, graphTraits::bidirectional,nodeContainer,edgeContainer> : public base_graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer, edgeContainer> baseClass;
	typedef graph<nodeProperties,edgeProperties,graphTraits::bidirectional,nodeContainer, edgeContainer> thisClass;
public:
	using typename baseClass::edgePairDescriptor;
	using typename baseClass::vertexPairDescriptor;
	using typename baseClass::edgeDescriptor;
	using typename baseClass::vertexDescriptor;
	using typename baseClass::adjVertexDescriptor;
	using typename baseClass::edgeType;
	graph(){}
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties& e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addOutEdge(edgeType(&(*sink),&(*source),e));
	}

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

template <typename nodeProperties, typename edgeProperties,
typename nodeContainer, typename edgeContainer>
class graph <nodeProperties*, edgeProperties*, graphTraits::bidirectional,nodeContainer,edgeContainer> : public base_graph<nodeProperties*,edgeProperties*,graphTraits::bidirectional,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties*,edgeProperties*,graphTraits::bidirectional,nodeContainer, edgeContainer> baseClass;
	typedef graph<nodeProperties*,edgeProperties*,graphTraits::bidirectional,nodeContainer, edgeContainer> thisClass;
public:
	using typename baseClass::edgePairDescriptor;
	using typename baseClass::vertexPairDescriptor;
	using typename baseClass::edgeDescriptor;
	using typename baseClass::vertexDescriptor;
	using typename baseClass::adjVertexDescriptor;
	using typename baseClass::edgeType;
	graph(){}
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties *e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addOutEdge(edgeType(&(*sink),&(*source),e));
	}

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

template <typename nodeProperties, typename edgeProperties,
typename nodeContainer, typename edgeContainer>
class graph <nodeProperties*, edgeProperties, graphTraits::bidirectional,nodeContainer,edgeContainer> : public base_graph<nodeProperties*,edgeProperties,graphTraits::bidirectional,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties*,edgeProperties,graphTraits::bidirectional,nodeContainer, edgeContainer> baseClass;
	typedef graph<nodeProperties*,edgeProperties,graphTraits::bidirectional,nodeContainer, edgeContainer> thisClass;
public:
	using typename baseClass::edgePairDescriptor;
	using typename baseClass::vertexPairDescriptor;
	using typename baseClass::edgeDescriptor;
	using typename baseClass::vertexDescriptor;
	using typename baseClass::adjVertexDescriptor;
	using typename baseClass::edgeType;
	graph(){}
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties& e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addOutEdge(edgeType(&(*sink),&(*source),e));
	}

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

template <typename nodeProperties, typename edgeProperties,
typename nodeContainer, typename edgeContainer>
class graph <nodeProperties, edgeProperties*, graphTraits::bidirectional,nodeContainer,edgeContainer> : public base_graph<nodeProperties,edgeProperties*,graphTraits::bidirectional,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties,edgeProperties*,graphTraits::bidirectional,nodeContainer, edgeContainer> baseClass;
	typedef graph<nodeProperties,edgeProperties*,graphTraits::bidirectional,nodeContainer, edgeContainer> thisClass;
public:
	using typename baseClass::edgePairDescriptor;
	using typename baseClass::vertexPairDescriptor;
	using typename baseClass::edgeDescriptor;
	using typename baseClass::vertexDescriptor;
	using typename baseClass::adjVertexDescriptor;
	using typename baseClass::edgeType;
	graph(){}
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties *e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addOutEdge(edgeType(&(*sink),&(*source),e));
	}

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

template <typename nodeProperties, typename edgeProperties, typename nodeContainer, typename edgeContainer>
class graph <nodeProperties, edgeProperties, graphTraits::directed,nodeContainer,edgeContainer> : public base_graph<nodeProperties,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer> baseClass;
	typedef graph<nodeProperties,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer> thisClass;
public:
	using typename baseClass::edgePairDescriptor;
	using typename baseClass::vertexPairDescriptor;
	using typename baseClass::edgeDescriptor;
	using typename baseClass::vertexDescriptor;
	using typename baseClass::adjVertexDescriptor;
	using typename baseClass::edgeType;
	graph(){};
	edgePairDescriptor in_edges(vertexDescriptor& v){return std::make_pair(v->inBegin(),v->inEnd());}
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties& e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addInEdge(edgeType(&(*source),&(*sink),e));
	}
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

template <typename nodeProperties, typename edgeProperties, typename nodeContainer, typename edgeContainer>
class graph <nodeProperties*, edgeProperties*, graphTraits::directed,nodeContainer,edgeContainer> : public base_graph<nodeProperties*,edgeProperties*,graphTraits::directed,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties*,edgeProperties*,graphTraits::directed,nodeContainer,edgeContainer> baseClass;
	typedef graph<nodeProperties*,edgeProperties*,graphTraits::directed,nodeContainer,edgeContainer> thisClass;
public:
	using typename baseClass::edgePairDescriptor;
	using typename baseClass::vertexPairDescriptor;
	using typename baseClass::edgeDescriptor;
	using typename baseClass::vertexDescriptor;
	using typename baseClass::adjVertexDescriptor;
	using typename baseClass::edgeType;
	graph(){};
	edgePairDescriptor in_edges(vertexDescriptor& v){return std::make_pair(v->inBegin(),v->inEnd());}
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties *e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addInEdge(edgeType(&(*source),&(*sink),e));
	}
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

template <typename nodeProperties, typename edgeProperties, typename nodeContainer, typename edgeContainer>
class graph <nodeProperties*, edgeProperties, graphTraits::directed,nodeContainer,edgeContainer> : public base_graph<nodeProperties*,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties*,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer> baseClass;
	typedef graph<nodeProperties*,edgeProperties,graphTraits::directed,nodeContainer,edgeContainer> thisClass;
public:
	using typename baseClass::edgePairDescriptor;
	using typename baseClass::vertexPairDescriptor;
	using typename baseClass::edgeDescriptor;
	using typename baseClass::vertexDescriptor;
	using typename baseClass::adjVertexDescriptor;
	using typename baseClass::edgeType;
	graph(){};
	edgePairDescriptor in_edges(vertexDescriptor& v){return std::make_pair(v->inBegin(),v->inEnd());}
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties& e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addInEdge(edgeType(&(*source),&(*sink),e));
	}
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

template <typename nodeProperties, typename edgeProperties, typename nodeContainer, typename edgeContainer>
class graph <nodeProperties, edgeProperties*, graphTraits::directed,nodeContainer,edgeContainer> : public base_graph<nodeProperties,edgeProperties*,graphTraits::directed,nodeContainer,edgeContainer>
{
	typedef base_graph<nodeProperties,edgeProperties*,graphTraits::directed,nodeContainer,edgeContainer> baseClass;
	typedef graph<nodeProperties,edgeProperties*,graphTraits::directed,nodeContainer,edgeContainer> thisClass;
public:
	using typename baseClass::edgePairDescriptor;
	using typename baseClass::vertexPairDescriptor;
	using typename baseClass::edgeDescriptor;
	using typename baseClass::vertexDescriptor;
	using typename baseClass::adjVertexDescriptor;
	using typename baseClass::edgeType;
	graph(){};
	edgePairDescriptor in_edges(vertexDescriptor& v){return std::make_pair(v->inBegin(),v->inEnd());}
	edgePairDescriptor out_edges(vertexDescriptor& v){return std::make_pair(v->outBegin(),v->outEnd());}
	void addEdge (vertexDescriptor& source, vertexDescriptor& sink, edgeProperties *e)
	{
		source->addOutEdge(edgeType(&(*source),&(*sink),e));
		sink->addInEdge(edgeType(&(*source),&(*sink),e));
	}
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
