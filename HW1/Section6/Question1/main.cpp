#include <iostream>
#include <cstring>
using namespace std;

float divide(float num, float divisor);

int main() {
    int nums[] = {8, 6, 12};
    int divisors[] = {2, 0, 6};
    for (int i = 0; i < 3; i++) {
        try {
            float result = divide(nums[i], divisors[i]);
            cout << nums[i] << " / " << divisors[i] << " = " << result << endl;
        }
        catch (int e) {
            cout << "Error Number: " << e << endl;
            cout << "Error Type: Division by Zero" << endl;
        }
    }
}

float divide(float num, float divisor) {
    if (divisor == 0) {
        throw (1);
    } else {
        return num / divisor;
    }
}