/**
 * @file AVLTree.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include <stack>

#include "AVLTree.h"

namespace tree {

template<typename T>
AVLTree<T>::AVLTree() : BinaryTree<T>() {
}

template<typename T>
bool AVLTree<T>::insertNode(const Node<T>* node) {
	if (node == nullptr)
		return false;

	std::stack<Node<T>* > stackTree = std::stack<Node<T>* >();
	// The tree does not have a root element
	if (BinaryTree<T>::root == nullptr) {
		BinaryTree<T>::root = node;
		return true;
	} else {
		// Get the root
		Node<T>* child = BinaryTree<T>::root;
		Node<T>* parent = nullptr;

		// Go across the tree to search the corresponding gap for the element
		while (true) {
			parent = child;
			// Insert to the left
			if (child->key > node->key) {
				if (child->left == nullptr) {
					child->left = node;
					break;
				}
				stackTree.push(child);
				child = child->left;
			}
			// Insert to the right
			else if (child->key < node->key) {
				if (child->right == nullptr) {
					child->right = node;
					break;
				}
				stackTree.push(child);
				child = child->right;
			} else
				return false;
		}

		Node<T>* x, y, z;

		// If the stackTree is empty, the root node has 1 or 2 children.
		// Otherwise, we have to check whether it is balanced or not
		// To get the first unbalanced subtree, we go from the bottom to the top
		// The first time we find the unbalanced tree, we balance it by using
		// the RR, RL, LL or LR movement
		while (!stackTree.empty()) {
			Node<T>* subtree = stackTree.top();
			stackTree.pop();
			int balance = BinaryTree<T>::getHeight(subtree->right)-BinaryTree<T>::getHeight(subtree->left);
			if (std::abs(balance) > 1) {
				if (balance == -1) { // => L
					z = subtree;
					y = subtree->left;
					if (node->key > subtree->left->key) { // => L+R
						x = subtree->left->right;
						// Turn left the small subtree and then right the big subtree
						y->right = x->left;
						z->left = x->right;
						x->left = y;
						x->right = z;
					} else { // L+L
						x = subtree->left->left;
						// Turn left the subtree once
						z->left = y->right;
						y->right = z;
					}
					parent->left = x;
				} else { // balance == +1 => R
					z = subtree;
					y = subtree->right;
					if (node->key < subtree->right->key) { // => R+L
						x = subtree->right->left;
						// Turn right the small subtree and then left the big subtree
						y->left = x->right;
						z->right = x->left;
						x->left = z;
						x->right = y;
					} else { // => R + R
						x = subtree->right->right;
						// Turn right the subtree once
						z->right = y->left;
						y->left = z;
					}
					parent->right = y;
				}
				break;
			}
		}
		return true;

	}


}

template<typename T>
bool AVLTree<T>::deleteNode(const T& key) {
	return false;
}

} /* namespace tree */
