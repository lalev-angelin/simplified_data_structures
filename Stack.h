//
// Created by lalev on 07.09.22.
//

#ifndef SIMPLIFIED_DATA_STRUCTURES_STACK_H
#define SIMPLIFIED_DATA_STRUCTURES_STACK_H

#include <memory>
#include <optional>

using namespace std;

#define Pointer std::shared_ptr<StackElement<T>>
#define newStackElement(X) (std::make_shared<StackElement<T>>(X))

template <class T> class StackElement {
public:
    T data;
    Pointer next;
    explicit StackElement(T value);
};


template <class T> class Stack {
protected:
    Pointer top;
public:
    Stack();
    void push(T data);
    optional<T> pop();
    optional<T> peek() const;
    void forEach(void (*consumer)(T& element));
};

template<class T>
StackElement<T>::StackElement(T newData) : data(newData), next(nullptr) {}

template<class T>
Stack<T>::Stack() {
    top = nullptr;
}

template<class T>
void Stack<T>::push(T data) {
    Pointer tmp = newStackElement(data);
    tmp->next = top;
    top = tmp;
}

template<class T>
optional<T> Stack<T>::pop() {
    if (top==nullptr) return {};
    Pointer tmp = top;
    top = top->next;
    return tmp->data;
}

template<class T>
optional<T> Stack<T>::peek() const {
    if (top==nullptr) return {};
    return top->data;
}

template<class T>
void Stack<T>::forEach(void (*consumer)(T& data)) {
    Pointer tmp = top;
    while (tmp!=nullptr) {
        consumer(tmp->data);
        tmp = tmp->next;
    }
}

#undef Pointer
#undef newElement

#endif //SIMPLIFIED_DATA_STRUCTURES_STACK_H
