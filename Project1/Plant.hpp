#pragma once
#include <iostream>
#include <string>
using namespace std;

class Plant {
    public:
        Plant(string name, char type, int plant_date);
        int age;
        string name;
        char type;
        int position;
        int water;
        int maintenance;
};

ostream& operator<<(ostream& os, const Plant& p);
ostream& operator<<(ostream& os, const Plant* p);