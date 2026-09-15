#include <iostream>
using namespace std;

int main() {
    int input;
    cout << "Enter and integer: ";
    cin >> input;

    if (input > 0) cout << "Your number is positive!";
    else if (input < 0) cout << "Your number is negative!";
    else cout << "Your number is 0!";
    cout << endl;
    return 0;
}