//
// Created by lalev on 09.09.22.
//

#ifndef SIMPLIFIED_DATA_STRUCTURES_INTQUEUE_H
#define SIMPLIFIED_DATA_STRUCTURES_INTQUEUE_H

#include <memory>
#include <optional>

using namespace std;

#define Pointer std::shared_ptr<IntQueueElement>
#define makeIntQueueElement(X) (std::make_shared<IntQueueElement>(X))

class IntQueueElement {
public:
    int data;
    Pointer next;
    explicit IntQueueElement(int newData);
};

class IntQueue {
private:
    Pointer first;
    Pointer last;
public:
    IntQueue();
    void pushLast(int data);
    optional<int> popFirst();
    optional<int> peekFirst();
    void forEach(void (*consumer)(int& data));
};


IntQueueElement::IntQueueElement(int newData)  : data(newData) {};

IntQueue::IntQueue() : first(nullptr), last(nullptr) {};

void IntQueue::pushLast(int data) {
    Pointer tmp = makeIntQueueElement(data);
    if (last!=nullptr) {
        last->next = tmp;
        last = tmp;
    } else {
        last = tmp;
        first = tmp;
    }
}

optional<int> IntQueue::popFirst() {
    if (first==nullptr) return {};

    Pointer tmp = first;
    first = first->next;
    if (first==nullptr) {
        last=nullptr;
    }
    return tmp->data;
}

optional<int> IntQueue::peekFirst() {
    if (first==nullptr) return {};
    return first->data;
}

void IntQueue::forEach(void (*consumer)(int &)) {
    Pointer tmp = first;
    while (tmp!=nullptr) {
        consumer(tmp->data);
        tmp = tmp->next;
    }
}

#undef Pointer
#undef makeIntQueueElement

#endif //SIMPLIFIED_DATA_STRUCTURES_INTQUEUE_H
