/**
 * @file BinaryTree.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_BINARYTREE_H_
#define SRC_TREE_BINARYTREE_H_

#include <cmath>
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

namespace tree {

/**
 * This structure represents a node in the binary tree
 */
template<typename T>
struct Node {
	// Value of the node
	T value;
	// Children
	Node* left;
	Node* right;
	// Constructor
	Node(T value) {
		this->value = value;
		this->left = nullptr;
		this->right = nullptr;
	}
};

/**
 * This class defines the method for a binary tree
 */
template<typename T>
class BinaryTree {
protected:
	/**
	 * Root node in the binary tree
	 */
	Node<T>* root;
	BinaryTree() : root(nullptr) {};
	~BinaryTree() {
		deleteTree(this->root);
	};
public:
	/**
	 * Insert a new node with a given value in the tree
	 * @param[in] value Value to insert in the tree
	 */
	virtual void insertNode(const T& value) = 0;
	/**
	 * Removes a node with a given value
	 * @param[in] value Value to remove from the tree
	 */
	virtual bool deleteNode(const T& value) = 0;
	/**
	 * Look for a node with a value
	 * @param[in] element Value to search in the tree
	 * @return Returns the node with the given value, or nullptr in case it was not found
	 */
	virtual Node<T>* search(const T& element) const = 0;
	/**
	 * Go along the tree in an in-order order.
	 * @param[out] orderedList List in n pre-order order
	 */
	virtual void getInorder(std::list<T>& orderedList) = 0;
	/**
	 * Go along the tree in a pre-order order.
	 * @param[out] orderedList List in n pre-order order
	 */
	virtual void getPreorder(std::list<T>& orderedList) = 0;
	/**
	 * Go along the tree in a post-order order.
	 * @param[out] orderedList List in n pre-order order
	 */
	virtual void getPostorder(std::list<T>& orderedList) = 0;
	/**
	 * Get the height of the tree
	 * @param[in] root Node where to start calculating the height from
	 * @return Tree height
	 */
	virtual unsigned int getHeight(Node<T>* root) = 0;
	/**
	 * Converts the tree into a printable format
	 * @return Returns the string with the tree structure
	 */
	std::string toString() {
		std::string output = "";
		unsigned int height = getHeight(this->root);
		std::vector<std::string> outStrs = std::vector<std::string>(height + 1, "");
		getStrings(this->root, 0, height, outStrs);
		for (std::string s : outStrs) {
			output += s + "\n";
		}
		return output;
	}
private:
	/**
	 * Deletes the tree from a node
	 * @param[in] root Node to start removing
	 */
	void deleteTree(Node<T>* root) {
		if (root == nullptr)
			return;
		deleteTree(root->right);
		deleteTree(root->left);
		delete root;
	}
	/**
	 * Converts an element of type T to a string
	 * @param[in] element Element to convert
	 * @return String containing the element value
	 */
	std::string t2str(T element) {
		std::ostringstream os;
		os << element;
		return os.str();
	}

	/**
	 * This method obtain the strings corresponding to each tree level
	 * @param[in] root Root node for the tree
	 * @param[in] level Current level to process
	 * @param[in] height Tree height
	 * @param[out] strs List of strings corresponding to each level
	 */
	void getStrings(Node<T>* root, const unsigned int level, const unsigned int height, std::vector<std::string>& strs) {
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
};


template struct Node<int>;
template struct Node<float>;
template struct Node<double>;
template struct Node<std::string>;

} // end namespace tree

#endif /* SRC_TREE_BINARYTREE_H_ */
