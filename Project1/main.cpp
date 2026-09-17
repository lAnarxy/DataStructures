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

    // Linked list of gardens, each garden is a linked list of plants
    // LinkedList<LinkedList<Plant*>*>* gardens = new LinkedList<LinkedList<Plant*>*>();

    return 0;
}