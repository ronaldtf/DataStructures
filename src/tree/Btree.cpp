/**
 * @file Btree.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "Btree.h"

namespace tree {

template <typename T>
Btree<T>::Btree(unsigned short d) : d(d), root(nullptr) {

}

template <typename T>
Btree<T>::~Btree() {
}

template <typename T>
BNode<T>* Btree<T>::search(const T& key) {
	if (this->root == nullptr)
		return nullptr;

	// Start in the root node
	BNode<T>* node = this->root;
	unsigned short nkeys = this->root->nkeys;
	unsigned short nkey = 0;

	while (true) {
		// Look until the key in the current node is higher or equal than the
		// existing key or the last key was reached
		while ((nkey < nkeys) || (node->keys[nkey] < key))
			++nkey;

		// The key was found
		if (node->keys[nkey] == nkeys)
			return node;
		// The key was not found:
		// 1. The key at nkey is higher than the searched key => take left child
		// 2. The key is higher than any key in the current node => take the right
		//     child (nkey is already nkeys + 1 => it points to the right child)
		node = node->keys[nkey];
		if (node == nullptr)
			return nullptr;
		nkeys = node->keys[nkey]->nkeys;
	}
}

} /* namespace tree */
