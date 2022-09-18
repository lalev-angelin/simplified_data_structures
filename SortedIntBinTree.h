//
// Created by lalev on 13.09.22.
//

#ifndef SIMPLIFIED_DATA_STRUCTURES_SORTEDINTBINTREE_H
#define SIMPLIFIED_DATA_STRUCTURES_SORTEDINTBINTREE_H

#include <memory>
#include <optional>
#include <string>
#include "Queue.h"

using namespace std;

#define Pointer shared_ptr<SortedIntBinTreeElement>
#define newSortedIntBinTreeElement(X) (make_shared<SortedIntBinTreeElement>(X))

class SortedIntBinTreeElement {
public:
    Pointer left;
    Pointer right;
    int value;
    explicit SortedIntBinTreeElement(int newValue);
};


class SortedIntBinTree {
protected:
    Pointer root;
    Pointer& findNearestNodeNonRecursive(int value, Pointer &start);
    Pointer& findLastLeft(Pointer &start);
    void walkInOrderRecursive(void (*consumer)(int& value), Pointer start);
public:
    SortedIntBinTree();
    void insert(int value);
    bool remove(int value);
    bool has(int value);
    void forEach(void (*consumer)(int& value));
};

SortedIntBinTreeElement::SortedIntBinTreeElement(int newValue) : value(newValue), left(nullptr), right(nullptr) {};

SortedIntBinTree::SortedIntBinTree() : root(nullptr) {}

Pointer& SortedIntBinTree::findNearestNodeNonRecursive(int value, Pointer &start) {
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
            direction = D_LEFT;
        } else {
            if (current->right==nullptr) return current->right;
            previous = current;
            current = current->right;
            direction = D_RIGHT;
        }
    }
}

Pointer& SortedIntBinTree::findLastLeft(Pointer &start) {
    if (start->left==nullptr) return start;

    Pointer current = start;
    Pointer previous = nullptr;

    while (current->left!=nullptr) {
        previous = current;
        current = current->left;
    }

    return previous->left;
}

void SortedIntBinTree::insert(int value) {
    Pointer tmp = newSortedIntBinTreeElement(value);
    if (root==nullptr) {
        root = tmp;
        return;
    }

    Pointer& node = findNearestNodeNonRecursive(value, root);

    if (node!=nullptr && node->value==value) return;

    node = tmp;
}

bool SortedIntBinTree::remove(int value) {
    if (root == nullptr) return false;

    Pointer& node = findNearestNodeNonRecursive(value, root);
    if (node!=nullptr) {
        if (node->right==nullptr) {
            node = node->left;
        } else {
            Pointer &next = findLastLeft(node->right);
            Pointer tmp = newSortedIntBinTreeElement(next->value);
            tmp->left = node->left;
            tmp->right = node->right;
            node = tmp;
            next = next->right;
        }
        return true;
    }

    return false;
}

bool SortedIntBinTree::has(int value) {
    Pointer node = findNearestNodeNonRecursive(value, root);
    return node!=nullptr;
}

void SortedIntBinTree::forEach(void (*consumer)(int&)) {
    if (root==nullptr) return;
    walkInOrderRecursive(consumer, root);
}

void SortedIntBinTree::walkInOrderRecursive(void (*consumer)(int &), Pointer start) {
    if (start->left!=nullptr) {
        walkInOrderRecursive(consumer, start->left);
    }
    consumer(start->value);
    if (start->right!=nullptr) {
        walkInOrderRecursive(consumer, start->right);
    }
}

#undef Pointer
#undef newSortedIntBinTree

#endif //SIMPLIFIED_DATA_STRUCTURES_SORTEDINTBINTREE_H
