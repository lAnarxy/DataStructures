#pragma once
#include <iostream>
#include <string>
using namespace std;

class Plant {
    public:
        Plant(string name, char type);
        int age;
        string name;
        char type;
        int position;
};