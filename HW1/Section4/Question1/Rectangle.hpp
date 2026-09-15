#pragma once

class Rectangle {
    private:
        int length;
        int width;
    public:
        void setValues(int newLength, int newWidth);
        int getArea();
        int getPerimeter();
        Rectangle();
        Rectangle(int len, int wid);
};