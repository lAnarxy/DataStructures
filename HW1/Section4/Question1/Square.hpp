#pragma once
#include "Rectangle.hpp"

class Square: public Rectangle{
    private:
        using Rectangle::setValues;
    public:
        void setValues(int newLength);
        Square();
        Square(int len);
};