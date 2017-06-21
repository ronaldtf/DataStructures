/**
 * @file Tree.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include <cmath>
#include <iostream>
#include <sstream>

#include "BinaryTree.h"

namespace tree {

template<typename T>
BinaryTree<T>::BinaryTree() {
	this->root = nullptr;
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
	deleteTree(this->root);
}

template<typename T>
void BinaryTree<T>::insert(const T& value) {
	// The tree does not have a root element
	if (this->root == nullptr) {
		this->root = new Node<T>(value);
	} else {
		// Get the root
		Node<T>* child = this->root;

		// Go across the tree to search the corresponding gap for the element
		while (true) {
			// Insert to the left
			if (child->value >= value) {
				if (child->left == nullptr) {
					child->left = new Node<T>(value);
					break;
				}
				child = child->left;
			}
			// Insert to the right
			else {
				if (child->right == nullptr) {
					child->right = new Node<T>(value);
					break;
				}
				child = child->right;
			}
		}
	}
}

template<typename T>
Node<T>* BinaryTree<T>::minNode(Node<T>* rootNode) {
	Node<T>* min = rootNode;
	Node<T>* child = rootNode;
	while (child != nullptr) {
		min = child;
		child = child->left;
	}
	return min;
}

template<typename T>
bool BinaryTree<T>::deleteNode(const T& value) {
	return deleteNode(this->root, value);
}

template<typename T>
bool BinaryTree<T>::deleteNode(Node<T>* rootNode, const T& value) {

	// Search the node to be removed
	Node<T>* parentNode = nullptr;
	Node<T>* currNode = search(rootNode, value, parentNode);

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
			if (currNode->value <= parentNode->value)
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
		// 2.2 Replace value of node to be removed with found minimum
		currNode->value = min->value;
		// 2.3 Apply remove to the right subtree to remove duplicate
		delete min;
		min = nullptr;
		std::cout << "here min "<< currNode->value << std::endl;
	}
	return true;
}

template<typename T>
Node<T>* BinaryTree<T>::search(const T& element) const {
	Node<T>* parent = nullptr; // This is not used here
	return search(this->root, element, parent);
}

template<typename T>
Node<T>* BinaryTree<T>::search(Node<T>* rootNode, const T& element, Node<T>* parent) const {
	Node<T>* child = rootNode;
	parent = nullptr;
	while (child != nullptr) {
		parent = child;
		if (child->value == element) {
			return child;
		}else if (child->value >= element) {
			child = child->left;
		} else {
			child = child->right;
		}
	}
	// Not found
	return nullptr;
}

template<typename T>
void BinaryTree<T>::getInorder(std::list<T>& orderedList) {
	getInorder(this->root, orderedList);
}

template<typename T>
void BinaryTree<T>::getInorder(Node<T>* root, std::list<T>& orderedList) {
	if (root == nullptr)
		return;
	if (root->left != nullptr)
		getInorder(root->left, orderedList);
	orderedList.push_back(root->value);
	if (root->right != nullptr)
		getInorder(root->right, orderedList);
}

template<typename T>
void BinaryTree<T>::getPreorder(std::list<T>& orderedList) {
	getPreorder(this->root, orderedList);
}

template<typename T>
void BinaryTree<T>::getPreorder(Node<T>* root, std::list<T>& orderedList) {
	if (root == nullptr)
		return;
	orderedList.push_back(root->value);

	if (root->left != nullptr)
		getPreorder(root->left, orderedList);
	if (root->right != nullptr)
		getPreorder(root->right, orderedList);
}

template<typename T>
void BinaryTree<T>::getPostorder(std::list<T>& orderedList) {
	getPostorder(this->root, orderedList);
}

template<typename T>
void BinaryTree<T>::getPostorder(Node<T>* root, std::list<T>& orderedList) {
	if (root == nullptr)
		return;
	if (root->left != nullptr)
		getPostorder(root->left, orderedList);
	if (root->right != nullptr)
		getPostorder(root->right, orderedList);
	orderedList.push_back(root->value);
}

template<typename T>
void BinaryTree<T>::deleteTree(Node<T>* root) {
	if (root == nullptr)
		return;
	deleteTree(root->right);
	deleteTree(root->left);
	delete root;
}

template<typename T>
unsigned int BinaryTree<T>::getHeight(Node<T>* root) {
	if (root == nullptr)
		return 0;
	return 1 + std::max(getHeight(root->right), getHeight(root->left));
}

template<typename T>
void BinaryTree<T>::getStrings(Node<T>* root, const unsigned int level, const unsigned int height, std::vector<std::string>& strs) {
	// Number of nodes in level i: 2^n

	static unsigned short NODESIZE = 2;
	int spaces = std::pow(2, height-level) - 1;
	std::string leftStr = std::string((NODESIZE*spaces), ' ');
	std::string rightStr = std::string(NODESIZE*(spaces + 1), ' ');
	std::string valStr = "  ";
	if (root != nullptr) {
		valStr = t2str(root->value);
		if (valStr.size() < NODESIZE) {
			int missing = (valStr.size() - NODESIZE)/2;
			std::string tmpLeftStr = "";
			std::string tmpRightStr = "";
			if (missing > 0) {
				std::string tmpLeftStr = std::string(missing, ' ');
				std::string tmpRightStr = std::string(missing+1, ' ');
			}
			valStr = tmpLeftStr + valStr + tmpRightStr;
		}
	}
	strs[level] += leftStr + valStr + rightStr;
	if (level < height) {
		if (root == nullptr) {
			getStrings(root, level+1, height, strs);
			getStrings(root, level+1, height, strs);
		} else {
			getStrings(root->left, level+1, height, strs);
			getStrings(root->right, level+1, height, strs);
		}
	}

}

template<typename T>
std::string BinaryTree<T>::toString() {
	std::string output = "";
	unsigned int height = getHeight(this->root);
	std::vector<std::string> outStrs = std::vector<std::string>(height + 1, "");
	getStrings(this->root, 0, height, outStrs);
	for (std::string s : outStrs) {
		output += s + "\n";
	}
	return output;
}

template<typename T>
std::string BinaryTree<T>::t2str(T element) {
	std::ostringstream os;
	os << element;
	return os.str();
}

template struct Node<int>;
template struct Node<float>;
template struct Node<double>;
template struct Node<std::string>;
template class BinaryTree<int>;
template class BinaryTree<float>;
template class BinaryTree<double>;
template class BinaryTree<std::string>;

} /* namespace tree */
