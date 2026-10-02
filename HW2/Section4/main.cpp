#include <iostream>

// Edit of linked list I made that was used in project 1.
// Added setHead(); to help reassign the newly ordered list for printing purposes.
#include "LinkedList.hpp"

template <typename T>
Node<T>* reverseList(Node<T>* head);

int main() {
    LinkedList<int>* list = new LinkedList<int>;
    list->insert_back(1);
    list->insert_back(2);
    list->insert_back(3);
    list->insert_back(4);
    list->insert_back(5);
    list->insert_back(6);
    cout << "Original list:\n" << list << endl;
    Node<int>* reversedList = reverseList(list->getNode());
    list->setHead(reversedList);
    cout << "Reversed list:\n" << list << endl;
}

// Reverses a linked list given the first node.
template <typename T>
Node<T>* reverseList(Node<T>* head) {
    // Returns the last node of the list
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    // Recurses until it reaches the final node
    Node<T>* newHead = reverseList(head->next);

    // Each node reverses the one in front of it
    head->next->next = head;
    // Sets its own next to null (sets old first node as tail)
    head->next = nullptr;

    // Returns the old last node as the new head
    return newHead;
}