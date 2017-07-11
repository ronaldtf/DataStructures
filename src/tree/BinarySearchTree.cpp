/**
 * @file Tree.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "BinarySearchTree.h"

namespace tree {

template<typename T>
BinarySearchTree<T>::BinarySearchTree() : BinaryTree<T>() {
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
}

template<typename T>
void BinarySearchTree<T>::insertNode(Node<T>* node) {
	if (node == nullptr)
		return;

	// The tree does not have a root element
	if (BinaryTree<T>::root == nullptr) {
		BinaryTree<T>::root = node;
	} else {
		// Get the root
		Node<T>* child = BinaryTree<T>::root;

		// Go across the tree to search the corresponding gap for the element
		while (true) {
			// Insert to the left
			if (child->key >= node->key) {
				if (child->left == nullptr) {
					child->left = node;
					break;
				}
				child = child->left;
			}
			// Insert to the right
			else {
				if (child->right == nullptr) {
					child->right = node;
					break;
				}
				child = child->right;
			}
		}
	}
}

template<typename T>
Node<T>* BinarySearchTree<T>::minNode(Node<T>* rootNode) const {
	if (rootNode == nullptr)
		return nullptr;
	Node<T>* min = rootNode;
	while (min->left != nullptr)
		min = min->left;
	return min;
}

template<typename T>
bool BinarySearchTree<T>::deleteNode(const T& key) {
	return deleteNode(BinaryTree<T>::root, key);
}

template<typename T>
bool BinarySearchTree<T>::deleteNode(Node<T>* rootNode, const T& key) {

	if (rootNode == nullptr)
		return false;

	// Search the node to be removed
	Node<T>* parentNode = nullptr;
	Node<T>* currNode = this->search(rootNode, key, &parentNode);
	// Node has not found => cannot delete it
	if (currNode == nullptr)
		return false;

	// ALGORITHM:
	// Current node has only 0 or 1 child
	if ((currNode->left == nullptr) || (currNode->right == nullptr)) {
		Node<T>* childNode = (currNode->left != nullptr) ? currNode->left : ((currNode->right != nullptr) ? currNode->right : nullptr);
		// 1. This is a root node => set child as root node
		if (parentNode == nullptr)
			rootNode = childNode;
		// 2. Current node is not root => set current child as parent child
		else {
			if (currNode->key <= parentNode->key)
				parentNode->left = childNode;
			else
				parentNode->right = childNode;
		}
		delete currNode;
		currNode = nullptr;
	}
	// 2. The node has both right and left children => update the tree
	else {
		// 2.1 Find the minimum value in the right subtree
		Node<T>* min = minNode(currNode->right);
		// 2.2 Get minimum value
		T minKey = min->key;
		// 2.3 Remove node with such value
		deleteNode(currNode, minKey);
		// 2.4 Update current node value
		currNode->key = minKey;
	}
	return true;
}

template class BinarySearchTree<int>;
template class BinarySearchTree<float>;
template class BinarySearchTree<double>;
template class BinarySearchTree<std::string>;

} /* namespace tree */
