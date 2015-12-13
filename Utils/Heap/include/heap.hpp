/**
 *  @file heap.hpp
 *
 *  Created on: 01-Aug-2015
 *  @author: Karan Talreja
 *  @details This file contains implementation of heap data structure.
 */
#ifndef UTILS_HEAP_INCLUDE_HEAP_HPP_
#define UTILS_HEAP_INCLUDE_HEAP_HPP_

#include <iostream>
#include <vector>
#include <type_traits>
using namespace std;

/**
 * @brief #basic_heap_traits provides comparator functions required for implementing heap functionality.
 * @tparam T Type of nodes to be kept in heap
 */
template<class T>
class basic_heap_traits
{
public:
	///@brief Member function to provide == operator support.
	static bool eq (T& a, T& b);

	///@brief Member function to provide < operator support.
	static bool lt (T& a, T& b);
};

/**
 * @brief [General Template]:#basic_heap_min_traits for providing min heap.
 * @tparam T 				Type of nodes to be kept in heap
 * @tparam isFundamental 	bool to know whether the type T is fundamental(int, char, size_t etc..) or not.
 * @details The second template parameter is required to provide partial specializations for ease of comparison between fundamental types.
 * The template std::remove_pointer removes the pointer from type. std::is_fundamental<>::value provides a bool for the second class template
 * parameter. @n
 * @b Specializations @b available: @n
 * #basic_heap_min_traits< T , true >	// Non-pointer fundamental types @n
 * #basic_heap_min_traits< T , false >	// Non-pointer non-fundamental types @n
 * #basic_heap_min_traits< T*, true >	// pointer fundamental types @n
 * #basic_heap_min_traits< T*, false >	// pointer non-fundamental types @n
 */
template <class T, bool isFundamental = std::is_fundamental< typename std::remove_pointer<T>::type >::value > class basic_heap_min_traits{};

/**
 * @brief [General Template]:#basic_heap_max_traits for providing max heap.
 * @tparam T 				Type of nodes to be kept in heap
 * @tparam isFundamental 	bool to know whether the type T is fundamental(int, char, size_t etc..) or not.
 * @details The second template parameter is required to provide partial specializations for ease of comparison between fundamental types.
 * The template std::remove_pointer removes the pointer from type. std::is_fundamental<>::value provides a bool for the second class template
 * parameter. @n
 * @b Specializations @b available: @n
 * #basic_heap_max_traits< T , true >	// Non-pointer fundamental types @n
 * #basic_heap_max_traits< T , false >	// Non-pointer non-fundamental types @n
 * #basic_heap_max_traits< T*, true >	// pointer fundamental types @n
 * #basic_heap_max_traits< T*, false >	// pointer non-fundamental types @n
 */
template <class T, bool isFundamental = std::is_fundamental< typename std::remove_pointer<T>::type >::value > class basic_heap_max_traits{};

/**
 * @brief [Partial Specialization]:#basic_heap_min_traits for providing min heap for fundamental types.
 * @tparam T 				Type of nodes to be kept in heap
 * @details basic_heap_min_traits<T,true> provides member function of '==' , '<' and '<=' operators. Second template
 * parameter is specialized as true to easily compare the member function arguments.
 */
template <class T>
class basic_heap_min_traits<T,true> : public basic_heap_traits <T>
{
public:
	///@brief Member function to provide == operator support.
	static bool eq (T& a, T& b) {return a == b ? true : false;}

	///@brief Member function to provide < operator support.
	static bool lt (T& a, T& b) {return a < b ? true : false;}

	///@brief Member function to provide <= operator support.
	static bool lte (T& a, T& b)
	{
		if (true == basic_heap_min_traits<T>::eq(a,b)) return true;
		return basic_heap_min_traits<T>::lt(a,b);
	}
};

/**
 * @brief [Partial Specialization]:#basic_heap_min_traits for providing min heap for non-fundamental types.
 * @tparam T 				Type of nodes to be kept in heap. Must contain a static member function T::getKey(T)
 * @details basic_heap_min_traits<T,false> provides member function of '==' , '<' and '<=' operators. Second template
 * parameter is specialized as false.
 */
template <class T>
class basic_heap_min_traits<T,false> : public basic_heap_traits <T>
{
public:
	///@brief Member function to provide == operator support.
	static bool eq (T& a, T& b) {return T::getKey(a) == T::getKey(b) ? true : false;}

	///@brief Member function to provide < operator support.
	static bool lt (T& a, T& b) {return T::getKey(a) < T::getKey(b) ? true : false;}

