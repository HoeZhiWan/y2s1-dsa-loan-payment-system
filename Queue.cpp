#include "Queue.h"
#include "payment.h"
#include "loan.h"
#include <stdexcept>

template <typename Type>
void Queue<Type>::enqueue(const Type& item) {
    list.push_back(item);
}

template <typename Type>
bool Queue<Type>::dequeue(Type& item) {
    if (isEmpty()) return false;
    item = list[0];
    list.remove(0);
    return true;
}

template <typename Type>
Type Queue<Type>::getFront() const {
    if (isEmpty()) throw std::runtime_error("Queue is empty");
    return list[0];
}

template <typename Type>
Type Queue<Type>::getRear() const {
    if (isEmpty()) throw std::runtime_error("Queue is empty");
    // Access the last element
    return list[list.size() - 1];
}

template <typename Type>
bool Queue<Type>::isEmpty() const {
    return list.empty();
}

template <typename Type>
int Queue<Type>::size() const {
    return list.size();
}

template <typename Type>
const LinkedList<Type>& Queue<Type>::getList() const {
    return list;
}

// Explicit Instantiations
template class Queue<Payment>;
template class Queue<Loan>;
