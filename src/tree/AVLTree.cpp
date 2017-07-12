/**
 * @file AVLTree.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "AVLTree.h"

namespace tree {

template<typename T>
AVLTree<T>::AVLTree() : BinaryTree<T>() {
}

template<typename T>
void AVLTree<T>::balanceTree(Node<T>** parent, std::stack<Node<T>*>& stackTree, Node<T>* node) {
	Node<T>* x, y, z;

//		LL CASE
//		___________________________________________________________
//		T1, T2, T3 and T4 are subtrees.
//		         z                                      y
//		        / \                                   /   \
//		       y   T4      Right Rotate (z)          x      z
//		      / \          - - - - - - - - ->      /  \    /  \
//		     x   T3                               T1  T2  T3  T4
//		    / \
//		  T1   T2

//		LR CASE
//		___________________________________________________________
//	     z                               z                           x
//	    / \                            /   \                        /  \
//	   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
//	  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
//	T1   x                          y    T3                    T1  T2 T3  T4
//	    / \                        / \
//	  T2   T3                    T1   T2

//		RR CASE
//		___________________________________________________________
//		  z                                y
//		 /  \                            /   \
//		T1   y     Left Rotate(z)       z      x
//		    /  \   - - - - - - - ->    / \    / \
//		   T2   x                     T1  T2 T3  T4
//		       / \
//		     T3  T4

//		RL CASE
//		___________________________________________________________
//		   z                            z                            x
//		  / \                          / \                          /  \
//		T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
//		    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
//		   x   T4                      T2   y                  T1  T2  T3  T4
//		  / \                              /  \
//		T2   T3                           T3   T4

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
				(*parent)->left = x;
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
				(*parent)->right = y;
			}
			break;
		}
	}
	// Empty the stack tree
	while (!stackTree.empty())
		stackTree.pop();

}

template<typename T>
bool AVLTree<T>::insertNode(const Node<T>* node) {

	// This first part consists of inserting the node into the tree, without
	// restrictions. We could have use the BinaryTree<T>::insert method except
	// because we need to keep the nodes we go through in order to, later,
	// go from the bottom to the top in case the tree is not balanced. Additionally,
	// we need to keep the parent node

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

		// This second part consists of balancing the tree
		balanceTree(&parent, stackTree, node);
		return true;
	}


}

template<typename T>
bool AVLTree<T>::deleteNode(const T& key) {
	return false;
}

} /* namespace tree */
