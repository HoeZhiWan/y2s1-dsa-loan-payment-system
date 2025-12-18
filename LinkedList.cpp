#include "linkedList.h"

#include "user.h"
#include "loan.h"
#include "payment.h"

using namespace std;

template <typename Type>
LinkedList<Type>::LinkedList(){
    head = nullptr;
    tail = nullptr;
    listSize = 0;
}

template <typename Type>
LinkedList<Type>::~LinkedList(){
    clear();
}

template <typename Type>
LinkedList<Type>::LinkedList(const LinkedList& other) {
    head = tail = nullptr;
    listSize = 0;
    
    for (const auto& item : other) {
        push_back(item);
    }
}

template <typename Type>
LinkedList<Type>& LinkedList<Type>::operator=(const LinkedList& other) {
    if (this == &other) {  
        return *this;
    }
    
    clear(); 

    for (const auto& item : other) {
        push_back(item);
    }
    
    return *this;
}

template <typename Type>
void LinkedList<Type>::push_back(const Type& value) {
    Node* newNode = new Node(value);
    if (empty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    listSize++;
}

template <typename Type>
void LinkedList<Type>::push_front(const Type& value) {
    Node* newNode = new Node(value);
    if (empty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    listSize++;
}

template <typename Type>
void LinkedList<Type>::insert(const Type& value, int index) {
    if (index < 0 || index > listSize) {
        return; 
    }
    if (index == 0) {
        push_front(value);
        return;
    }
    if (index == listSize) {
        push_back(value);
        return;
    }

    Node* newNode = new Node(value);
    Node* current = head;
    for (int i = 0; i < index - 1; ++i) {
        current = current->next;
    }
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
    listSize++;
}

template <typename Type>
void LinkedList<Type>::remove(int index) {
    if (index < 0 || index > listSize) {
        return; 
    }
    Node* toDelete;
    if (index == 0) {
        toDelete = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr; 
        }
    } else {
        Node* current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        toDelete = current->next;
        current->next = toDelete->next;
        if (toDelete->next) {
            toDelete->next->prev = current;
        } else {
            tail = current; 
        }
    }
    delete toDelete;
    listSize--;
}

template <typename Type>
void LinkedList<Type>::clear() {
    Node* current = head;
    while (current) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = tail = nullptr;
    listSize = 0;
}

template <typename Type>
Type& LinkedList<Type>::operator[](int index) {
    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename Type>
const Type& LinkedList<Type>::operator[](int index) const {
    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename Type>
int LinkedList<Type>::size() const {
    return listSize;
}

template <typename Type>
bool LinkedList<Type>::empty() const {
    return listSize == 0;
}

template <typename Type>
LinkedList<Type>::Node::Node(const Type& value) : 
    data(value), next(nullptr), prev(nullptr) {
        
}

template class LinkedList<User>;
template class LinkedList<Loan>;
template class LinkedList<Payment>;
template class LinkedList<string>;

