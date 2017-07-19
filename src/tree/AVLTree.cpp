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
bool AVLTree<T>::insertNode(Node<T>* node) {

	// This first part consists of inserting the node into the tree, without
	// restrictions.
	std::stack<Node<T>*> stackTree = std::stack<Node<T>*>();
	if (!BinarySearchTree<T>::insertNode(node, &stackTree))
		return false;

	// This second part consists of balancing the tree
	balanceTree(stackTree, node->key);
	return true;
}

template<typename T>
bool AVLTree<T>::deleteNode(const T& key) {
	std::stack<Node<T>*> stackTree;
	if (!BinarySearchTree<T>::deleteNode(key, &stackTree))
		return false;
	balanceTree(stackTree, key);
	return true;
}

template<typename T>
void AVLTree<T>::pointParentToChild(Node<T>** root, Node<T>** parent,
		Node<T>** child) {
	if (*parent != nullptr) {
		if ((*parent)->key < (*child)->key)
			(*parent)->right = *child;
		else
			(*parent)->left = *child;
	} else
		*root = *child;

}

template<typename T>
void AVLTree<T>::balanceTree(std::stack<Node<T>*>& stackTree, T nodeKey) {
	Node<T>* x;
	Node<T>* y;
	Node<T>* z;

	if (stackTree.size() < 2) {
		return;
	}
	// The element inserted is not in the stack tree
	// The parent of the element inserted can be removed from the stack
	// because we can only have an unbalanced tree after when height >= 2
	stackTree.pop();

	Node<T>* parent = nullptr;

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
	//
	//		LR CASE
	//		___________________________________________________________
	//	     z                               z                           x
	//	    / \                            /   \                        /  \
	//	   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
	//	  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
	//	T1   x                          y    T3                    T1  T2 T3  T4
	//	    / \                        / \
	//	  T2   T3                    T1   T2
	//
	//		RR CASE
	//		___________________________________________________________
	//		  z                                y
	//		 /  \                            /   \
	//		T1   y     Left Rotate(z)       z      x
	//		    /  \   - - - - - - - ->    / \    / \
	//		   T2   x                     T1  T2 T3  T4
	//		       / \
	//		     T3  T4
	//
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
		std::cout << "stack size: " << stackTree.size() << std::endl;
		int balance = BinarySearchTree<T>::getHeight(subtree->right)
				- BinarySearchTree<T>::getHeight(subtree->left);
		if (std::abs(balance) > 1) {
			z = subtree;
			BinarySearchTree<T>::search(BinarySearchTree<T>::root, z->key,
					&parent);
			if (balance == -1) { // => L
				y = subtree->left;
				if (nodeKey > subtree->left->key) { // => L+R
					x = subtree->left->right;
					// Turn left the small subtree and then right the big subtree
					y->right = x->left;
					z->left = x->right;
					x->left = y;
					x->right = z;
					pointParentToChild(&(BinarySearchTree<T>::root), &parent,
							&x);
				} else { // L+L
					x = subtree->left->left;
					// Turn left the subtree once
					z->left = y->right;
					y->right = z;
					pointParentToChild(&(BinarySearchTree<T>::root), &parent,
							&y);
				}
			} else { // balance == +1 => R
				y = subtree->right;
				if (nodeKey < subtree->right->key) { // => R+L
					x = subtree->right->left;
					// Turn right the small subtree and then left the big subtree
					z->right = x->left;
					y->left = x->right;
					x->left = z;
					x->right = y;
					pointParentToChild(&(BinarySearchTree<T>::root), &parent,
							&x);
				} else { // => R + R
					x = subtree->right->right;
					// Turn right the subtree once
					z->right = y->left;
					y->left = z;
					pointParentToChild(&(BinarySearchTree<T>::root), &parent,
							&y);
				}
			}

			break;
		}
	}
	// Empty the stack tree
	while (!stackTree.empty())
		stackTree.pop();
}

template class AVLTree<int> ;
template class AVLTree<float> ;
template class AVLTree<double> ;
template class AVLTree<std::string> ;

} /* namespace tree */
