/**
 * @file BNode.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_BNODE_H_
#define SRC_TREE_BNODE_H_

#include <string>
#include <vector>

namespace tree {

template <typename T>
struct BNode {
	std::vector<T> keys;
	std::vector<T> values;
	std::vector<BNode<T>*> children;
	BNode() : keys(), values(), children() {
	};
	virtual ~BNode() {
		keys.clear();
		values.clear();
		for (BNode<T>* node : children)
			delete node;
		children.clear();
	}
};
}

template struct tree::BNode<int> ;
template struct tree::BNode<float> ;
template struct tree::BNode<double> ;
template struct tree::BNode<std::string> ;

#endif /* SRC_TREE_BNODE_H_ */
