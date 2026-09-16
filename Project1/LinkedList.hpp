#pragma once
#include <iostream>

template <class T>
class Node {
    public:
        Node();
        Node(T value);
        T data;
        Node* next;
};

template <class T>
class LinkedList {
    Node<T>* head;
    public:
        LinkedList();
        void insert(T value, int position = 0);
        void print();
};