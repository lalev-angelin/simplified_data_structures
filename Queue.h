//
// Created by lalev on 11.09.22.
//

#ifndef SIMPLIFIED_DATA_STRUCTURES_QUEUE_H
#define SIMPLIFIED_DATA_STRUCTURES_QUEUE_H

#include <memory>
#include <optional>

using namespace std;

#define Pointer shared_ptr<T>
#define newQueueElement(X) (make_ptr<T>(X))

template <class T>
class QueueElement {
public:
    Pointer next;
    T value;
    QueueElement(T newValue);
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
Queue<T>::Queue() {

}


#undef Pointer
#undef newQueueElement

#endif //SIMPLIFIED_DATA_STRUCTURES_QUEUE_H
