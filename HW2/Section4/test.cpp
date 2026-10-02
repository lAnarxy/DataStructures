#include <iostream>

// Edit of linked list I made that was used in project 1.
// Added setHead(); to help reassign the newly ordered list for printing purposes.
#include "LinkedList.hpp"

template <typename T>
int count(Node<T>* head);

int main() {
    LinkedList<int>* list = new LinkedList<int>;
    list->insert_back(1);
    list->insert_back(2);
    list->insert_back(3);
    list->insert_back(4);
    list->insert_back(5);
    list->insert_back(6);
    cout << count(list->getNode()) << endl;
}

// Reverses a linked list given the first node.
template <typename T>
int count(Node<T>* head) {
    // Returns the last node of the list
    if (head == nullptr) {
        return 0;
    }

    int num_Nodes = count(head->next) + 1;
    
    return num_Nodes;
}