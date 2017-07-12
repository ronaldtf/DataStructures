/**
 * @file BinaryTree.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_BINARYTREE_H_
#define SRC_TREE_BINARYTREE_H_

#include <iostream>
#include <list>
#include <vector>

#include "Node.h"

namespace tree {

/**
 * This class defines the method for a binary tree
 */
template<typename T>
class BinaryTree {
public:
	/**
	 * Insert a new node with a given value in the tree
	 * @param[in] key Node to insert in the tree
	 */
	virtual bool insertNode(Node<T>* node);
	/**
	 * Removes a node with a given value
	 * @param[in] key Key to remove from the tree
	 */
	virtual bool deleteNode(const T& key) = 0;
	/**
	 * Removes a node
	 * @param[in] node Node to remove from the tree
	 */
	bool deleteNode(Node<T>* node);
	/**
	 * Look for a node with a value
	 * @param[in] key Key to search in the tree
	 * @return Returns the node with the given value, or nullptr in case it was not found
	 */
	Node<T>* search(const T& key) const;
	/**
	 * Go along the tree in an in-order order.
	 * @param[out] orderedList List in n pre-order order
	 */
	void getInorder(std::list<Node<T>*>& orderedList) const;
	/**
	 * Go along the tree in a pre-order order.
	 * @param[out] orderedList List in n pre-order order
	 */
	void getPreorder(std::list<Node<T>*>& orderedList) const;
	/**
	 * Go along the tree in a post-order order.
	 * @param[out] orderedList List in n pre-order order
	 */
	void getPostorder(std::list<Node<T>*>& orderedList) const;
	/**
	 * Get the height of the tree
	 * @return Height of the tree
	 */
	unsigned int getHeight() const;
	/**
	 * Converts the tree into a printable format
	 * @return Returns the string with the tree structure
	 */
	std::string toString() const;
protected:
	/**
	 * Root node in the binary tree
	 */
	Node<T>* root;
	/**
	 * Class constructor
	 */
	BinaryTree();
	/**
	 * Class destructor
	 */
	~BinaryTree();

	/**
	 * Go along the tree in an in-order order.
	 * @param[in] root Root node
	 * @param[out] orderedList List in an in-order order
	 */
	void getInorder(Node<T>* root, std::list<Node<T>*>& orderedList) const;
	/**
	 * Go along the tree in n pre-order order.
	 * @param[in] root Root node
	 * @param[out] orderedList List in a pre-order order
	 */
	void getPreorder(Node<T>* root, std::list<Node<T>*>& orderedList) const;
	/**
	 * Go along the tree in a post-order order.
	 * @param[in] root Root node
	 * @param[out] orderedList List in a post-order order
	 */
	void getPostorder(Node<T>* root, std::list<Node<T>*>& orderedList) const;
	/**
	 * Search an element in the tree
	 * @param[in] rootNode Node where to start the search from
	 * @param[in] keyValue Value to search in the tree
	 * @param[out] parent Parent node for the searched node (nullptr in case the value was
	 * not found or the value is in the root node)
	 * @return Returns the node with the given value, or nullptr in case it was not found
	 */
	Node<T>* search(Node<T>* rootNode, const T& keyValue,
			Node<T>** parent) const;
	/**
	 * Deletes the tree from a node
	 * @param[in] root Node to start removing
	 */
	void deleteTree(Node<T>* root);
	/**
	 * Converts an element of type T to a string
	 * @param[in] element Element to convert
	 * @return String containing the element value
	 */
	std::string t2str(T element) const;

	/**
	 * This method obtain the strings corresponding to each tree level
	 * @param[in] root Root node for the tree
	 * @param[in] level Current level to process
	 * @param[in] height Tree height
	 * @param[out] strs List of strings corresponding to each level
	 */
	void getStrings(Node<T>* root, const unsigned int level,
			const unsigned int height, std::vector<std::string>& strs) const;
	/**
	 * Get the height of the tree
	 * @param[in] root Node where to start calculating the height from
	 * @return Tree height
	 */
	unsigned int getHeight(Node<T>* root) const;

};

} // end namespace tree

#endif /* SRC_TREE_BINARYTREE_H_ */
