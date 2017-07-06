/**
 * @file Tree.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_BINARYSEARCHTREE_H_
#define SRC_TREE_BINARYSEARCHTREE_H_

#include <list>
#include <string>
#include <vector>

namespace tree {

/**
 * This structure represents a node in the binary tree
 */
template<typename T>
struct Node {
	// Value of the node
	T value;
	// Children
	Node* left;
	Node* right;
	// Constructor
	Node(T value) {
		this->value = value;
		this->left = nullptr;
		this->right = nullptr;
	}
};

/**
 * This class implements the needed methods in a binary tree
 */
template<typename T>
class BinarySearchTree {
private:
	/**
	 * Root node in the binary tree
	 */
	Node<T>* root;
	/**
	 * Get the list of elements for every level in a formatted string, using enough spaces between them
	 * in order to draw the tree correctly
	 * @param[in] root Root node
	 * @param[in] level Current level
	 * @param[in] height Tree height
	 * @param[out] strs List of strings, each per tree level
	 */
	void getStrings(Node<T>* root, const unsigned int level, const unsigned int height, std::vector<std::string>& strs);
	/**
	 * Removes the entire tree
	 */
	void deleteTree(Node<T>* root);
	/**
	 * Go along the tree in an in-order order.
	 * @param[in] root Root node
	 * @param[out] orderedList List in an in-order order
	 */
	void getInorder(Node<T>* root, std::list<T>& orderedList);
	/**
	 * Go along the tree in n pre-order order.
	 * @param[in] root Root node
	 * @param[out] orderedList List in a pre-order order
	 */
	void getPreorder(Node<T>* root, std::list<T>& orderedList);
	/**
	 * Go along the tree in a post-order order.
	 * @param[in] root Root node
	 * @param[out] orderedList List in a post-order order
	 */
	void getPostorder(Node<T>* root, std::list<T>& orderedList);
	/**
	 * Removes a node in the tree with a given value
	 * @param[in] root Root node
	 * @param[in] value Value to remove in the node
	 * @return Returns whether it has been possible to remove the element from the tree (e.g. it will
	 * return false if the value does not exist)
	 */
	bool deleteNode(Node<T>* rootNode, const T& value);
	/**
	 * Search an element in the tree
	 * @param[in] rootNode Node where to start the search from
	 * @param[in] element Value to search in the tree
	 * @param[out] parent Parent node for the searched node (nullptr in case the value was
	 * not found or the value is in the root node)
	 * @return Returns the node with the given value, or nullptr in case it was not found
	 */
	Node<T>* search(Node<T>* rootNode, const T& element, Node<T>** parent) const;
	/**
	 * Search the node with the minimum value
	 * @param[in] rootNode Node where to start the search from
	 * @return Returns the node with the lowest value, starting from the rootNode (or
	 * nullptr in case the rootnode is nullptr)
	 */
	Node<T>* minNode(Node<T>* rootNode) const;
	/**
	 * Converts a type to a string
	 * @param[in] element Element to convert to a string
	 * @return Returns the stringified element
	 */
	std::string t2str(T element);
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
	 * @param[in] value Value to insert in the tree
	 */
	void insertNode(const T& value);
	/**
	 * Removes a node with a given value
	 * @param[in] value Value to remove from the tree
	 */
	bool deleteNode(const T& value);
	/**
	 * Look for a node with a value
	 * @param[in] element Value to search in the tree
	 * @return Returns the node with the given value, or nullptr in case it was not found
	 */
	Node<T>* search(const T& element) const;
	/**
	 * Go along the tree in an in-order order.
	 * @param[out] orderedList List in n pre-order order
	 */
	void getInorder(std::list<T>& orderedList);
	/**
	 * Go along the tree in a pre-order order.
	 * @param[out] orderedList List in n pre-order order
	 */
	void getPreorder(std::list<T>& orderedList);
	/**
	 * Go along the tree in a post-order order.
	 * @param[out] orderedList List in n pre-order order
	 */
	void getPostorder(std::list<T>& orderedList);
	/**
	 * Get the height of the tree
	 * @param[in] root Node where to start calculating the height from
	 * @return Tree height
	 */
	unsigned int getHeight(Node<T>* root);
	/**
	 * Converts the tree into a printable format
	 * @return Returns the string with the tree structure
	 */
	std::string toString();
};


} /* namespace tree */

#endif /* SRC_TREE_BINARYSEARCHTREE_H_ */
