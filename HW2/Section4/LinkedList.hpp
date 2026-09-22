#pragma once
#include <iostream>
using namespace std;

template <typename T> class LinkedList;
template <typename T> ostream& operator<<(ostream& os, const LinkedList<T>& l);
template <typename T> ostream& operator<<(ostream& os, const LinkedList<T>* l);

// Nodes used for LinkedList
template <typename T>
class Node {
    public:
        T data;
        Node* next;
        
        Node(const T& value) : data(value), next(nullptr) {}
};

// Class for LinkedList that tracks both the head and tail.
template <typename T>
class LinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
        size_t size;
    public:
        LinkedList() : head(nullptr), tail(nullptr), size(0) {}

        ~LinkedList() {
            clear();
        }

        void insert_at_index(T value, int position = 0);
        void insert_front(T value);
        void insert_back(T value);
        void remove(int position = 0);
        size_t getSize() const { return size; }
        void print();
        void clear();
        Node<T>* getNode(int position = 0);
        void setHead(Node<T>* newHead);

        friend ostream& operator<< <T>(ostream& os, const LinkedList<T>& l);
        friend ostream& operator<< <T>(ostream& os, const LinkedList<T>* l);
};

// Implementation for inserting a new node with the given 
// value at given position (default is before head)
template <typename T>
void LinkedList<T>::insert_at_index(T value, int position) {
    Node<T>* newNode = new Node<T>(value);
    
    if (head == nullptr || position == 0) {
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) {
            tail = newNode;
        }
    } else if (position == size) {
        tail->next = newNode;
        tail = newNode;
    } else {
        Node<T>* current = head;
        for (int i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        
        if (newNode->next == nullptr) {
            tail = newNode;
        }
    }
    size++;
    return;
}

// Function to explicitly insert to front.
template <typename T>
void LinkedList<T>::insert_front(T value) {
    insert_at_index(value);
    return;
}

// Function to explicitly insert to back
template <typename T>
void LinkedList<T>::insert_back(T value) {
    insert_at_index(value, size);
    return;
}

// Removes node at a certain index
template <typename T>
void LinkedList<T>::remove(int position) {
    if (head == nullptr || position < 0 || position >= size) {
        return;
    }

    Node<T>* temp;
    if (head == tail){
        temp = head;
        head = nullptr;
        tail = nullptr;
    } else if (position == 0) {
        temp = head;
        tail->next = temp->next;
        head = temp->next;
    } else {
        Node<T>* current = head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
        if (current->next == head) {
            tail = current;
        }
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
    while (index < size) {
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

// Gets the node at a certain position, head node by default.
template <typename T>
Node<T>* LinkedList<T>::getNode(int position) {
    if (position < 0 || position >= size) {
        return nullptr;
    }
    Node<T>* current = head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    return current;
}

// Reassigns a new head value to the list
template <typename T>
void LinkedList<T>::setHead(Node<T>* newHead) {
    if (newHead != nullptr){
        size++;
        Node<T>* curr = newHead;
        while (curr->next != nullptr && size < 10) {
            size++;
            curr = curr->next;
        }
        head = newHead;
        tail = curr;
    }
}

// Adds functionality for cout<<
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