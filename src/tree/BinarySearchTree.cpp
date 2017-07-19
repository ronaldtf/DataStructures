/**
 * @file Tree.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "BinarySearchTree.h"

#include <cmath>
#include <sstream>
#include <string>

namespace tree {

template<typename T>
BinarySearchTree<T>::BinarySearchTree() :
		root(nullptr) {
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
	deleteTree(this->root);
}

template<typename T>
bool BinarySearchTree<T>::insertNode(Node<T>* node) {
	return insertNode(node, nullptr);
}

template<typename T>
bool BinarySearchTree<T>::deleteNode(const T& key) {
	return deleteNode(key, nullptr);
}

template<typename T>
bool BinarySearchTree<T>::deleteNode(Node<T>* node) {
	if (node == nullptr)
		return false;
	return deleteNode(node->key);
}

template<typename T>
Node<T>* BinarySearchTree<T>::search(const T& key) const {
	return search(BinarySearchTree<T>::root, key, nullptr);
}

template<typename T>
Node<T>* BinarySearchTree<T>::search(Node<T>* rootNode, const T& keyValue,
		Node<T>** parent) const {
	Node<T>* p = nullptr;
	Node<T>* child = rootNode;
	while (child != nullptr) {
		if (child->key == keyValue) {
			if (parent != nullptr)
				*parent = p;
			return child;
		} else {
			p = child;
			if (child->key >= keyValue) {
				child = child->left;
			} else {
				child = child->right;
			}
		}
	}
	if (parent != nullptr)
		*parent = nullptr;
	// Not found
	return nullptr;
}

template<typename T>
void BinarySearchTree<T>::getInorder(std::list<Node<T>*>& orderedList) const {
	getInorder(BinarySearchTree<T>::root, orderedList);
}

template<typename T>
void BinarySearchTree<T>::getInorder(Node<T>* root,
		std::list<Node<T>*>& orderedList) const {
	if (root == nullptr)
		return;
	if (root->left != nullptr)
		getInorder(root->left, orderedList);
	orderedList.push_back(root);
	if (root->right != nullptr)
		getInorder(root->right, orderedList);
}

template<typename T>
void BinarySearchTree<T>::getPreorder(std::list<Node<T>*>& orderedList) const {
	getPreorder(BinarySearchTree<T>::root, orderedList);
}

template<typename T>
void BinarySearchTree<T>::getPreorder(Node<T>* root,
		std::list<Node<T>*>& orderedList) const {
	if (root == nullptr)
		return;
	orderedList.push_back(root);

	if (root->left != nullptr)
		getPreorder(root->left, orderedList);
	if (root->right != nullptr)
		getPreorder(root->right, orderedList);
}

template<typename T>
void BinarySearchTree<T>::getPostorder(std::list<Node<T>*>& orderedList) const {
	getPostorder(BinarySearchTree<T>::root, orderedList);
}

template<typename T>
void BinarySearchTree<T>::getPostorder(Node<T>* root,
		std::list<Node<T>*>& orderedList) const {
	if (root == nullptr)
		return;
	if (root->left != nullptr)
		getPostorder(root->left, orderedList);
	if (root->right != nullptr)
		getPostorder(root->right, orderedList);
	orderedList.push_back(root);
}

template<typename T>
unsigned int BinarySearchTree<T>::getHeight(Node<T>* root) const {
	if (root == nullptr)
		return 0;
	return 1 + std::max(getHeight(root->right), getHeight(root->left));
}

template<typename T>
unsigned int BinarySearchTree<T>::getHeight() const {
	return getHeight(this->root);
}

template<typename T>
std::string BinarySearchTree<T>::toString() const {
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
void BinarySearchTree<T>::deleteTree(Node<T>* root) {
	if (root == nullptr)
		return;
	deleteTree(root->right);
	deleteTree(root->left);
	delete root;
}

template<typename T>
std::string BinarySearchTree<T>::t2str(T element) const {
	std::ostringstream os;
	os << element;
	return os.str();
}

template<typename T>
void BinarySearchTree<T>::getStrings(Node<T>* root, const unsigned int level,
		const unsigned int height, std::vector<std::string>& strs) const {
	// Number of nodes in level i: 2^n

	static unsigned short NODESIZE = 2;
	int spaces = std::pow(2, height - level) - 1;
	std::string leftStr = std::string((NODESIZE * spaces), ' ');
	std::string rightStr = std::string(NODESIZE * (spaces + 1), ' ');
	std::string valStr = "  ";
	if (root != nullptr) {
		valStr = t2str(root->key);
		if (valStr.size() < NODESIZE) {
			int missing = (valStr.size() - NODESIZE) / 2;
			std::string tmpLeftStr = "";
			std::string tmpRightStr = "";
			if (missing > 0) {
				std::string tmpLeftStr = std::string(NODESIZE * missing, ' ');
				std::string tmpRightStr = std::string(NODESIZE * (missing + 1),
						' ');
			}
			valStr = tmpLeftStr + valStr + tmpRightStr;
		}
	}
	strs[level] += leftStr + valStr + rightStr;
	if (level < height) {
		if (root == nullptr) {
			getStrings(root, level + 1, height, strs);
			getStrings(root, level + 1, height, strs);
		} else {
			getStrings(root->left, level + 1, height, strs);
			getStrings(root->right, level + 1, height, strs);
		}
	}

}

template<typename T>
bool BinarySearchTree<T>::insertNode(Node<T>* node,
		std::stack<Node<T>*>* stackTree) {

	// This first part consists of inserting the node into the tree, without
	// restrictions. We could have use the BinarySearchTree<T>::insert method except
	// because we need to keep the nodes we go through in order to, later,
	// go from the bottom to the top in case the tree is not balanced. Additionally,
	// we need to keep the parent node

	if (node == nullptr)
		return false;

	// The tree does not have a root element
	if (BinarySearchTree<T>::root == nullptr) {
		BinarySearchTree<T>::root = node;
		return true;
	} else {
		// Get the root
		Node<T>* child = BinarySearchTree<T>::root;

		// Go across the tree to search the corresponding gap for the element
		while (true) {
			// Insert the current node in the stack
			if (stackTree != nullptr)
				stackTree->push(child);

			// Insert to the left
			if (child->key > node->key) {
				if (child->left == nullptr) {
					child->left = node;
					break;
				}
				child = child->left;
			}
			// Insert to the right
			else if (child->key < node->key) {
				if (child->right == nullptr) {
					child->right = node;
					break;
				}
				child = child->right;
			} else { // The node already exists
				// Clean the stack tree before exiting
				while (!stackTree->empty())
					stackTree->pop();
				return false;
			}
		}
		return true;
	}
}

template<typename T>
bool BinarySearchTree<T>::deleteNode(const T& key,
		std::stack<Node<T>*>* stackTree) {

	// Search the node to be removed
	Node<T> *parent = nullptr;
	Node<T>* currNode = this->search(this->root, key, &parent);
	// Node has not found => cannot delete it
	if (currNode == nullptr)
		return false;

	// ALGORITHM:
	// Current node has only 0 or 1 child
	if ((currNode->left == nullptr) || (currNode->right == nullptr)) {
		Node<T>* childNode =
				(currNode->left != nullptr) ?
						currNode->left :
						((currNode->right != nullptr) ?
								currNode->right : nullptr);
		// 1. This is a root node => set child as root node
		if (parent == nullptr)
			this->root = childNode;
		// 2. Current node is not root => set current child as parent child
		else {
			if (currNode->key < parent->key)
				parent->left = childNode;
			else
				parent->right = childNode;
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
		deleteNode(minKey);
		// 2.4 Update current node value
		currNode->key = minKey;
	}
	return true;
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

template class BinarySearchTree<int> ;
template class BinarySearchTree<float> ;
template class BinarySearchTree<double> ;
template class BinarySearchTree<std::string> ;

} /* namespace tree */
