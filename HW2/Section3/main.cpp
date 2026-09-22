#include <iostream>
#include <string>
using namespace std;

// Pair class, hold any 2 values
template <typename T, typename U>
class Pair {
    private:
    T left;
    U right;

    public:
    Pair(T leftVal, U rightVal) { this->left = leftVal; this->right = rightVal; }
    void print() {
        cout << "<" << left << ", " << right << ">" << endl;
    }
    void setLeft(T val) { left = val; }
    void setRight(U val) { right = val; }
    T getLeft() const { return left; }
    U getRight() const { return right; }

};
// cout << functionality
template <typename T, typename U> ostream& operator<<(ostream& os, const Pair<T, U>* p) {
    os << "<" << p->getLeft() << ", " << p->getRight() << ">";
    return os;
}

// Creates and prints 5 different pairs of values.
int main() {
    Pair<int, float>* pair1 = new Pair<int, float>(1, 2.33);
    Pair<double, string>* pair2 = new Pair<double, string>(3.45, "Paired");
    Pair<bool, long>* pair3 = new Pair<bool, long>(true, 10000);
    Pair<Pair<double, string>*, float>* intermediate = new Pair<Pair<double, string>*, float>(pair2, 10.55);
    Pair<char, Pair<Pair<double, string>*, float>*>* pair4 = new Pair<char, Pair<Pair<double, string>*, float>*>('A', intermediate);
    Pair<string, float>* pair5 = new Pair<string, float>("Apple", 2.99);
    pair1->print();
    pair2->print();
    pair3->print();
    pair4->print();
    pair5->print();
}
