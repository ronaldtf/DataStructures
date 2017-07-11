/**
 * @file AVLTree.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_AVLTREE_H_
#define SRC_TREE_AVLTREE_H_

#include "BinaryTree.h"
#include "Node.h"

namespace tree {

/**
 * This class implements an AVL tree as a particular case of a BinaryTree.
 * The difference between this and a BinarySearchTree is that this tree
 * is balanced, i.e. the difference between the shortest and the longest
 * path is, as much, 1
 */
template<typename T>
class AVLTree: public BinaryTree<T> {
public:
	/**
	 * Class constructor
	 */
	AVLTree();
	/**
	 * Insert a new node with a given value in the tree
	 * @param[in] node Node to insert in the tree
	 * @see BinaryTree
	 */
	void insertNode(const Node<T>* node);
	/**
	 * Removes a node with a given value
	 * @param[in] key Key to remove from the tree
	 * @see BinaryTree
	 */
	bool deleteNode(const T& key);
};

} /* namespace tree */

#endif /* SRC_TREE_AVLTREE_H_ */
