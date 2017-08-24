/**
 * @file Btree.h
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#ifndef SRC_TREE_BTREE_H_
#define SRC_TREE_BTREE_H_

#include "BNode.h"

#include <list>

namespace tree {

template<typename T>
class Btree {
private:
	unsigned short d;
	BNode<T>* root;
public:
	/**
	 * Class constructor.
	 * @param[in] d: minimum degree term. This defines the number of
	 *               minimum keys per node (d-1) - except for the root -
	 *               and the maximum (2*d-1).
	 */
	Btree(unsigned short d = 1);
	/**
	 * Class destructor
	 */
	virtual ~Btree();
	/**
	 * Search a given key in the b-tree
	 * @param[in] key Key to find
	 * @return Returns the node which contains the key, or nullptr
	 * if it is not found
	 */
	BNode<T>* search(const T& key);
	/**
	 * Go along the tree in an in-order order.
	 * @param[out] orderedList List in an in-order order
	 */
	void getInorder(std::list<T>& orderedList) const;
	/**
	 * Go along the tree in n pre-order order.
	 * @param[out] orderedList List in a pre-order order
	 */
	void getPreorder(std::list<T>& orderedList) const;
	/**
	 * Go along the tree in a post-order order.
	 * @param[out] orderedList List in a post-order order
	 */
	void getPostorder(std::list<T>& orderedList) const;
	/**
	 * Determines whether a node is a leaf node or not
	 * @param[in] node Node to be checked
	 * @return Returns whether the node is a leaf node or not
	 */
	bool isLeaf(BNode<T>* node);
	/**
	 * Insert an element into the tree (if it does not exist yet)
	 * @param[in] key	Key to add to the tree
	 * @param[in] value	Value associated to the key
	 */
	bool insert(T& key, T& value);
	/**
	 * Removes an element from the tree (if exists)
	 * @param[in] key 	Key to remove
	 * @return 	Returns whether the node has been removed or not
	 */
	bool remove(T& key);
private:
	/**
	 * Go along the tree in an in-order order.
	 * @param[in] root Root node
	 * @param[out] orderedList List in an in-order order
	 */
	void getInorder(BNode<T>* root, std::list<T>& orderedList) const;
	/**
	 * Go along the tree in n pre-order order.
	 * @param[in]  root        Root node
	 * @param[out] orderedList List in a pre-order order
	 */
	void getPreorder(BNode<T>* root, std::list<T>& orderedList) const;
	/**
	 * Go along the tree in a post-order order.
	 * @param[in]  root        Root node
	 * @param[out] orderedList List in a post-order order
	 */
	void getPostorder(BNode<T>* root, std::list<T>& orderedList) const;
	/**
	 * Search a given key in the b-tree
	 * @param[in] key 		Key to find
	 * @param[out] parent	Parent node for the searched key
	 * @return Returns the node which contains the key, or nullptr
	 * if it is not found
	 */
	BNode<T>* search(const T& key, BNode<T>** parent);
	/**
	 * Initialize a node and its children
	 * @param[out] node	 Node to initialize
	 * @param[in]  key	 Key to set to the node
	 * @param[in]  value Value to set to the node
	 */
	void initNode(BNode<T>** node, T& key, T& value);
	/**
	 * Insert an element into the tree
	 * @param[in] key Key element to insert in the tree
	 * @param[in] value Value element to insert in the tree
	 * @param[in] node Reference to the node where to start the insertion
	 * @param[in] parent Parent node for the current one
	 */
	bool insertElement(T& key, T&value, BNode<T>** node, BNode<T>** parent);
	/**
	 * Insert an element in the sorted place of the node (ascending order)
	 * @param[in]  key Key to add
	 * @param[in]  value Value to add
	 * @param[out] node Node to insert the values
	 */
	void insertInNoFullNode(T key, T value, BNode<T>** node);
	/**
	 * Removes an element from the tree starting from the node
	 * @param[in] key Key to remove
	 * @param[in] node Node to start searching
	 * @param[in] parent Parent of the node
	 */
	bool remove(T& key, BNode<T>**node, BNode<T>**parent);
	/**
	 * Copies the sibling key/value at a given position into the parent
	 * and the parent key/values to the target node
	 * @param[in] sibling Sibling node of the target
	 * @param[in] parent  Parent node of the target
	 * @param[in] target  Target node
	 * @param[in] parentI Position at the parent to be replace by the sibling
	 * @param[in] posSibling Position at the sibling whose key/value replace
	 *                    current parent ones
	 */
	void rotateAndKeepSibling(BNode<T>** sibling, BNode<T>** parent,
			BNode<T>** target, size_t parentI, size_t posSibling);
	/**
	 * Merge two siblings and remove the parent node
	 * @param[in] sibling Sibling node of the target node
	 * @param[in] target Target node
	 * @param[in] parent Parent node of siblings
	 * @param[in] parentI Position of the key parent for siblings
	 */
	void mergeAndRemove(BNode<T>** sibling, BNode<T>** target,
			BNode<T>** parent, size_t parentI);
	/**
	 * Get the position a key is found in the node, or the next one if not available
	 * @param[in] node Node to search in
	 * @param[in] key Key to search
	 * @return Position in the node
	 */
	size_t getPositionInNode(BNode<T>* node, T& key) const;

	/**
	 * Split the node in two parts
	 * @param[in|out] originalAndLeftNode Original node and left part of the node after the splitting.
	 * @param[out] right Right node after the splitting
	 * @param[out] midKey Key in the middle
	 * @param[out] midValue Value in the middle
	 */
	void splitNode(BNode<T>** originalAndLeftNode, BNode<T>** right, T& midKey,
			T& midValue);
};

} /* namespace tree */

#endif /* SRC_TREE_BTREE_H_ */
