//
// Created by lalev on 13.09.22.
//

#ifndef SIMPLIFIED_DATA_STRUCTURES_DEQUE_H
#define SIMPLIFIED_DATA_STRUCTURES_DEQUE_H

#include <memory>
#include <optional>

#define Pointer std::shared_ptr<DequeElement<T>>
#define newDequeElement(X) (std::make_shared<DequeElement<T>>(X))

using namespace std;

template <class T> class DequeElement {
public:
    T value;
    Pointer previous;
    Pointer next;
    explicit DequeElement(T newValue);
};

template <class T> class Deque {
protected:
    Pointer first;
    Pointer last;
public:
    Deque();
    void pushFirst(T value);
    optional<T> popFirst();
    optional<T> peekFirst();
    void pushLast(T value);
    optional<T> popLast();
    optional<T> peekLast();
    void forEach(void (*consumer)(T value));
};

template<class T>
DequeElement<T>::DequeElement(T newValue) : value(newValue) {}


template<class T>
Deque<T>::Deque() : first(nullptr), last(nullptr) {}

template<class T>
void Deque<T>::pushFirst(T value) {
    Pointer tmp = newDequeElement(value);

    if (first == nullptr) {
        first = tmp;
        last = tmp;
    } else {
        first->previous = tmp;
        tmp->next = first;
        first = tmp;
    }
}

template<class T>
optional<T> Deque<T>::popFirst() {
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

template<class T>
optional<T> Deque<T>::peekFirst() {
    if (first==nullptr) return {};
    return first->value;
}

template<class T>
void Deque<T>::pushLast(T value) {
    Pointer tmp = newDequeElement(value);

    last->next = tmp;
    tmp->previous = last;
    last = tmp;
}

template<class T>
optional<T> Deque<T>::popLast() {
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

template<class T>
optional<T> Deque<T>::peekLast() {
    if (last==nullptr) return {};
    return last->value;
}

template<class T>
void Deque<T>::forEach(void (*consumer)(T)) {
    Pointer tmp = first;
    while (tmp != nullptr) {
        consumer(tmp->value);
        tmp = tmp->next;
    }
}

#undef Pointer
#undef newDequeElement

#endif //SIMPLIFIED_DATA_STRUCTURES_DEQUE_H
