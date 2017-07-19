/**
 * @file Client.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */
#include "AVLTree.h"
#include "BinarySearchTree.h"
#include <cassert>
#include <iostream>
#include <list>
#include <string>

template <typename T>
void logAndWait(int element, tree::BinarySearchTree<T> &tree, std::string action) {
	std::cout << "=========> " << action << " element " << element << std::endl;
	std::cout << tree.toString() << std::endl;
	system("read");
}

/*
 * This is the main, used for testing purposes
 */
int main() {

	tree::BinarySearchTree<int> binaryTree = tree::BinarySearchTree<int>();

	binaryTree.insertNode(new Node<int>(5));
	binaryTree.insertNode(new ExtendedNode<int, int>(9, 9));
	binaryTree.insertNode(new Node<int>(3));
	binaryTree.insertNode(new Node<int>(1));
	binaryTree.insertNode(new Node<int>(6));
	binaryTree.insertNode(new Node<int>(14));
	binaryTree.insertNode(new Node<int>(4));
	binaryTree.insertNode(new Node<int>(0));

	std::cout << "TREE:" << std::endl;
	std::cout << binaryTree.toString() << std::endl;

	std::list<Node<int>*> orderedList;
	orderedList.clear();
	std::cout << std::endl << "PRE-ORDER: ";
	binaryTree.getPreorder(orderedList);
	for (Node<int>* i : orderedList) {
		std::cout << i->key << " ";
	}
	std::cout << std::endl;

	orderedList.clear();
	std::cout << std::endl << "IN-ORDER: ";
	binaryTree.getInorder(orderedList);
	for (Node<int>* i : orderedList) {
		std::cout << i->key << " ";
	}
	std::cout << std::endl;

	orderedList.clear();
	std::cout << std::endl << "POST-ORDER: ";
	binaryTree.getPostorder(orderedList);
	for (Node<int>* i : orderedList) {
		std::cout << i->key << " ";
	}
	std::cout << std::endl;

	std::cout << "Remove element 5" << std::endl;
	binaryTree.deleteNode(5);
	std::cout << binaryTree.toString() << std::endl;

	std::cout << "Remove element 14" << std::endl;
	binaryTree.deleteNode(14);
	std::cout << binaryTree.toString() << std::endl;

	std::cout << "Remove element 3" << std::endl;
	binaryTree.deleteNode(3);
	std::cout << binaryTree.toString() << std::endl;

	std::cout << "Remove element 0" << std::endl;
	binaryTree.deleteNode(0);
	std::cout << binaryTree.toString() << std::endl;

	Node<int>* four = binaryTree.search(4);
	assert(four != nullptr);

	Node<int>* three = binaryTree.search(3);
	assert(three == nullptr);

	tree::AVLTree<int> avlTree = tree::AVLTree<int>();

	avlTree.insertNode(new Node<int>(1));
	logAndWait(1, avlTree, "insert");

	avlTree.insertNode(new ExtendedNode<int, int>(2, 2));
	logAndWait(2, avlTree, "insert");

	avlTree.insertNode(new Node<int>(3));
	logAndWait(3, avlTree, "insert");

	// Try to insert again the 2 => no effect

	avlTree.insertNode(new Node<int>(2));
	logAndWait(2, avlTree, "insert");

	avlTree.insertNode(new Node<int>(7));
	logAndWait(7, avlTree, "insert");

	avlTree.insertNode(new Node<int>(6));
	logAndWait(6, avlTree, "insert");

	avlTree.insertNode(new Node<int>(14));
	logAndWait(14, avlTree, "insert");

	avlTree.insertNode(new Node<int>(4));
	logAndWait(4, avlTree, "insert");

	avlTree.insertNode(new Node<int>(0));
	logAndWait(0, avlTree, "insert");

	avlTree.insertNode(new Node<int>(15));
	logAndWait(15, avlTree, "insert");

	avlTree.insertNode(new Node<int>(5));
	logAndWait(5, avlTree, "insert");

	avlTree.deleteNode(6);
	logAndWait(6, avlTree, "delete");

	return 0;
}

