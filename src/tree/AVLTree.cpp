/**
 * @file AVLTree.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "AVLTree.h"

namespace tree {

template<typename T>
AVLTree<T>::AVLTree() :
		BinarySearchTree<T>() {
}

template<typename T>
void AVLTree<T>::balanceTree(Node<T>** parent, std::stack<Node<T>*>& stackTree,
		T nodeKey) {
	Node<T>* x;
	Node<T>* y;
	Node<T>* z;

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
		int balance = BinarySearchTree<T>::getHeight(subtree->right)
				- BinarySearchTree<T>::getHeight(subtree->left);
		if (std::abs(balance) > 1) {
			if (balance == -1) { // => L
				z = subtree;
				y = subtree->left;
				if (nodeKey > subtree->left->key) { // => L+R
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
				if (nodeKey < subtree->right->key) { // => R+L
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
bool AVLTree<T>::insertNode(Node<T>* node) {

	// This first part consists of inserting the node into the tree, without
	// restrictions.
	std::stack<Node<T>*> stackTree;
	Node<T>* parent;
	if (!BinarySearchTree<T>::insertNode(node, &stackTree, &parent))
		return false;

	// This second part consists of balancing the tree
	balanceTree(&parent, stackTree, node->key);
	return true;

}



template<typename T>
bool AVLTree<T>::deleteNode(const T& key) {
	std::stack<Node<T>*> stackTree;
	Node<T>* parent;
	if (!BinarySearchTree<T>::deleteNode(BinarySearchTree<T>::root, &stackTree, &parent, key))
		return false;
	balanceTree(&parent, stackTree, key);
	return true;
}

template class AVLTree<int> ;
template class AVLTree<float> ;
template class AVLTree<double> ;
template class AVLTree<std::string> ;

} /* namespace tree */
