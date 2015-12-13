/**
 *  @file main.cpp
 *
 *  Created on: 01-Aug-2015
 *  @author: Karan Talreja
 *  @details This file contains a sample testing scenario for the heap data structure. All the data structures present in the file
 *  are in a namespace called HeapTest. The test tries to add nodes into heap and run some fundamental operations on them.
 */
#include <heap.hpp>
#include <type_traits>

/**
 * @brief HeapTest to wrap the object model specific to this testing suite.
 */
namespace HeapTest
{

/**
 * @brief Node which is to be inserted in the heap
 * @details Since this class cannot be a fundamental type, needs to have a static member function getKey which provides the necessary
 * support required by the heap data structure.
 */
class heapNode
{
	int weight;		///< Member to keep the weight attribute of the heapNode
public:
	///@brief Member function to get the key required by heap.
	static int getKey(heapNode& a) {return a.weight;}

	///@brief Friend operator << for decompiling the node which is used from the heap decompile
	friend ostream& operator << (ostream& out, heapNode& a) { return out << a.weight;}

	///@brief Constructor to initialize class members
	heapNode(){weight = 0;}

	/**
	 * @brief Single argument constructor to initialize member weight.
	 * @param[in] n	The value to be assigned to member weight.
	 */
	heapNode(int n) {weight = n;}
};
}

using namespace HeapTest;
int main()
{
	/**
	 * The following snippet makes a max heap of a pointer to fundamental type and checks basic heap operations
	 * Sample Output:
	 * 10 9 6 7 8 2 5 1 4 3
	 * 9 8 6 7 3 2 5 1 4
	 * 9 8 6 7 3 2 5 1 4 1
	 */
	heap<size_t*,basic_heap_max_traits<size_t*> > a;
	for (size_t i = 1; i <= 10 ; i++) a.insert(new size_t(i));
	a.decompile();
	a.extractTop();
	a.decompile();
	a.insert(new size_t(1));
	a.decompile();

	/**
	 * The following snippet makes a max heap of a pointer to non-fundamental type and checks basic heap operations
	 * Sample Output:
	 * 10 9 6 7 8 2 5 1 4 3
	 * 9 8 6 7 3 2 5 1 4
	 * 9 8 6 7 3 2 5 1 4 1
	 */
	heap<heapNode*,basic_heap_max_traits<heapNode*> > aNf1;
	for (int i = 1; i <= 10 ; i++) aNf1.insert(new heapNode(i));
	aNf1.decompile();
	aNf1.extractTop();
	aNf1.decompile();
	aNf1.insert(new heapNode(1));
	aNf1.decompile();

	/**
	 * The following snippet makes a max heap of a non-fundamental type and checks basic heap operations
	 * Sample Output:
	 * 10 9 6 7 8 2 5 1 4 3
	 * 9 8 6 7 3 2 5 1 4
	 * 9 8 6 7 3 2 5 1 4 1
	 */
	heap<heapNode,basic_heap_max_traits<heapNode> > aNf;
	for (int i = 1; i <= 10 ; i++) aNf.insert(*new heapNode(i));
	aNf.decompile();
	aNf.extractTop();
	aNf.decompile();
	aNf.insert(*new heapNode(1));
	aNf.decompile();
	return 0;
}
