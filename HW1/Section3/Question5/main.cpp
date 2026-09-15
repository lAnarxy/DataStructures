#include <iostream>
using namespace std;

void swapInts(int &num1, int &num2);

int main() {
    int num1 = 3;
    int num2 = 8;
    swapInts(num1, num2);
    cout << "After swap: " << num1 << ", " << num2 << endl;
    return 0;
}

void swapInts(int &num1, int &num2) {
    cout << "Before swap: " << num1 << ", " << num2 << endl;
    int temp = num1;
    num1 = num2;
    num2 = temp;
    return;
}