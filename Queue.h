//
// Created by lalev on 11.09.22.
//

#ifndef SIMPLIFIED_DATA_STRUCTURES_QUEUE_H
#define SIMPLIFIED_DATA_STRUCTURES_QUEUE_H

#include <memory>
#include <optional>

using namespace std;

#define Pointer shared_ptr<QueueElement<T>>
#define newQueueElement(X) (make_shared<QueueElement<T>>(X))

template <class T>
class QueueElement {
public:
    Pointer next;
    T value;
    explicit QueueElement(T newValue);
};

template<class T>
class Queue {
private:
    Pointer first;
    Pointer last;
public:
    Queue();
    void pushLast(T value);
    optional<T> popFirst();
    optional<T> peekFirst();
    void forEach(void (*consumer)(T& value));
};

template<class T>
QueueElement<T>::QueueElement(T newValue) : value(newValue), next(nullptr) {}


template<class T>
Queue<T>::Queue() : first(nullptr), last(nullptr) {};

template<class T>
void Queue<T>::pushLast(T value) {
    Pointer tmp = newQueueElement(value);
    if (last != nullptr) {
        last->next = tmp;
        last = tmp;
    } else {
        last = tmp;
        first = tmp;
    }
}

template<class T>
optional<T> Queue<T>::popFirst() {
    if (first == nullptr) return {};
     Pointer tmp = first;
     first = first->next;
     if (first == nullptr) {
         last = nullptr;
     }
     return tmp->value;
}

template<class T>
optional<T> Queue<T>::peekFirst() {
    if (first==nullptr) return {};
    return first->value;
}

template<class T>
void Queue<T>::forEach(void (*consumer)(T &)) {
    Pointer tmp = first;
    while (tmp!=nullptr) {
        consumer(tmp->value);
        tmp = tmp->next;
    }
}


#undef Pointer
#undef newQueueElement

#endif //SIMPLIFIED_DATA_STRUCTURES_QUEUE_H
