/**
 * @file Btree.cpp
 * @author Ronald T. Fernandez
 * @version 1.0
 */

#include "Btree.h"

namespace tree {

template <typename T>
Btree<T>::Btree(unsigned short d) : d(d), root(nullptr) {

}

template <typename T>
Btree<T>::~Btree() {
}

} /* namespace tree */
