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
	avlTree.insertNode(new ExtendedNode<int, int>(2, 2));
	avlTree.insertNode(new Node<int>(3));

	// Try to insert again the 2 => no effect
	avlTree.insertNode(new Node<int>(2));

	avlTree.insertNode(new Node<int>(7));
	avlTree.insertNode(new Node<int>(6));
	avlTree.insertNode(new Node<int>(14));
	avlTree.insertNode(new Node<int>(4));
	avlTree.insertNode(new Node<int>(0));
	std::cout << avlTree.toString() << std::endl;



	return 0;
}

