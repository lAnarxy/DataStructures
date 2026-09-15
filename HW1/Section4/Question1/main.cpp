#include <iostream>
#include "Rectangle.hpp"
#include "Square.hpp"
using namespace std;

int main() {
    Rectangle defaultRect;
    Rectangle specificRect(12, 5);

    cout << "\nRectangles -------" << endl;
    cout << "Default Area: " << defaultRect.getArea() << ". Default Perimeter: " << defaultRect.getPerimeter() << '.' << endl;
    cout << "Specific Area: " << specificRect.getArea() << ". Specific Perimeter: " << specificRect.getPerimeter() << '.' << endl;

    defaultRect.setValues(10,3);
    cout << "Updated Area: " << defaultRect.getArea() << ". Updated Perimeter: " << defaultRect.getPerimeter() << '.' << endl;

    Square defaultSq;
    Square specificSq(5);

    cout << "\nSquares -------" << endl;
    cout << "Default Area: " << defaultSq.getArea() << ". Default Perimeter: " << defaultSq.getPerimeter() << '.' << endl;
    cout << "Specific Area: " << specificSq.getArea() << ". Specific Perimeter: " << specificSq.getPerimeter() << '.' << endl;

    defaultSq.setValues(3);
    cout << "Updated Area: " << defaultSq.getArea() << ". Updated Perimeter: " << defaultSq.getPerimeter() << ".\n" << endl;

    return 0;
}