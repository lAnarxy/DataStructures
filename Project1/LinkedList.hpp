#pragma once
#include <iostream>
using namespace std;

template <typename T> class LinkedList;
template <typename T> ostream& operator<<(ostream& os, const LinkedList<T>& l);
template <typename T> ostream& operator<<(ostream& os, const LinkedList<T>* l);

template <typename T>
class Node {
    public:
        T data;
        Node* previous;
        Node* next;
        
        Node(const T& value) : data(value), previous(nullptr), next(nullptr) {}
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
        void remove(int position = 0);
        size_t getSize() const { return size; }
        void print();
        void clear();
        Node<T>* getNode(int position = 0);

        friend ostream& operator<< <T>(ostream& os, const LinkedList<T>& l);
        friend ostream& operator<< <T>(ostream& os, const LinkedList<T>* l);
};

// Implementation for inserting a new node with the given 
// value at given position (default is before head)
template <typename T>
void LinkedList<T>::insert(T value, int position) {
    Node<T>* newNode = new Node<T>(value);
    
    if (position == 0 || head == nullptr) {
        newNode->next = head;
        if (head != nullptr) {
            head->previous = newNode;
        }
        head = newNode;
    } else {
        Node<T>* current = head;
        for (int i = 0; i < position - 1 && current->next != nullptr; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->previous = current;
        if (newNode->next != nullptr) {
            newNode->next->previous = newNode;
        }
        current->next = newNode;
    }
}

template <typename T>
void LinkedList<T>::remove(int position) {
    if (head == nullptr || position < 0 || position >= size) {
        return;
    }

    Node<T>* temp;
    if (position == 0) {
        temp = head;
        head = head->next;
        if (head != nullptr) {
            head->previous = nullptr;
        }
    } else {
        Node<T>* current = head;
        for (int i = 0; i < position - 1; i++) {
            if (current->next == nullptr) {
                return;
            }
            current = current->next;
        }
        temp = current->next;
        if (temp->next != nullptr){
            temp->next->previous = current;
        }
        current->next = temp->next;
    }
    delete temp;
    size--;
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

// Clears the linked list and frees memory
template <typename T>
void LinkedList<T>::clear() {
    while (head != nullptr) {
        Node<T>* next = head->next;
        delete head;
        head = next;
    }
    size = 0;
}

template <typename T>
Node<T>* LinkedList<T>::getNode(int position = 0) {
    if (position < 0 || position >= size) {
        return nullptr;
    }
    Node<T>* current = head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    return current;
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

template <typename T>
ostream& operator<<(ostream& os, const LinkedList<T>* l) {
    if (l->head == nullptr) {
        os << "The list is empty." << endl;
        return os;
    }

    int index = 0;
    Node<T>* current = l->head;
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