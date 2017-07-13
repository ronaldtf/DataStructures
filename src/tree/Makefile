FLAGS = -g -std=c++11 -Wall
all:
	g++ $(FLAGS) -c BinarySearchTree.cpp
	g++ $(FLAGS) -c AVLTree.cpp
	g++ $(FLAGS) -o BinaryTree BinarySearchTree.o AVLTree.o Client.cpp
clean:
	rm *.o BinaryTree
