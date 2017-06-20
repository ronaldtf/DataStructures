/**
 * @file Client.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */
#include "BinaryTree.h"
#include <iostream>
#include <string>

int main() {

	tree::BinaryTree<int> binaryTree = tree::BinaryTree<int>();
	binaryTree.insert(5);
	binaryTree.insert(9);
	binaryTree.insert(3);
	binaryTree.insert(1);
	binaryTree.insert(6);
	binaryTree.insert(14);
	binaryTree.insert(4);
	binaryTree.insert(0);
	binaryTree.insert(10);
	binaryTree.insert(11);

	std::cout << binaryTree.toString() << std::endl;
	return 0;
}


