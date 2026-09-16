#include <iostream>
using namespace std;

int main() {
    cout << "Welcome to the Digital Garden!" << endl;
    int numGardens;
    cout << "How many gardens would you like to make? (1-6, 3 recommended)" << endl;
    while (!(numGardens > 0 && numGardens < 7) || !(cin >> numGardens)) {
        cout << "Invalid Input. Please enter a number between 1 and 6 (3 recommended)" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Preparing " << numGardens << " gardens..." << endl;
    return 0;
}