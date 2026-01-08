#ifndef PAYMENTQUEUE_H
#define PAYMENTQUEUE_H
#include "payment.h"

struct PaymentNode {
    Payment item;
    PaymentNode* next;

    PaymentNode(const Payment& p) : item(p), next(nullptr) {}
};

class PaymentQueue {
private:
    PaymentNode* frontPtr;   
    PaymentNode* backPtr;    

public:
    
    PaymentQueue();

    ~PaymentQueue();

    bool isEmpty() const;

    void enqueue(const Payment& newItem);

    bool dequeue(Payment& frontItem);

    Payment getFront() const;

    Payment getRear() const;
};







#endif