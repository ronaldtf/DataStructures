/**
 * @file Btree.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_BTREE_H_
#define SRC_TREE_BTREE_H_

#include "BNode.h"

namespace tree {

template <typename T>
class Btree {
private:
	unsigned short d;
	Btree<T>* root;
public:
	/**
	 * Class constructor.
	 * @param[in] d: minimum degree term. This defines the number of
	 *               minimum keys per node (d-1) and the maximum
	 *                (2*d-1).
	 */
	Btree(unsigned short d = 1);
	BNode<T>* search(const T& key);
	virtual ~Btree();
};

} /* namespace tree */

#endif /* SRC_TREE_BTREE_H_ */
