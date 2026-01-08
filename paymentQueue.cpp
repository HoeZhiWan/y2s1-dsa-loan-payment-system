#include <iostream>
#include "paymentQueue.h"

using namespace std;

PaymentQueue::PaymentQueue() : frontPtr(nullptr), backPtr(nullptr) {}

PaymentQueue::~PaymentQueue() {
    PaymentNode* temp = frontPtr;
    while (temp != nullptr) {
        frontPtr = temp->next;
        delete temp;
        temp = frontPtr;
    }
    backPtr = nullptr;
}

bool PaymentQueue::isEmpty() const {
    return (frontPtr == nullptr && backPtr == nullptr);
}

void PaymentQueue::enqueue(const Payment& newItem) {
    PaymentNode* newPtr = new PaymentNode(newItem);

    if (isEmpty()) {
        
        frontPtr = newPtr;
        backPtr  = newPtr;
    } else {
        
        backPtr->next = newPtr;
        backPtr       = newPtr;
    }
}


bool PaymentQueue::dequeue(Payment& frontItem) {
    if (isEmpty()) {
        cout << "[Queue] Cannot dequeue. Empty queue.\n";
        return false;
    }

  
    PaymentNode* tempPtr = frontPtr;
    frontItem = frontPtr->item;  

    
    frontPtr = frontPtr->next;

    
    if (frontPtr == nullptr) {
        backPtr = nullptr;
    }

    delete tempPtr;
    return true;
}


Payment PaymentQueue::getFront() const {
    if (isEmpty()) {
        throw runtime_error("getFront() called on empty queue");
    }
    return frontPtr->item;
}


Payment PaymentQueue::getRear() const {
    if (isEmpty()) {
        throw runtime_error("getRear() called on empty queue");
    }
    return backPtr->item;
}
