/**
 * @file Client.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */
#include "BinarySearchTree.h"
#include <iostream>
#include <list>
#include <string>

/*
 * This is the main, used for testing purposes
 */
int main() {

	tree::BinarySearchTree<int> binaryTree = tree::BinarySearchTree<int>();

//	binaryTree.insertNode(25);
//	binaryTree.insertNode(15);
//	binaryTree.insertNode(50);
//	binaryTree.insertNode(10);
//	binaryTree.insertNode(22);
//	binaryTree.insertNode(35);
//	binaryTree.insertNode(70);
//	binaryTree.insertNode(4);
//	binaryTree.insertNode(12);
//	binaryTree.insertNode(18);
//	binaryTree.insertNode(24);
//	binaryTree.insertNode(31);
//	binaryTree.insertNode(44);
//	binaryTree.insertNode(66);
//	binaryTree.insertNode(90);

	binaryTree.insertNode(5);
	binaryTree.insertNode(9);
	binaryTree.insertNode(3);
	binaryTree.insertNode(1);
	binaryTree.insertNode(6);
	binaryTree.insertNode(14);
	binaryTree.insertNode(4);
	binaryTree.insertNode(0);

	std::cout << "TREE:" << std::endl;
	std::cout << binaryTree.toString() << std::endl;

	std::list<int> orderedList;
	orderedList.clear();
	std::cout << std::endl << "PRE-ORDER: ";
	binaryTree.getPreorder(orderedList);
	for (int i : orderedList) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	orderedList.clear();
	std::cout << std::endl << "IN-ORDER: ";
	binaryTree.getInorder(orderedList);
	for (int i : orderedList) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	orderedList.clear();
	std::cout << std::endl << "POST-ORDER: ";
	binaryTree.getPostorder(orderedList);
	for (int i : orderedList) {
		std::cout << i << " ";
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

	return 0;
}


