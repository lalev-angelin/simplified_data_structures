//
// Created by lalev on 13.09.22.
//

#ifndef SIMPLIFIED_DATA_STRUCTURES_TREE_H
#define SIMPLIFIED_DATA_STRUCTURES_TREE_H

#include <memory>
#include <optional>
#include <string>
#include "Queue.h"

using namespace std;

#define Pointer shared_ptr<SortedBinTreeElement<T>>
#define newSortedBinTreeElement(X) (make_shared<SortedBinTreeElement<T>>(X))

#define PPointer shared_ptr<Pointer>
#define newPPointer make_shared<Pointer>

template <class T> class SortedBinTreeElement {
public:
    Pointer left;
    Pointer right;
    T value;
    explicit SortedBinTreeElement(T newValue);
};


template <class T> class SortedBinTree {
protected:
    Pointer root;
    Pointer& findNearestNodeNonRecursive(T value, Pointer &start);
public:
    SortedBinTree();
    void insert(T value);
//    bool remove(T value);
//    bool has(T value);
//    void forEach(void (*consumer)(T& value));
//
//
//    void insert(T value, int (*comparator)(T value));
//    bool has(bool (*predicate)(T value));
//    bool remove(bool (*predicate)(T value));
//
//    Queue<T> findAll(bool (*predicate)(T value));
};

template<class T>
SortedBinTreeElement<T>::SortedBinTreeElement(T newValue) : value(newValue), left(nullptr), right(nullptr) {};

template <class T>
SortedBinTree<T>::SortedBinTree() : root(nullptr) {}

template <class T>
Pointer& SortedBinTree<T>::findNearestNodeNonRecursive(T value, Pointer &start) {

    PPointer current = newPPointer(start);

    while(true) {
        if (value==(*current)->value) {
            return (*current);
        } else if (value<(*current)->value) {
            if ((*current)->left== nullptr) return (*current)->left;
            current = newPPointer((*current)->left);
        } else {
            if ((*current)->right==nullptr) return (*current)->right;
            current = newPPointer((*current)->right);
        }
    }
}

template<class T>
void SortedBinTree<T>::insert(T value) {
    Pointer tmp = newSortedBinTreeElement(value);
    if (root==nullptr) {
        root = tmp;
        return;
    }

    Pointer& node = findNearestNodeNonRecursive(value, root);
    node = tmp;
}


#undef PPointer
#undef newPPointer
#undef Pointer
#undef newQueueElement

#endif //SIMPLIFIED_DATA_STRUCTURES_TREE_H
