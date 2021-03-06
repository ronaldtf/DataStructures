/**
 * @file Tree.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_BINARYSEARCHTREE_H_
#define SRC_TREE_BINARYSEARCHTREE_H_

#include "Node.h"

#include <list>
#include <stack>
#include <vector>

namespace tree {

/**
 * This class defines the method for a binary tree
 * NOTE: I have opted here to use a tree with pointers. However, it might be
 * implemented as an array structure where each child for a node at position X is
 * 2*(X+1)-1, 2*(X+1) - starting X at position 0.
 * The (dis)advantages of the solution implementing here regarding the array are:
 * - The array needs to be re-dimensioned when the maximum size has reached. The
 *   solution here does not need relocate array positions as it uses pointers.
 * - The access to an element of an array is 1 if we know the index. The access to
 *   the structure implemented here is log(N). However, we rarely know the index
 *   of the array by default.
 */
template<typename T>
class BinarySearchTree {
public:
	/**
	 * Class constructor
	 */
	BinarySearchTree();
	/**
	 * Class destructor
	 */
	virtual ~BinarySearchTree();
	/**
	 * Insert a new node with a given value in the tree
	 * @param[in] key Node to insert in the tree
	 */
	virtual bool insertNode(Node<T>* node);
	/**
	 * Removes a node with a given value
	 * @param[in] key Key to remove from the tree
	 */
	virtual bool deleteNode(const T& key);
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

	/**
	 * This method inserts the not in the tree
	 * @param[in] node Node to be inserted
	 * @param[in|out] stackTree List of nodes indicating the path followed to insert
	 * the new node. Note: if the stackTree is originally null, the insertion on the
	 * stack will be ignored
	 * @return Returns true if the node has been inserted, false otherwise
	 */
	bool insertNode(Node<T>* node, std::stack<Node<T>*>* stackTree);

	/**
	 * Removes a node in the tree with a given value
	 * @param[in] key Value to remove in the node
	 * @param[in|out] stackTree Stack which indicates the path from the beginning to the deleted tree.
	 * In case it is null, this parameter will be ignored.
	 * @return Returns whether it has been possible to remove the element from the tree (e.g. it will
	 * return false if the value does not exist)
	 */
	bool deleteNode(const T& key, std::stack<Node<T>*>* stackTree);
private:
	/**
	 * Search the node with the minimum value
	 * @param[in] rootNode Node where to start the search from
	 * @return Returns the node with the lowest value, starting from the rootNode (or
	 * nullptr in case the rootnode is nullptr)
	 */
	Node<T>* minNode(Node<T>* rootNode) const;

};

} /* namespace tree */

#endif /* SRC_TREE_BINARYSEARCHTREE_H_ */
