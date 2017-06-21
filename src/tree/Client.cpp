/**
 * @file Client.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */
#include "BinaryTree.h"
#include <iostream>
#include <list>
#include <string>

int main() {

	tree::BinaryTree<int> binaryTree = tree::BinaryTree<int>();

//	binaryTree.insert(25);
//	binaryTree.insert(15);
//	binaryTree.insert(50);
//	binaryTree.insert(10);
//	binaryTree.insert(22);
//	binaryTree.insert(35);
//	binaryTree.insert(70);
//	binaryTree.insert(4);
//	binaryTree.insert(12);
//	binaryTree.insert(18);
//	binaryTree.insert(24);
//	binaryTree.insert(31);
//	binaryTree.insert(44);
//	binaryTree.insert(66);
//	binaryTree.insert(90);

	binaryTree.insert(5);
	binaryTree.insert(9);
	binaryTree.insert(3);
	binaryTree.insert(1);
	binaryTree.insert(6);
	binaryTree.insert(14);
	binaryTree.insert(4);
	binaryTree.insert(0);

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

	binaryTree.deleteNode(5);
	//std::cout << binaryTree.toString() << std::endl;
	orderedList.clear();
	std::cout << std::endl << "POST-ORDER: ";
	binaryTree.getPostorder(orderedList);
	for (int i : orderedList) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	return 0;
}


