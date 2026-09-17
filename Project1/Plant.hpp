#pragma once
#include <iostream>
#include <string>
using namespace std;

class Plant {
    public:
        Plant(string name, string type, int plant_date);
        int plant_date;
        int age;
        string name;
        string type;
        int position;
        int water;
        int maintenance;
        void updateAge(int time);
};

ostream& operator<<(ostream& os, const Plant& p);
ostream& operator<<(ostream& os, const Plant* p);