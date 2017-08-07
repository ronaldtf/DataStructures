/**
 * @file Btree.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_BTREE_H_
#define SRC_TREE_BTREE_H_

#include "BNode.h"

#include <list>

namespace tree {

template <typename T>
class Btree {
private:
	unsigned short d;
	BNode<T>* root;
public:
	/**
	 * Class constructor.
	 * @param[in] d: minimum degree term. This defines the number of
	 *               minimum keys per node (d-1) and the maximum
	 *                (2*d-1).
	 */
	Btree(unsigned short d = 1);
	/**
	 * Class destructor
	 */
	virtual ~Btree();
	/**
	 * Search a given key in the b-tree
	 * @param[in] key Key to find
	 * @return Returns the node which contains the key, or nullptr
	 * if it is not found
	 */
	BNode<T>* search(const T& key);
	/**
	 * Go along the tree in an in-order order.
	 * @param[out] orderedList List in an in-order order
	 */
	void getInorder(std::list<T>& orderedList) const;
	/**
	 * Go along the tree in n pre-order order.
	 * @param[out] orderedList List in a pre-order order
	 */
	void getPreorder(std::list<T>& orderedList) const;
	/**
	 * Go along the tree in a post-order order.
	 * @param[out] orderedList List in a post-order order
	 */
	void getPostorder(std::list<T>& orderedList) const;
	/**
	 * Determines whether a node is a leaf node or not
	 * @param[in] node Node to be checked
	 * @return Returns whether the node is a leaf node or not
	 */
	bool isLeaf(BNode<T>* node);
	/**
	 * Insert an element into the tree
	 * @param[in] element Element to insert in the tree
	 * @return Returns whether the element has been inserted or, however, it
	 * already existed in the tree
	 */
	bool insert(T& element);
private:
	/**
	 * Go along the tree in an in-order order.
	 * @param[in] root Root node
	 * @param[out] orderedList List in an in-order order
	 */
	void getInorder(BNode<T>* root, std::list<T>& orderedList) const;
	/**
	 * Go along the tree in n pre-order order.
	 * @param[in] root Root node
	 * @param[out] orderedList List in a pre-order order
	 */
	void getPreorder(BNode<T>* root, std::list<T>& orderedList) const;
	/**
	 * Go along the tree in a post-order order.
	 * @param[in] root Root node
	 * @param[out] orderedList List in a post-order order
	 */
	void getPostorder(BNode<T>* root, std::list<T>& orderedList) const;
};

} /* namespace tree */

#endif /* SRC_TREE_BTREE_H_ */
