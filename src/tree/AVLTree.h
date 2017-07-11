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
};

} /* namespace tree */

#endif /* SRC_TREE_AVLTREE_H_ */
