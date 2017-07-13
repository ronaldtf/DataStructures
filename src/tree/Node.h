/**
 * @file Node.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_NODE_H_
#define SRC_TREE_NODE_H_

#include <iostream>

/**
 * This structure represents a node in the binary tree
 */
template<typename T>
struct Node {
	// Key of the node
	T key;
	// Children
	Node* left;
	Node* right;
	// Constructor
	Node(const T key) : key(key) {
		this->left = nullptr;
		this->right = nullptr;
	}
	virtual ~Node() {
	}
	;
	/**
	 * Verifies whether the node has a value
	 * @return Returns true as the Node has only a key by default
	 */
	virtual bool hasValue() const {
		return false;
	}
	;
};

/**
 * This structure represents a node in the binary tree.
 * In this case, a key and a value is set in each node
 */
template<typename T, typename U>
struct ExtendedNode: public Node<T> {
	U value;
	ExtendedNode(T key, U value) :
			Node<T>(key), value(value) {
	}
	;
	~ExtendedNode() {
	}
	;
	/**
	 * Verifies whether the node has a value
	 * @return Returns true as the Extended node has always a key and a value
	 */
	bool hasValue() const {
		return true;
	}
	;
};

template struct Node<int> ;
template struct Node<float> ;
template struct Node<double> ;
template struct Node<std::string> ;

#endif /* SRC_TREE_NODE_H_ */