	///@brief Member function to provide <= operator support.
	static bool lte (T& a, T& b)
	{
		if (true == basic_heap_min_traits<T>::eq(a,b)) return true;
		return basic_heap_min_traits<T>::lt(a,b);
	}
};

/**
 * @brief [Partial Specialization]:#basic_heap_max_traits for providing max heap for fundamental types.
 * @tparam T 				Type of nodes to be kept in heap
 * @details basic_heap_max_traits<T,true> provides member function of '==' , '<' and '<=' operators. Second template
 * parameter is specialized as true to easily compare the member function arguments.
 */
template <class T>
class basic_heap_max_traits<T,true> : public basic_heap_traits <T>
{
public:
	///@brief Member function to provide == operator support.
	static bool eq (T& a, T& b) {return a == b ? true : false;}

	///@brief Member function to provide < operator support. Since this is max heap, '<' means '>'.
	static bool lt (T& a, T& b) {return a > b ? true : false;}

	///@brief Member function to provide <= operator support.Since this is max heap, '<=' means '>='.
	static bool lte (T& a, T& b)
	{
		if (true == basic_heap_max_traits<T>::eq(a,b)) return true;
		return basic_heap_max_traits<T>::lt(a,b);
	}
};

/**
 * @brief [Partial Specialization]:#basic_heap_max_traits for providing max heap for non-fundamental types.
 * @tparam T 				Type of nodes to be kept in heap. Must contain a static member function T::getKey(T)
 * @details basic_heap_max_traits<T,false> provides member function of '==' , '<' and '<=' operators. Second template
 * parameter is specialized as false.
 */
template <class T>
class basic_heap_max_traits<T,false> : public basic_heap_traits <T>
{
public:
	///@brief Member function to provide == operator support.
	static bool eq (T& a, T& b) {return T::getKey(a) == T::getKey(b) ? true : false;}

	///@brief Member function to provide < operator support.Since this is max heap, '<' means '>'.
	static bool lt (T& a, T& b) {return T::getKey(a) > T::getKey(b) ? true : false;}

	///@brief Member function to provide <= operator support.Since this is max heap, '<=' means '>='.
	static bool lte (T& a, T& b)
	{
		if (true == basic_heap_max_traits<T>::eq(a,b)) return true;
		return basic_heap_max_traits<T>::lt(a,b);
	}
};

/**
 * @brief [Partial Specialization]:#basic_heap_min_traits for providing min heap for pointers of fundamental types.
 * @tparam T 				Type of nodes to be kept in heap
 * @details basic_heap_min_traits<T*,true> provides member function of '==' , '<' and '<=' operators. Second template
 * parameter is specialized as true to easily compare the member function arguments.
 */
template <class T>
class basic_heap_min_traits<T*,true> : public basic_heap_traits <T>
{
public:
	///@brief Member function to provide == operator support.
	static bool eq (T* &a, T* &b) {return *a == *b ? true : false;}

	///@brief Member function to provide < operator support.
	static bool lt (T* &a, T* &b) {return *a < *b ? true : false;}

	///@brief Member function to provide <= operator support.
	static bool lte (T* &a, T* &b)
	{
		if (true == basic_heap_min_traits<T*>::eq(a,b)) return true;
		return basic_heap_min_traits<T*>::lt(a,b);
	}
};

/**
 * @brief [Partial Specialization]:#basic_heap_min_traits for providing min heap for pointers of non-fundamental types.
 * @tparam T 				Type of nodes to be kept in heap. Must contain a static member function T::getKey(T)
 * @details basic_heap_min_traits<T*,false> provides member function of '==' , '<' and '<=' operators. Second template
 * parameter is specialized as false.
 */
template <class T>
class basic_heap_min_traits<T*,false> : public basic_heap_traits <T>
{
public:
	///@brief Member function to provide == operator support.
	static bool eq (T* &a, T* &b) {return T::getKey(*a) == T::getKey(*b) ? true : false;}

	///@brief Member function to provide < operator support.
	static bool lt (T* &a, T* &b) {return T::getKey(*a) < T::getKey(*b) ? true : false;}

	///@brief Member function to provide <= operator support.
	static bool lte (T* &a, T* &b)
	{
		if (true == basic_heap_min_traits<T*>::eq(a,b)) return true;
		return basic_heap_min_traits<T*>::lt(a,b);
	}
};

/**
 * @brief [Partial Specialization]:#basic_heap_max_traits for providing max heap for pointers of fundamental types.
 * @tparam T 				Type of nodes to be kept in heap
 * @details basic_heap_max_traits<T*,true> provides member function of '==' , '<' and '<=' operators. Second template
 * parameter is specialized as true to easily compare the member function arguments.
 */
