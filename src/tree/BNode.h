/**
 * @file BNode.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_BNODE_H_
#define SRC_TREE_BNODE_H_

#include <string>

namespace tree {

template <typename T>
struct BNode {
	BNode<T>** children;
	T* keys;
	T* values;
	int nKeys;
	unsigned short d;
	BNode(unsigned short d) : children(nullptr), keys(nullptr), values(nullptr), nKeys(0), d(d) {
	};
	virtual ~BNode() {
		if (nKeys > 0) {
			for (unsigned short nkey = 0; nkey < nKeys+1; ++nkey)
				delete children[nkey];
			delete children;
			delete keys;
			delete values;
			nKeys = 0;
		}
	}
};
}

template struct tree::BNode<int> ;
template struct tree::BNode<float> ;
template struct tree::BNode<double> ;
template struct tree::BNode<std::string> ;

#endif /* SRC_TREE_BNODE_H_ */
