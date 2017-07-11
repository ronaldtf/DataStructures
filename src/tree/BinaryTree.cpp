/**
 * @file BinaryTree.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "BinaryTree.h"

namespace tree {

template<typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {

};

template<typename T>
BinaryTree<T>::~BinaryTree() {
	deleteTree(this->root);
};

template<typename T>
Node<T>* BinaryTree<T>::search(const T& element) const {
	Node<T>* parent = nullptr; // This is not used here
	return search(BinaryTree<T>::root, element, &parent);
}

template<typename T>
Node<T>* BinaryTree<T>::search(Node<T>* rootNode, const T& element, Node<T>** parent) const {
	Node<T>* child = rootNode;
	while (child != nullptr) {
		if (child->value == element) {
			return child;
		} else {
			*parent = child;
			if (child->value >= element) {
				child = child->left;
			} else {
				child = child->right;
			}
		}
	}
	// Not found
	return nullptr;
}

template<typename T>
void BinaryTree<T>::getInorder(std::list<T>& orderedList) const {
	getInorder(BinaryTree<T>::root, orderedList);
}

template<typename T>
void BinaryTree<T>::getInorder(Node<T>* root, std::list<T>& orderedList) const {
	if (root == nullptr)
		return;
	if (root->left != nullptr)
		getInorder(root->left, orderedList);
	orderedList.push_back(root->value);
	if (root->right != nullptr)
		getInorder(root->right, orderedList);
}

template<typename T>
void BinaryTree<T>::getPreorder(std::list<T>& orderedList) const {
	getPreorder(BinaryTree<T>::root, orderedList);
}

template<typename T>
void BinaryTree<T>::getPreorder(Node<T>* root, std::list<T>& orderedList) const {
	if (root == nullptr)
		return;
	orderedList.push_back(root->value);

	if (root->left != nullptr)
		getPreorder(root->left, orderedList);
	if (root->right != nullptr)
		getPreorder(root->right, orderedList);
}

template<typename T>
void BinaryTree<T>::getPostorder(std::list<T>& orderedList) const {
	getPostorder(BinaryTree<T>::root, orderedList);
}

template<typename T>
void BinaryTree<T>::getPostorder(Node<T>* root, std::list<T>& orderedList) const {
	if (root == nullptr)
		return;
	if (root->left != nullptr)
		getPostorder(root->left, orderedList);
	if (root->right != nullptr)
		getPostorder(root->right, orderedList);
	orderedList.push_back(root->value);
}

template<typename T>
unsigned int BinaryTree<T>::getHeight(Node<T>* root) const {
	if (root == nullptr)
		return 0;
	return 1 + std::max(getHeight(root->right), getHeight(root->left));
}

template<typename T>
unsigned int BinaryTree<T>::getHeight() const {
	return getHeight(this->root);
}

template<typename T>
std::string BinaryTree<T>::toString() const {
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
void BinaryTree<T>::deleteTree(Node<T>* root) {
	if (root == nullptr)
		return;
	deleteTree(root->right);
	deleteTree(root->left);
	delete root;
}

template<typename T>
std::string BinaryTree<T>::t2str(T element) const {
	std::ostringstream os;
	os << element;
	return os.str();
}

template<typename T>
void BinaryTree<T>::getStrings(Node<T>* root, const unsigned int level, const unsigned int height, std::vector<std::string>& strs) const {
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
				std::string tmpLeftStr = std::string(NODESIZE*missing, ' ');
				std::string tmpRightStr = std::string(NODESIZE*(missing+1), ' ');
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

template class BinaryTree<int>;
template class BinaryTree<float>;
template class BinaryTree<double>;
template class BinaryTree<std::string>;

} // end namespace tree


