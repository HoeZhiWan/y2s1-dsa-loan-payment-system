#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"
#include <stdexcept>

using namespace std;

template <typename Type>
class Queue {
private:
    LinkedList<Type> list;

public:
    void enqueue(const Type& item);
    bool dequeue(Type& item);
    Type getFront() const;
    Type getRear() const;
    bool isEmpty() const;
    int size() const;
    const LinkedList<Type>& getList() const;
};

#endif
