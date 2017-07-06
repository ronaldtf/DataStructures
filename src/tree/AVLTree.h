/**
 * @file AVLTree.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_AVLTREE_H_
#define SRC_TREE_AVLTREE_H_

#include "BinaryTree.h"

namespace tree {

template<typename T>
class AVLTree : public BinaryTree<T> {
public:
	AVLTree();
	/**
	 * Insert a new node with a given value in the tree
	 * @param[in] value Value to insert in the tree
	 * @see BinaryTree
	 */
	void insertNode(const T& value);
	/**
	 * Removes a node with a given value
	 * @param[in] value Value to remove from the tree
	 * @see BinaryTree
	 */
	bool deleteNode(const T& value);
	/**
	 * Look for a node with a value
	 * @param[in] element Value to search in the tree
	 * @return Returns the node with the given value, or nullptr in case it was not found
	 * @see BinaryTree
	 */
	Node<T>* search(const T& element) const;
	/**
	 * Go along the tree in an in-order order.
	 * @param[out] orderedList List in n pre-order order
	 * @see BinaryTree
	 */
	void getInorder(std::list<T>& orderedList);
	/**
	 * Go along the tree in a pre-order order.
	 * @param[out] orderedList List in n pre-order order
	 * @see BinaryTree
	 */
	void getPreorder(std::list<T>& orderedList);
	/**
	 * Go along the tree in a post-order order.
	 * @param[out] orderedList List in n pre-order order
	 * @see BinaryTree
	 */
	void getPostorder(std::list<T>& orderedList);
	/**
	 * Get the height of the tree
	 * @param[in] root Node where to start calculating the height from
	 * @return Tree height
	 * @see BinaryTree
	 */
	unsigned int getHeight(Node<T>* root);
};

} /* namespace tree */

#endif /* SRC_TREE_AVLTREE_H_ */
