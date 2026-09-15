#include <iostream>
using namespace std;

void add(const int a, int b);

int main() {
    int var1 = 5;
    const int var2 = 10;

    add(var1, var2);
    var1 += 2;
    add(var2, var1);
}

void add(const int a, int b) {
    cout << "var1 = " << a << endl;
    cout << "var2 = " << b << endl;
    b += a;
    cout << "var1 + var2 = " << b << endl;
}