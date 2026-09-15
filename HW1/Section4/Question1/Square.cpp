#include "Square.hpp"

Square::Square() {
    setValues(2);
}

Square::Square(int len) {
    setValues(len);
}

void Square::setValues(int newLength) {
    setValues(newLength, newLength);
}