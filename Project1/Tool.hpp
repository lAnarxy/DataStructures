#pragma once
#include <iostream>
#include <string>
using namespace std;

class Tool {
    public:
        Tool(string name, char type);
        int age;
        string name;
        char type;
        int position;
};

ostream& operator<<(ostream& os, const Tool& t);