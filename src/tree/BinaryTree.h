/**
 * @file Tree.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_BINARYTREE_H_
#define SRC_TREE_BINARYTREE_H_

#include <list>
#include <string>
#include <vector>

namespace tree {

template<typename T>
struct Node {
	T value;
	Node* left;
	Node* right;
	Node(T value) {
		this->value = value;
		this->left = nullptr;
		this->right = nullptr;
	}
};

template<typename T>
class BinaryTree {
private:
	Node<T>* root;
	void getStrings(Node<T>* root, const unsigned int level, const unsigned int height, std::vector<std::string>& strs);
	void deleteTree(Node<T>* root);
	void getInorder(Node<T>* root, std::list<T>& orderedList);
	void getPreorder(Node<T>* root, std::list<T>& orderedList);
	void getPostorder(Node<T>* root, std::list<T>& orderedList);
	std::string t2str(T element);
public:
	BinaryTree();
	~BinaryTree();
	void insert(const T& value);
	void getInorder(std::list<T>& orderedList);
	void getPreorder(std::list<T>& orderedList);
	void getPostorder(std::list<T>& orderedList);
	Node<T>* search(const T& element) const;
	unsigned int getHeight(Node<T>* root);
	std::string toString();
};


} /* namespace tree */

#endif /* SRC_TREE_BINARYTREE_H_ */
