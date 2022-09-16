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
    Pointer& findLastLeft(Pointer &start);
public:
    SortedBinTree();
    void insert(T value);
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
Pointer& SortedBinTree<T>::findNearestNodeNonRecursive(T value, Pointer &start) {
    enum Direction {D_NONE, D_LEFT, D_RIGHT} direction;

    Pointer current = start;
    Pointer previous = nullptr;
    direction = D_NONE;

    while(true) {
        if (value==current->value) {
            if (direction==D_NONE) {
                return start;
            } else if (direction==D_LEFT) {
                return previous->left;
            } else {
                return previous->right;
            }

        } else if (value<current->value) {
            if (current->left==nullptr) return current->left;
            previous = current;
            current = current->left;
        } else {
            if (current->right==nullptr) return current->right;
            previous = current;
            current = current->right;
        }
    }
}

template <class T>
Pointer& SortedBinTree<T>::findLastLeft(Pointer &start) {
    if (start->left==nullptr) return start;

    Pointer current = start;
    Pointer previous = nullptr;

    while (current->left!=nullptr) {
        previous = current;
        current = current->left;
    }

    return previous->left;
}

template<class T>
void SortedBinTree<T>::insert(T value) {
    Pointer tmp = newSortedBinTreeElement(value);
    if (root==nullptr) {
        root = tmp;
        return;
    }

    Pointer& node = findNearestNodeNonRecursive(value, root);

    if (node!=nullptr && node->value==value) return;

    node = tmp;
}

template<class T>
bool SortedBinTree<T>::remove(T value) {
    if (root == nullptr) return false;

    Pointer& node = findNearestNodeNonRecursive(value, root);
    if (node!=nullptr) {
        node==nullptr;
        return true;
    }

    return false;
}



#undef Pointer
#undef newQueueElement

#endif //SIMPLIFIED_DATA_STRUCTURES_TREE_H
