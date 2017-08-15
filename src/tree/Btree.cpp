/**
 * @file Btree.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "Btree.h"

#include <algorithm>

namespace tree {

template <typename T>
Btree<T>::Btree(unsigned short d) : d(d), root(nullptr) {

}

template <typename T>
Btree<T>::~Btree() {
}

template <typename T>
BNode<T>* Btree<T>::search(const T& key) {
	BNode<T>* parent = nullptr;
	return search(key, &parent);
}

template <typename T>
BNode<T>* Btree<T>::search(const T& key, BNode<T>** parent) {

	// Start in the root node
	BNode<T>* node = this->root;
	unsigned short nkeys;

	while (true) {
		if (node == nullptr) {
			parent = nullptr;
			return nullptr;
		}
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
		*parent = node;
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

template <typename T>
void Btree<T>::rotateAndKeepSibling(BNode<T>** sibling, BNode<T>** parent, BNode<T>** target, size_t parentI, size_t posSibling) {
	// Replace parent key/value with right/left key/value of sibling...
	T& parentKey = (*parent)->keys.at(parentI);
	T& parentValue = (*parent)->values.at(parentI);
	std::replace((*parent)->keys.begin()+parentI, (*parent)->keys.begin()+parentI+1, parentKey, (*sibling)->keys.at(posSibling));
	std::replace((*parent)->values.begin()+parentI, (*parent)->values.begin()+parentI+1, parentValue, (*sibling)->values.at(posSibling));

	// ... and append original parent (to keep it in a sorted way, we have to check whether we have to set
	//     it at the beginning or at the end of the vector)
	size_t tmpPos = (posSibling == 0) ? (*target)->keys.size() : 0;
	(*target)->keys.insert((*target)->keys.begin()+tmpPos, (*target)->keys.begin()+tmpPos+1, parentKey);
	(*target)->value.insert((*target)->values.begin()+tmpPos, (*target)->values.begin()+tmpPos+1, parentValue);
}

template <typename T>
bool Btree<T>::remove(T& key) {
	BNode<T>* parent = nullptr;
	BNode<T>* node = search(key, &parent);
	if (node == nullptr)
		return false;
	return remove(key, &node, &parent);
}

template <typename T>
void Btree<T>::mergeAndRemove(BNode<T>** sibling, BNode<T>** target, BNode<T>** parent, size_t parentI) {
	// Insert parent as an element of current node
	(*target)->keys.insert((*target)->keys.end(), (*parent)->keys.at(parentI));
	(*target)->values.insert((*target)->values.end(), (*parent)->values.at(parentI));
	// Insert sibling keys/values into current node
	(*target)->keys.insert((*target)->keys.end(), (*sibling)->keys.begin(), sibling->keys.end());
	(*target)->values.insert((*target)->values.end(), (*sibling)->values.begin(), (*sibling)->values.end());
	// Clear sibling keys/values
	(*sibling)->keys.clear();
	(*sibling)->values.clear();
	// Remove parent node
	(*parent)->keys.erase((*parent)->keys.begin() + parentI, (*parent)->keys.begin() + parentI + 1);
	(*parent)->values.erase((*parent)->values.begin() + parentI, (*parent)->values.begin() + parentI + 1);
	// Remove child for removed parent node
	(*parent)->children.erase((*parent)->children.begin() + parentI, (*parent)->children.end() + parentI + 1);
}

template <typename T>
bool Btree<T>::remove(T& key, BNode<T>**node, BNode<T>**parent) {

	// Look for key position of the parent node
	size_t parentI = -1;
	if (*parent != nullptr)
		for (parentI=0; parentI < (*parent)->keys.size() - 1 && (*parent)->keys.at(parentI) < key; ++parentI);

	// Get position of the key within the node
	size_t posKey = 0;
	for (; posKey < (*node)->keys.size() && (*node)->keys.at(posKey) != key; ++posKey);

	// 1. The node is a leaf:
	if (isLeaf(*node)) {
		// 1.1 Number of keys in node >= d or it is the root node
		if (((*node)->keys.size() >= d) || ((*parent) == nullptr)) {
			// Simply remove the key from the node (it is a leaf node, therefore, there
			// is no problem with children)
			(*node)->keys.erase((*node)->keys.begin()+posKey, (*node)->keys.begin()+posKey+1);
			(*node)->keys.erase((*node)->values.begin()+posKey, (*node)->values.begin()+posKey+1);
			return true;
		}

		// 1.2 Number of keys in node == d-1
		else {
			// Find sibling nodes
			BNode<T>* left = (*parent)->children(parentI);
			BNode<T>* right = (*parent)->children.at(parentI+1);

			T& nodeKey = (*node)->keys.at(posKey); // == key
			T& nodeValue = (*node)->values.at(posKey);
			// Remove current key/value...
			(*node)->keys.erase((*node)->keys.begin()+posKey, (*node)->keys.begin()+posKey+1);
			(*node)->values.erase((*node)->values.begin()+posKey, (*node)->values.begin()+posKey+1);

			//    1.2.1 Sibling nodes with >= d
			if ((left->keys.size() >= d) || (right->keys.size() >= d)) {
				size_t posSibling = (left->keys.size() >= d) ? left->keys.size() - 1 : 0;
				BNode<T>* sibling = (left->keys.size() >= d) ? left : right;

				// Copy parent key/value to the node and sibling key/value to the parent
				rotate(&sibling, parent, node, parentI, posSibling);
				// ... remove sibling key/value
				sibling->keys.erase(sibling->keys.begin()+posSibling, sibling->keys.begin()+posSibling+1);
				sibling->values.erase(sibling->values.begin()+posSibling, sibling->values.begin()+posSibling+1);

				return true;
			}
			//    1.2.2 Sibling nodes with <= d-1
			else {
				// Merge node with sibling:

				// Verify whether current node is the top right child of the parent and get the sibling accordingly
				bool isLastChild = ((*parent)->keys.at(parent) < key);
				BNode<T>* sibling = isLastChild ?  (*parent)->children.at(parentI) : (*parent)->children.at(parentI+1);
				if (isLastChild)
					std::swap(node, sibling);
				mergeAndRemove(&sibling, node, parent, parentI);

				return true;
			}
		}
	}


	// 2. The node is an internal node
	//    2.1 Number of keys in left child node >= d
	BNode<T>* left = (*node)->children(posKey);
	BNode<T>* right = (*node)->children.at(posKey+1);
	if (left->keys.size() >= d) {
		T lkey = left->keys.at(left->keys.size()-1);
		rotateAndKeepSibling(&left, node, &right, posKey, left->keys.size() -1);
		return remove(lkey, &left, node);
	}
	//    2.2 Number of keys in right child node >= d
	else if (right->keys.size() >= d) {
		T rkey = left->keys.at(0);
		rotateAndKeepSibling(&right, node, &left, posKey, 0);
		return remove(rkey, &right, node);
	}
	//    2.3 Number of keys in left and right children == d-1
	else {
		if ((*node)->keys.size() == d-1) {
			BNode<T>* tmp = right;
			BNode<T>* tmpParent = node;
			// Look for the minimum value on the right
			while (!isLeaf(tmp)) {
				tmpParent = tmp;
				tmp = tmp->children.at(0);
			}
			(*node)->keys.at(posKey) = tmp->keys.at(0);
			(*node)->values.at(posKey) = tmp->values.at(0);

			return remove(tmp->keys.at(0), tmp, tmpParent);
		} else {
			mergeAndRemove(left, right, node, posKey);
			return true;
		}
	}

}

} /* namespace tree */
