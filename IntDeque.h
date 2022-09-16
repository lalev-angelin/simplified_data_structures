//
// Created by lalev on 14.09.22.
//

#ifndef SIMPLIFIED_DATA_STRUCTURES_INTDEQUE_H
#define SIMPLIFIED_DATA_STRUCTURES_INTDEQUE_H

#include <memory>
#include <optional>

#define Pointer std::shared_ptr<IntDequeElement>
#define newIntDequeElement(X) (std::make_shared<IntDequeElement>(X))

using namespace std;

class IntDequeElement {
protected:
    int value;
    Pointer previous;
    Pointer next;
    explicit IntDequeElement(int newValue);
};

class IntDeque {
private:
    Pointer first;
    Pointer last;
public:
    IntDeque();
    void pushFirst(int value);
    optional<int> popFirst();
    optional<int> peekFirst();
    void pushLast(int value);
    optional<int> popLast();
    optional<int> peekLast();
    void forEach(void (*consumer)(int value));
};

IntDequeElement::IntDequeElement(int newValue) : value(newValue) {}

IntDeque::IntDeque() : first(nullptr), last(nullptr) {}

void IntDeque::pushFirst(int value) {
    Pointer tmp = newIntDequeElement(value);

    if (first == nullptr) {
        first = tmp;
        last = tmp;
    } else {
        first->previous = tmp;
        tmp->next = first;
        first = tmp;
    }
}

optional<int> IntDeque::popFirst() {
    if (first==nullptr) {
        return {};
    }

    Pointer tmp = first;
    first = first->next;
    if (first==nullptr) {
        last=nullptr;
    } else {
        first->previous = nullptr;
    }

    return tmp->value;
}

optional<int> IntDeque::peekFirst() {
    if (first==nullptr) return {};
    return first->value;
}

void IntDeque::pushLast(int value) {
    Pointer tmp = newIntDequeElement(value);

    last->next = tmp;
    tmp->previous = last;
    last = tmp;
}

optional<int> IntDeque::popLast() {
    if (last==nullptr) {
        return {};
    }

    Pointer tmp = last;
    last = last->previous;
    if (last==nullptr) {
        first=nullptr;
    } else {
        last->next = nullptr;
    }

    return tmp->value;
}

optional<int> IntDeque::peekLast() {
    if (last==nullptr) return {};
    return last->value;
}

void IntDeque::forEach(void (*consumer)(int value)) {
    Pointer tmp = first;
    while (tmp != nullptr) {
        consumer(tmp->value);
        tmp = tmp->next;
    }
}

#undef Pointer
#undef newIntDequeElement

#endif //SIMPLIFIED_DATA_STRUCTURES_INTDEQUE_H
