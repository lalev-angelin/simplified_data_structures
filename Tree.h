//
// Created by lalev on 13.09.22.
//

#ifndef SIMPLIFIED_DATA_STRUCTURES_TREE_H
#define SIMPLIFIED_DATA_STRUCTURES_TREE_H

#include <memory>

using namespace std;

#define Pointer shared_ptr<SortedBinTreeElement<T>>
#define newQueueElement(X) (make_shared<SortedBinTreeElement<T>>(X))

template <class T> class SortedBinTreeElement {
public:
    Pointer left;
    Pointer right;
    T value;
    explicit SortedBinTreeElement(T newValue);
};

template <class T> class SortedBinTree {
private:
    Pointer top;
public:
    SortedBinTree();
    insert(T value);
    delete(T value);
    T& get
    forEach(void (*consumer)(T& value))
    search(bool (*predicate)(T value));
};

template<class T>
SortedBinTreeElement<T>::SortedBinTreeElement(T newValue) : value(newValue), left(nullptr), right(nullptr) {};

template <class T>
SortedBinTree<T>::SortedBinTree() : top(nullptr) {};

SortedBinTree<T


#undef Pointer
#undef newQueueElement

#endif //SIMPLIFIED_DATA_STRUCTURES_TREE_H
