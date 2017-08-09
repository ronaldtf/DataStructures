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

	// Start in the root node
	BNode<T>* node = this->root;
	unsigned short nkeys;

	while (true) {
		if (node == nullptr)
			return nullptr;
		nkeys = node->keys.size();
		unsigned short nkey = 0;
		// Look until the key in the current node is higher or equal than the
		// existing key or the last key was reached
		while ((nkey < nkeys) && (node->keys.at(nkey) < key))
			++nkey;

		// The key was found
		if ((nkey < nkeys) && (node->keys.at(nkey) == nkeys))
			return node;

		// The key was not found:
		// 1. The key at nkey is higher than the searched key => take left child
		// 2. The key is higher than any key in the current node => take the right
		//     child (nkey is already nkeys + 1 => it points to the right child)
		node = node->children.at(nkey);
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
	for (; i < root->keys.size(); ++i) {
		getInorder(root->children.at(i), orderedList);
		orderedList.push_back(root->keys.at(i));
	}
	getInOrder(root->keys.at(i), orderedList);
}

template <typename T>
void Btree<T>::getPreorder(std::list<T>& orderedList) const {
	return getPreorder(this->root, orderedList);
}

template <typename T>
void Btree<T>::getPreorder(BNode<T>* root, std::list<T>& orderedList) const {
	if (root == nullptr)
		return;
	for (T key : root->keys)
		orderedList.push_back(key);
	for (BNode<T>* child : root->children)
		getPreorder(child, orderedList);
}

template <typename T>
void Btree<T>::getPostorder(std::list<T>& orderedList) const {
	return getPostorder(this->root, orderedList);
}

template <typename T>
void Btree<T>::getPostorder(BNode<T>* root, std::list<T>& orderedList) const {
	if (root == nullptr)
		return;
	for (BNode<T>* child : root->children)
		getPostorder(child, orderedList);
	for (T key : root->keys)
		orderedList.push_back(key);
}

template <typename T>
bool Btree<T>::isLeaf(BNode<T>* node) {
	if (node == nullptr)
		return true;
	// Theoretically, if the first child is null the rest should be
	// null as well => the check of first child should be enough
	for (BNode<T>* child : node->children) {
		if (child != nullptr)
			return false;
	}
	return true;
}

template <typename T>
bool Btree<T>::insert(T& key, T& value) {
	if (search(key))
		return false;

	return insertElement(key, value, this->root, nullptr);
}

template <typename T>
void Btree<T>::insertSortedInNode(T& element, std::vector<T>& v) {
	v.insert(std::upper_bound(v.begin(), v.end(), element), element);
}

template <typename T>
void Btree<T>::initNode(BNode<T>** node, T& key, T& value) {
	*node = new BNode<T>();
	(*node)->keys.push_back(key);
	(*node)->values.push_back(value);
	(*node)->children = std::vector<T>();
	(*node)->children.insert(2*d-1, nullptr);
}

template <typename T>
bool Btree<T>::insertElement(T& key, T& value, BNode<T>* node, BNode<T>** parent) {

	// 1. The root node is null => create the root node
	if (node ==  nullptr) {
		initNode(&node, key, value);
		return true;
	}

	// 2. The root node has enough space
	if (node->keys.size() < 2*d-1) {
		// 2.1 The node is a leaf node => add the key in a sorted way
		if (isLeaf(node)) {
			// Insert ordered in the vector
			insertInNode(key, node->keys);
			insertInNode(value, node->values);
			return true;
		}
		// 2.2 The node is not a leaf node => insert it in the right child
		else {
			size_t i = 0;
			for (; i < node->keys.size() && node->keys.at(i) < key; ++i);
			return insert(key, value, node->children.at(i), &node);
		}
	}

	// 3. There is not space in the current node

	// Insert the element in the current node (regardless it is a leaf node or not)
	insertSortedInNode(key, node->keys);
	insertSortedInNode(value, node->values);

	// Get the element in the middle (after the insertion)
	T& midKey = node->keys.at(d-1);
	T& midValue = node->keys.at(d-1);

	// Split the current node into two parts:
	// a. Create a right sub-node with the right half (without the middle element)
	// b. Remove to the current node that right half (including the middle element)
	//    This is the same as creating a node with the left part, but it is more efficient
	BNode<T>* rightSubtree = new  BNode<T>();
	rightSubtree->keys.insert(rightSubtree->keys.begin(), node->keys.begin() + d - 1, node->keys.end());
	rightSubtree->values.insert(rightSubtree->values.begin(), node->values.begin() + d - 1, node->values.end());
	rightSubtree->children.insert(rightSubtree->values.begin(), node->children.begin() + d - 1, node->children.end());
	node->keys.erase(node->keys.begin() + d);
	node->values.erase(node->values.begin() + d);
	node->children.erase(node->children.begin() + d);

	// There is no parent node => set the new mid node as parent node
	if (parent == nullptr) {
		initNode(&(this->root), key, value);
		root->childrent.at(0) = node;
		root->children.at(1) = rightSubtree;
		return true;
	}

	// There is a parent node
	// a. define child nodes for parent
	// b. insert the new mid node into parent node
	size_t i = 0;
	for (; i < node->keys.size() && node->keys.at(i) < midKey; ++i);
	(*parent)->children.emplace((*parent)->children.begin() + i, rightSubtree);  // emplace child in the right place of the parent
	return insert(midKey, midValue, parent);
}

} /* namespace tree */
