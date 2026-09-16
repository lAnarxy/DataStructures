#include "LinkedList.hpp"

template <class T>
Node<T>::Node() {
    next = nullptr;
}

template <class T>
Node<T>::Node(T value) {
    data = value;
    next = nullptr;
}

template <class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
}

// Implementation for inserting a new node with the given value at given position (default is before head)
template <class T>
void LinkedList<T>::insert(T value, int position = 0) {
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

// Implementation for printing the linked list
template <class T>
void LinkedList<T>::print() {
    if (head == nullptr) {
        cout < "The list is empty." << endl;
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