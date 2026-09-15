#include <iostream>
using namespace std;

int main() {
    int len = 5;
    int *nums = new int[len];
    for (int i = 0; i < len; i++) {
        nums[i] = i*i;
        cout << "Element " << i << ": " << nums[i] << endl;
    }
    delete[] nums;
    nums = nullptr;
    return 0;
}