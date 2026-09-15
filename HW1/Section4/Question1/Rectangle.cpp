#include "Rectangle.hpp"

Rectangle::Rectangle() {
    length = 2;
    width = 4;
}

Rectangle::Rectangle(int len, int wid) {
    length = len;
    width = wid;
}

void Rectangle::setValues(int newLength, int newWidth) {
    length = newLength;
    width = newWidth;
}

int Rectangle::getArea() {
    return length * width;
}

int Rectangle::getPerimeter() {
    return 2 * (length + width);
}