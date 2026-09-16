#pragma once
#include <iostream>
using namespace std;

template <typename T> class LinkedList;
template <typename T> ostream& operator<<(ostream& os, const LinkedList<T>& l);

template <typename T>
class Node {
    public:
        T data;
        Node* next;
        
        Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
    private:
        Node<T>* head;
        size_t size;
    public:
        LinkedList() : head(nullptr), size(0) {}

        ~LinkedList() {
            clear();
        }

        void insert(T value, int position = 0);
        void print();
        void clear();

        friend ostream& operator<< <T>(ostream& os, const LinkedList<T>& l);
};

// Implementation for inserting a new node with the given 
// value at given position (default is before head)
template <typename T>
void LinkedList<T>::insert(T value, int position) {
    Node<T>* newNode = new Node<T>(value);
    
    if (position == 0 || head == nullptr) {
        newNode->next = head;
        head = newNode;
    } else {
        Node<T>* current = head;
        for (int i = 0; i < position - 1 && current->next != nullptr; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

template <typename T>
void LinkedList<T>::clear() {
    while (head != nullptr) {
        Node<T>* next = head->next;
        delete head;
        head = next;
    }
    size = 0;
}

// Implementation for printing the linked list
template <typename T>
void LinkedList<T>::print() {
    if (head == nullptr) {
        cout << "The list is empty." << endl;
        return;
    }

    int index = 0;
    Node<T>* current = head;
    while (current != nullptr) {
        try {
            cout << "Index " << index << ": " << current->data << endl;
            current = current->next;
            index++;
        } catch (const exception& e) {
            cout << "Error printing node at index " << index << ": " << e.what() << endl;
            return;
        }
    }
}

template <typename T>
ostream& operator<<(ostream& os, const LinkedList<T>& l) {
    if (l.head == nullptr) {
        os << "The list is empty." << endl;
        return os;
    }

    int index = 0;
    Node<T>* current = l.head;
    while (current != nullptr) {
        try {
            os << "Index " << index << ": " << current->data << endl;
            current = current->next;
            index++;
        } catch (const exception& e) {
            os << "Error printing node at index " << index << ": " << e.what() << endl;
            return os;
        }
    } 
    return os;
}