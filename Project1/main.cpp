#include <iostream>
#include "LinkedList.hpp"
#include "Plant.hpp"
// #include "Tool.hpp"
using namespace std;

int main() {
    cout << "Welcome to the Digital Garden!" << endl;
    int numGardens;
    cout << "How many gardens would you like to make? (1-6, 3 recommended)" << endl;
    cin >> numGardens;
    while (!(numGardens > 0 && numGardens < 7) || cin.fail()) {
        cout << "Invalid Input. Please enter a number between 1 and 6 (3 recommended)" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> numGardens;
    }
    cout << "Preparing " << numGardens << " gardens..." << endl;

    LinkedList<int>* test = new LinkedList<int>();
    test->print();
    test->insert(5);
    test->insert(4);
    test->insert(2);
    test->insert(3, 1);
    test->insert(1);
    test->insert(6, 5);
    test->print();
    test->remove(5);
    test->print();
    cout<< test->size << endl;
    
    Node<int>* check = test->getNode(4);
    if (check->next == nullptr) {cout<<"Fail"<<endl;}
    // Linked list of gardens, each garden is a linked list of plants
    // LinkedList<LinkedList<Plant*>*>* gardens = new LinkedList<LinkedList<Plant*>*>();

    return 0;
}