template <class T>
class basic_heap_max_traits<T*,true> : public basic_heap_traits <T>
{
public:
	///@brief Member function to provide == operator support.
	static bool eq (T* &a, T* &b) {return *a == *b ? true : false;}

	///@brief Member function to provide < operator support. Since this is max heap, '<' means '>'.
	static bool lt (T* &a, T* &b) {return *a > *b ? true : false;}

	///@brief Member function to provide <= operator support.Since this is max heap, '<=' means '>='.
	static bool lte (T* &a, T* &b)
	{
		if (true == basic_heap_max_traits<T*>::eq(a,b)) return true;
		return basic_heap_max_traits<T*>::lt(a,b);
	}
};

/**
 * @brief [Partial Specialization]:#basic_heap_max_traits for providing max heap for pointers of non-fundamental types.
 * @tparam T 				Type of nodes to be kept in heap. Must contain a static member function T::getKey(T)
 * @details basic_heap_max_traits<T*,false> provides member function of '==' , '<' and '<=' operators. Second template
 * parameter is specialized as false.
 */
template <class T>
class basic_heap_max_traits<T*,false> : public basic_heap_traits <T>
{
public:
	///@brief Member function to provide == operator support.
	static bool eq (T* &a, T* &b) {return T::getKey(*a) == T::getKey(*b) ? true : false;}

	///@brief Member function to provide < operator support. Since this is max heap, '<' means '>'.
	static bool lt (T* &a, T* &b) {return T::getKey(*a) > T::getKey(*b) ? true : false;}

	///@brief Member function to provide <= operator support.Since this is max heap, '<=' means '>='.
	static bool lte (T* &a, T* &b)
	{
		if (true == basic_heap_max_traits<T*>::eq(a,b)) return true;
		return basic_heap_max_traits<T*>::lt(a,b);
	}
};

/**
 * @brief [General Template]: #heap provides a data structure for efficient extractTop queries
 * @tparam T 		Type of nodes to be kept in heap.
 * @tparam traits 	Traits of nodes which is to kept in heap. Traits provide comparator functions.
 * @details  * @b Specializations @b available: @n
 * #heap< T* , traits >	// Pointer types @n
 */
template <class T, class traits = basic_heap_traits<T> >
class heap
{
	vector<T> m_heap;		///< Member to hold all the nodes in the heap
	size_t m_size;			///< Member to hold the size of m_heap
public:
	///@brief Constructor to initialize heap members.
	heap(): m_size(0){};

	///@brief Member function to insert a node into the heap.
	void insert(T);

	///@brief Member function to extract the top element from the heap. Largest in case of max and smallest in case of min.
	T extractTop();

	///@brief Member function to decompile the contents of the heap.
	void decompile();

	///@brief Member function to get the current size of m_heap
	size_t getSize() {return m_size;}
};

/**
 * @param[in] node	node is the object which is to be inserted into the heap.
 *
 * @details The function puts the node at the last position of the member vector. Then the index of its parent is calculated by halving
 * the size of the heap. While the parent is lesser than the child or the new node is at the top of the heap, this node is bubbled up
 * to its rightful position in the vector where its parent is always lesser than the child.
 *
 * @return Nothing
 */
template <class T, class traits>
void heap<T,traits>::insert(T node)
{
	size_t parent,child;
	T tempNode;
	m_heap.push_back(node);
	m_size++;
	child = m_size;
	parent = (child)/2;
	while((parent >=1) && (false == traits::lt(m_heap[parent-1],m_heap[child-1])))
	{
		tempNode = m_heap[child-1];
		m_heap[child-1] = m_heap[parent-1];
		m_heap[parent-1] = tempNode;
		child = parent;
		parent = parent/2;
	}
}

/**
 * @details The function extracts the top most node from the heap. The top most element is swapped with the last element of the vector.
 * Then the last element is erased which breaks the heap property. To restore the heap property, the top most element is bubbled down to
 * its correct place in the heap. This node would have two children at position 2*P and 2*P + 1. The one which is smaller of the two would be
 * swapped with the parent node. This loop would break when the smallest of the two children is greater than the parent, which means that the
 * heap property is restored. The parent is smaller than both the children.
 *
 * @retval "Smallest Node" in case of min-heap
 * @retval "Largest Node" in case of max-heap
 */
