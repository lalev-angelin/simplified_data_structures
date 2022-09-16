//
// Created by lalev on 08.09.22.
//

#ifndef SIMPLIFIED_DATA_STRUCTURES_INTSTACK_H
#define SIMPLIFIED_DATA_STRUCTURES_INTSTACK_H

#include <memory>
#include <optional>

using namespace std;

#define Pointer std::shared_ptr<IntStackElement>
#define newIntStackElement(X) (std::make_shared<IntStackElement>(X))

class IntStackElement {
public:
    int data;
    Pointer next;
    explicit IntStackElement(int newData);
};

class IntStack {
protected:
    Pointer top;
public:
    IntStack();
    void push(int data);
    optional<int> pop();
    optional<int> peek() const;
    void forEach(void (*consumer)(int& value));
};

IntStackElement::IntStackElement(int newData) {
    data = newData;
    next = nullptr;
}

IntStack::IntStack() {
    top = nullptr;
}

void IntStack::push(int data) {
    Pointer tmp = newIntStackElement(data);
    tmp->next = top;
    top = tmp;
}

optional<int> IntStack::pop() {
    if (top==nullptr) return {};
    Pointer tmp = top;
    top = top->next;
    return tmp->data;
}

optional<int> IntStack::peek() const {
    if (top==nullptr) return {};
    return top->data;
}

void IntStack::forEach(void (*consumer)(int &)) {
    Pointer tmp = top;
    while (tmp!=nullptr) {
        consumer(tmp->data);
        tmp=tmp->next;
    }
}

#undef Pointer
#undef newIntStackElement

#endif //SIMPLIFIED_DATA_STRUCTURES_INTSTACK_H
