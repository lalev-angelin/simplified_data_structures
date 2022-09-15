//
// Created by lalev on 13.09.22.
//

#ifndef SIMPLIFIED_DATA_STRUCTURES_TREE_H
#define SIMPLIFIED_DATA_STRUCTURES_TREE_H

#include <memory>
#include <optional>
#include "Queue.h"

using namespace std;

#define Pointer shared_ptr<SortedBinTreeElement<T>>
#define newSortedBinTreeElement(X) (make_shared<SortedBinTreeElement<T>>(X))

template <class T> class SortedBinTreeElement {
public:
    Pointer left;
    Pointer right;
    T value;
    explicit SortedBinTreeElement(T newValue);
};

template <class T> class SortedBinTree {
private:
    Pointer root;
    Pointer findLastNodeNonRecursive(T value);
public:
    SortedBinTree();
    bool insert(T value);
    bool remove(T value);
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
Pointer SortedBinTree<T>::findLastNodeNonRecursive(T value) {

    Pointer current = root;
    while (current != nullptr) {
        if (value == current->value) break;
        if (value < current->value) {
            if (current->left == nullptr) break;
            current = current->left;
        } else {
            if (current->right == nullptr) break;
            current = current->right;
        }
    }

    return current;
}

template<class T>
bool SortedBinTree<T>::insert(T value) {
    Pointer tmp = newSortedBinTreeElement(value);
    Pointer node = findLastNodeNonRecursive(value);

    if (node==nullptr) {
        root = tmp;
        return true;
    }

    if (value == node->value) return false;

    if (value < node->value) {
        node->left = tmp;
    } else {
        node->right=tmp;
    }

    return true;
}

template<class T>
bool SortedBinTree<T>::remove(T value) {
    return false;
}

#undef Pointer
#undef newQueueElement

#endif //SIMPLIFIED_DATA_STRUCTURES_TREE_H
