/**
 * @file Tree.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_BINARYSEARCHTREE_H_
#define SRC_TREE_BINARYSEARCHTREE_H_

#include "BinaryTree.h"
#include "Node.h"

namespace tree {

/**
 * This class implements the needed methods in a binary tree
 */
template<typename T>
class BinarySearchTree: public BinaryTree<T> {
private:
	/**
	 * Removes a node in the tree with a given value
	 * @param[in] root Root node
	 * @param[in] value Value to remove in the node
	 * @return Returns whether it has been possible to remove the element from the tree (e.g. it will
	 * return false if the value does not exist)
	 */
	bool deleteNode(Node<T>* rootNode, const T& value);
	/**
	 * Search the node with the minimum value
	 * @param[in] rootNode Node where to start the search from
	 * @return Returns the node with the lowest value, starting from the rootNode (or
	 * nullptr in case the rootnode is nullptr)
	 */
	Node<T>* minNode(Node<T>* rootNode) const;
public:
	/**
	 * Class constructor
	 */
	BinarySearchTree();
	/**
	 * Class destructor (calls the deleteTree() method)
	 */
	~BinarySearchTree();
	/**
	 * Insert a new node with a given value in the tree
	 * @param[in] node Node to insert in the tree
	 */
	void insertNode(Node<T>* node);
	/**
	 * Removes a node with a given value
	 * @param[in] key Key to remove from the tree
	 * @see BinaryTree
	 */
	bool deleteNode(const T& key);
};

} /* namespace tree */

#endif /* SRC_TREE_BINARYSEARCHTREE_H_ */
