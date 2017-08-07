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

	while (true) {
		unsigned short nkey = 0;
		// Look until the key in the current node is higher or equal than the
		// existing key or the last key was reached
		while ((nkey < nkeys) && (node->keys[nkey] < key))
			++nkey;

		// The key was found
		if ((nkey < nkeys) && (node->keys[nkey] == nkeys))
			return node;
		// The key was not found:
		// 1. The key at nkey is higher than the searched key => take left child
		// 2. The key is higher than any key in the current node => take the right
		//     child (nkey is already nkeys + 1 => it points to the right child)
		node = node->children[nkey];
		if (node == nullptr)
			return nullptr;
		nkeys = node->nkeys;
	}
}

template <typename T>
void Btree<T>::getInorder(std::list<T>& orderedList) const {
	return getInorder(this->root, orderedList);
}

template <typename T>
void Btree<T>::getInorder(BNode<T>* root, std::list<T>& orderedList) const {
	if (root == nullptr)
		return;
	unsigned int i = 0;
	for (; i < root->nkeys; ++i) {
		getInorder(root->children[i], orderedList);
		orderedList.push_back(root->keys[i]);
	}
	getInOrder(root->keys[i], orderedList);
}

template <typename T>
void Btree<T>::getPreorder(std::list<T>& orderedList) const {
	return getPreorder(this->root, orderedList);
}

template <typename T>
void Btree<T>::getPreorder(BNode<T>* root, std::list<T>& orderedList) const {
	if (root == nullptr)
		return;
	unsigned int i = 0;
	for (; i < root->nkeys; ++i) {
		orderedList.push_back(root->keys[i]);
	}
	for (i=0; i <= root->nkeys; ++i)
		getPreorder(root->children[i], orderedList);
}

template <typename T>
void Btree<T>::getPostorder(std::list<T>& orderedList) const {
	return getPostorder(this->root, orderedList);
}

template <typename T>
void Btree<T>::getPostorder(BNode<T>* root, std::list<T>& orderedList) const {
	if (root == nullptr)
		return;
	unsigned int i = 0;
	for (; i <= root->nkeys; ++i)
		getPreorder(root->children[i], orderedList);
	for (i=0; i < root->nkeys; ++i) {
		orderedList.push_back(root->keys[i]);
	}
}

template <typename T>
bool Btree<T>::insert(T& element) {
	return false;
}
} /* namespace tree */
