#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include <functional>

using namespace std;

template <typename Type>
class LinkedList
{
private:
    struct Node {
        Type data;
        Node* next;
        Node* prev;

        Node(const Type& value);
    };

    Node* head;
    Node* tail;
    int listSize;

public:
    LinkedList();                                       // Constructor
    ~LinkedList();                                      // Destructor
    LinkedList(const LinkedList& other);                // Copy Constructor
    LinkedList& operator=(const LinkedList& other);     // Copy Assignment Operator    

    void push_back(const Type& value);                  // Add to end
    void push_front(const Type& value);                 // Add to front
    void insert(const Type& value, int index);          // Insert at index
    void remove(int index);                             // Remove at index  
    void clear();                                       // Clear list

    Type& operator[](int index);                        // Access element at index                 
    const Type& operator[](int index) const;            // Access element at index (const)

    int size() const;                                   // Get size of list       
    bool empty() const;                               // Check if list is empty

    class Iterator {
    private:
        Node* current;  
    public:
        Iterator(Node* node) : current(node) {}
        Type& operator*() { 
            return current->data;
        }
        Iterator& operator++() {
            current = current->next;
            return *this;
        }
        Iterator& operator--() {
            current = current->prev;
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    class ConstIterator {
    private:
        const Node* current;
    public:
        ConstIterator(const Node* node) : current(node) {}
        const Type& operator*() const { 
            return current->data;
        }
        ConstIterator& operator++() {
            current = current->next;
            return *this;
        }
        ConstIterator& operator--() {
            current = current->prev;
            return *this;
        }
        bool operator!=(const ConstIterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }
    Iterator end() {
        return Iterator(nullptr);
    }

    ConstIterator begin() const {
        return ConstIterator(head);
    }
    
    ConstIterator end() const {
        return ConstIterator(nullptr);
    }
};

#endif