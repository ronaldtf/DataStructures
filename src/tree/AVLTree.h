/**
 * @file AVLTree.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_AVLTREE_H_
#define SRC_TREE_AVLTREE_H_

#include "BinarySearchTree.h"
#include "Node.h"

#include <stack>

namespace tree {

/**
 * This class implements an AVL tree as a particular case of a BinaryTree.
 * The difference between this and a BinarySearchTree is that this tree
 * is balanced, i.e. the difference between the shortest and the longest
 * path is, as much, 1
 */
template<typename T>
class AVLTree: public BinarySearchTree<T> {
public:
	/**
	 * Class constructor
	 */
	AVLTree();
	/**
	 * Insert a new node with a given value in the tree
	 * @param[in] node Node to insert in the tree
	 * @return Returns true if the node has been inserted, or false
	 * otherwise
	 * @see BinaryTree
	 */
	bool insertNode(Node<T>* node);
	/**
	 * Removes a node with a given value
	 * @param[in] key Key to remove from the tree
	 * @see BinaryTree
	 */
	bool deleteNode(const T& key);
private:
	/**
	 * Set the child in the right place for the parent, or to the root if
	 * the parent is NULL
	 * @param[in|out] root   Root node of the tree
	 * @param[in|out] parent Parent node
	 * @param[in|out] child  Child node
	 */
	void pointParentToChild(Node<T>** root, Node<T>** parent, Node<T>** child);
	/**
	 * This method balances the tree by applying the RR, RL, LL, LR movements regarding
	 * the condition of the balancing
	 * @param[in] parent Parent of the unbalanced subtree
	 * @param[in] stackTree Stack with the nodes from the bottom to the top after the
	 * insertion
	 * @param[in] nodeKey Key of the last node inserted
	 */
	void balanceTree(std::stack<Node<T>*>& stackTree, T nodeKey);
};

} /* namespace tree */

#endif /* SRC_TREE_AVLTREE_H_ */