template <class T, class traits>
T heap<T,traits>::extractTop(void)
{
	T retVal = m_heap[0],tempNode;
	tempNode = m_heap[0];
	m_heap[0] = m_heap[m_size-1];
	m_heap[m_size-1] = tempNode;
	typename vector<T>::iterator itr = m_heap.begin();
	itr = itr + m_size -1;
	m_heap.erase(itr);
	m_size--;
	int parent = 1;
	int child = parent;
	while(2*parent < m_size)
	{
		child = (true == traits::lte(m_heap[(2*parent)-1],m_heap[(2*parent)])) ? 2*parent : 2*parent + 1;
		if(false == traits::lt(m_heap[parent-1],m_heap[child-1]))
		{
			tempNode = m_heap[child -1];
			m_heap[child - 1] = m_heap[parent - 1];
			m_heap[parent - 1] = tempNode;
			parent = child;
		}
		else
			break;
	}
	return retVal;
}

/**
 * @details Decompile member function for the heap which prints out the vector serially.
 * @returns Nothing
 */
template <class T, class traits>
void heap<T,traits>::decompile()
{
	for(typename vector<T>::iterator itr = m_heap.begin(); itr != m_heap.end() ;itr++) cout<< *itr <<" ";
	cout<<endl;
}

/**
 * @brief [Partial specialization]: #heap provides a data structure for efficient extractTop queries
 * @tparam T 		Pointer type of nodes to be kept in heap.
 * @tparam traits 	Traits of nodes which is to kept in heap. Traits provide comparator functions.
 */
template <class T, class traits>
class heap<T*,traits>
{
	vector<T*> m_heap;		///< Member to hold all the nodes in the heap
	size_t m_size;			///< Member to hold the size of m_heap
public:
	///@brief Constructor to initialize heap members.
	heap():m_size(0){};

	///@brief Member function to insert a node into the heap.
	void insert(T*);

	///@brief Member function to extract the top element from the heap. Largest in case of max and smallest in case of min.
	T* extractTop();

	///@brief Member function to decompile the contents of the heap.
	void decompile();

	///@brief Member function to get the current size of m_heap
	size_t getSize() {return m_size;}
};

/**
 * @param[in] node	node is the pointer to object which is to be inserted into the heap.
 *
 * @details The function puts the node at the last position of the member vector. Then the index of its parent is calculated by halving
 * the size of the heap. While the parent is lesser than the child or the new node is at the top of the heap, this node is bubbled up
 * to its rightful position in the vector where its parent is always lesser than the child.
 *
 * @return Nothing
 */
template <class T, class traits>
void heap<T*,traits>::insert(T* node)
{
	size_t parent,child;
	T* tempNode;
	m_heap.push_back(node);
	m_size++;
	child = m_size;
	parent = (child)/2;
	while((parent >=1) && (false == traits::lt(m_heap[parent-1],m_heap[child-1])))
	{
		tempNode = m_heap[child-1];
		m_heap[child-1] = m_heap[parent-1];
		m_heap[parent-1] = tempNode;
		child = parent;
		parent = parent/2;
	}
}

/**
 * @details The function extracts the top most node from the heap. The top most element is swapped with the last element of the vector.
 * Then the last element is erased which breaks the heap property. To restore the heap property, the top most element is bubbled down to
 * its correct place in the heap. This node would have two children at position 2*P and 2*P + 1. The one which is smaller of the two would be
 * swapped with the parent node. This loop would break when the smallest of the two children is greater than the parent, which means that the
 * heap property is restored. The parent is smaller than both the children.
 *
 * @retval "Smallest Node" in case of min-heap
 * @retval "Largest Node" in case of max-heap
 */
template <class T, class traits>
T* heap<T*,traits>::extractTop(void)
{
	T* retVal = m_heap[0],*tempNode;
	tempNode = m_heap[0];
	m_heap[0] = m_heap[m_size-1];
	m_heap[m_size-1] = tempNode;
	typename vector<T*>::iterator itr = m_heap.begin();
	itr = itr + m_size -1;
	m_heap.erase(itr);
	m_size--;
	int parent = 1;
	int child = parent;
	while(2*parent < m_size)
	{
		child = (true == traits::lte(m_heap[(2*parent)-1],m_heap[(2*parent)])) ? 2*parent : 2*parent + 1;
		if(false == traits::lt(m_heap[parent-1],m_heap[child-1]))
		{
			tempNode = m_heap[child -1];
			m_heap[child - 1] = m_heap[parent - 1];
			m_heap[parent - 1] = tempNode;
			parent = child;
		}
		else
			break;
	}
	return retVal;
}

/**
 * @details Decompile member function for the heap which prints out the vector serially.
 * @returns Nothing
 */
template <class T, class traits>
void heap<T*,traits>::decompile()
{
	for(typename vector<T*>::iterator itr = m_heap.begin(); itr != m_heap.end() ;itr++) cout<< *(*itr) <<" ";
	cout<<endl;
}

#endif /* UTILS_HEAP_INCLUDE_HEAP_HPP_ */
