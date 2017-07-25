FLAGS = -g -std=c++11 -Wall
all:
	g++ $(FLAGS) -c BinarySearchTree.cpp
	g++ $(FLAGS) -c AVLTree.cpp
	g++ $(FLAGS) -c Btree.cpp
	g++ $(FLAGS) -o BinaryTree BinarySearchTree.o AVLTree.o Btree.o Client.cpp
clean:
	rm *.o BinaryTree
