/**
 * @file Tree.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_BINARYTREE_H_
#define SRC_TREE_BINARYTREE_H_

namespace tree {

template<typename T>
class Node {
private:
	T* data;
public:
	Node();
	Node(T& data);
};

template<typename T>
class BinaryTree {
private:
	Node<T>* root;
	BinaryTree<T>* left;
	BinaryTree<T>* right;
private:
	void copyTree(BinaryTree& currentTree, const BinaryTree& anotherTree);
public:
	BinaryTree();
	BinaryTree(const BinaryTree& anotherTree);
	unsigned int getHeight();
	std::string toString();
};

} /* namespace tree */

#endif /* SRC_TREE_BINARYTREE_H_ */
