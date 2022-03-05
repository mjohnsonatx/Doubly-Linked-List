//***************************************************************
// Filename: LinkedList.h                                       *
// Name: Michael Johnson                                        *
// Course: CS 3358-256                                          *
//***************************************************************
// This program is a template of a doubly linked list that will *
// allow the storage of one value in ascending order. It        *
// includes the conventional functions necessary to modify the  *
// list including adding to the list in ascending order,        *
// removing a particular value, printing the list forward and   *
// backward, ascertaining the last value, determining if a      *
// value is contained in the list, and the length of the list.  *
//***************************************************************


#ifndef LINKEDLISTV3_H_INCLUDED
#define LINKEDLISTV3_H_INCLUDED

#include <assert.h>
#include <iostream>

using namespace std;

// See comment at top of file for description.

template <class T>
class LinkedList {

private:
    struct Node {
        Node* previous;
        Node* next;
        T value;
    };
    Node* head;
    Node* tail;
    T getLast(Node* p);

public:
    LinkedList();
    ~LinkedList();
    void insert(const T value);
    bool remove(const T value);
    bool contains(const T value);
    size_t length() const;
    void print_forwards() const;
    void print_backwards() const;
    bool isEmpty();
    T getLast();
};

//*************************************************************************
// LinkedList is the default constructor for this class and allocates two *
// pointers set to NULL.                                                  *
//*************************************************************************

template <class T>
LinkedList<T>::LinkedList() {
    head = NULL;
    tail = NULL;
}

//*****************************************************************************
// ~LinkedList is the destructor called when the scope of the class is left.  *                   *
//*****************************************************************************

template <class T>
LinkedList<T>::~LinkedList() {

    Node* p = head;
    while (!isEmpty()) {
        p = p->next;
        delete p;
    }
}

//******************************************************************************
// LinkedList::<T>insert is the function used to insert a new node into the    *
// list in ascending order.                                                    *
// Parameters: template argument.
// *****************************************************************************
template <class T>
void LinkedList<T>::insert(const T value) {

    Node* newNode = new Node;
    newNode->value = value;

    // If the list is empty.
    if (head == NULL) {
        head = newNode;
        head->previous = NULL;

        tail = newNode;
        tail->next = NULL;
    }
    else {
        Node* p = head;

        //To find the correct position in list.
        while ((p) && p->value < value)
            p = p->next;

        // If the added value is inserted at the tail.
        if (p == NULL) {
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
            tail->next = NULL;
        }
        else {

            // If the new value is the smallest value.
            if (p == head) {
                head->previous = newNode;
                newNode->next = head;
                head = newNode;
                head->previous = NULL;
            }

            // The new value was inserted within the list.
            else {
                // attaches new node behind p.
                newNode->previous = p->previous;

                // attaches the previous node's next pointer to the new node.
                p->previous->next = newNode;

                // points the new node to the node p is.
                newNode->next = p;

                // points the previous pointer of the node after new node to.
                // new node
                p->previous = newNode;
            }
        }
    }
}

//******************************************************************************
// LinkedList<T>::remove removes the node matching the argument passed to it.  *
// Parameter: template argument.
//******************************************************************************
template <class T>
bool LinkedList<T>::remove(const T value) {
    Node* p = head;

    // find the node to remove
    while ((p) && p->value != value)
        p = p->next;

    // the value is not found.
    if (p == NULL || p->value != value)
        return 0; // returned false.

    else {

        // if there is one node it is removed by resetting it to Null.
        if (p == head && p == tail) {
            head = NULL;
            tail = NULL;
        }

        // if the node to be removed is the head.
        else if (p == head) {
            head = p->next;
            head->previous = NULL;
        }

        // node to be removed is the tail.
        else if (p == tail) {
            tail = p->previous;
            tail->next = NULL;
        }

        // the node to be removed is within the list.
        else {

            // points the node following the node to be removed to the node
            // behind the node being removed.
            p->next->previous = p->previous;

            // points the node behind p to the node in front of p.
            p->previous->next = p->next;
        }
    }
    delete p;
    return 1;
}

//******************************************************************************
// LinkedList<T>::contains is used to determine if the list has a certain value*
// Parameter: T value.                                                         *
//******************************************************************************

template <class T>
bool LinkedList<T>::contains(const T value) {
    Node* p = head;

    while (p && p->value != value) {
        p = p->next;
        if (p->value == value)
            return 1;
        else
            return 0;
    }
}

//******************************************************************************
// LinkedList<T>::length is a function used to determine the number of nodes   *
// in the list.                                                                *
// Local numCount, number of nodes in the list.                                *
// Returns numCount.                                                           *
//******************************************************************************

template <class T>
size_t LinkedList<T>::length() const {
    Node* p = head;
    size_t numCount = 0; // counter for number of nodes
    while (p) {
        p = p->next;
        ++numCount;
    }
    return numCount;
}

//******************************************************************************
// LinkedList<T>::print_forwards prints the list in ascending order.           *
//******************************************************************************

template <class T>
void LinkedList<T>::print_forwards() const {
    Node* p = head;

    while (p) {
        cout << " " << p->value;
        p = p->next;
    }
    cout << endl;
}

//******************************************************************************
// LinkedList<T>::print_backwards prints the list in descending order.         *
//******************************************************************************

template <class T>
void LinkedList<T>::print_backwards() const {
    Node* p = tail;
    while (p) {
        cout<< " " << p->value;
        p = p->previous;
    }
    cout << endl;
}

//******************************************************************************
// LinkedList<T>::isEmpty checks to see if the list is empty.                  *
// Returns: Boolean value.                                                     *
//******************************************************************************

template <class T>
bool LinkedList<T>::isEmpty() {
    return (head == NULL);
}

//******************************************************************************
// LinkedList<T>::getLast is a recursive function that ascertains and returns  *
// the last value of the list.                                                 *
// Returns pointer initialized at head for the overloaded getLast function.     *                                             *
//******************************************************************************
template <class T>
T LinkedList<T>::getLast() {

    // ensures that the list is not empty
    assert(!isEmpty());

        // passes head as the argument value to start searching for the last
        // node
        return getLast(head);
}

//******************************************************************************
// LinkedList<T>::getLast(Node *p) is the overloaded getLast function used     *
// after assert determines that the list is not empty.                         *
// Parameter: pointer, p.                                                      *
// Returns, value of last node, or advances p to the next node recursively   *                    *
//******************************************************************************

template <class T>
T LinkedList<T>::getLast(Node *p) {

    // identifies that this is the last node
    if (p->next == NULL)
        return p->value;

    else
        // advances head down the list if not last node
        getLast(p->next);
}

#endif // LINKEDLISTV3_H_INCLUDED
