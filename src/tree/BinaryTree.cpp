/**
 * @file Tree.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "BinaryTree.h"
#include <algorithm>
#include <cmath>
#include <stack>

namespace tree {

template<typename T>
Node<T>::Node() {
	this->data = nullptr;
}

template<typename T>
Node<T>::Node(T& data) {
	this->data = new T();
	*(this->data) = data;
};

template<typename T>
BinaryTree<T>::BinaryTree() {
	this->root = nullptr;
	this->left = nullptr;
	this->right = nullptr;
}

template<typename T>
void BinaryTree<T>::copyTree(BinaryTree& currentTree, const BinaryTree& anotherTree) {
	if (anotherTree.root == nullptr)
		currentTree.root = nullptr;
	else {
		currentTree.root = new Node<T>(*anotherTree.root);
		copyTree(currentTree.left, anotherTree.left);
		copyTree(currentTree.right, anotherTree.right);
	}
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& anotherTree) {
	copyTree(this, anotherTree);
}

template<typename T>
unsigned int BinaryTree<T>::getHeight() {
	// In order to avoid this, we could have an attribute that
	// keeps the height of the tree and modifies the value
	// when addding/removing nodes to/from the tree
	if (this->left != nullptr || this->right != nullptr) {
		int leftHeight = (this->left != nullptr) ? this->left->getHeight() : 0;
		unsigned int rightHeight = (this->right != nullptr) ? this->right->getHeight() : 0;
		return 1 + std::max<unsigned int>(leftHeight, rightHeight);
	}
	return 0;
}

template<typename T>
std::string BinaryTree<T>::toString() {
	return "";
}

} /* namespace tree */
