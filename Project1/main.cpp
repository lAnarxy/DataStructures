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

    LinkedList<int>* test_list = new LinkedList<int>();
    test_list->insert(3, 0);
    test_list->insert(1, 0);
    test_list->insert(2, 1);
    test_list->print();

    LinkedList<LinkedList<Plant*>*>* gardens = new LinkedList<LinkedList<Plant*>*>();
    LinkedList<Plant*>* garden1 = new LinkedList<Plant*>();
    Plant* test_plant = new Plant("Test Plant", 'F', 0);
    cout << test_plant << endl;
    garden1->insert(test_plant, 0);
    cout << garden1 << endl;
    gardens->insert(garden1, 0);
    gardens->print();

    // Creates a list of gardens, where each garden is a linked list of plants.d
    // LinkedList<LinkedList<Plant>>* gardens = new LinkedList<LinkedList<Plant>>();

    return 0;
}