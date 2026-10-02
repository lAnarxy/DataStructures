#pragma once
#include <iostream>
#include <string>
using namespace std;

class Ingredient {
    private:
        string name;
        int calories;
        Ingredient* additive;
    
    public:
        Ingredient(const string& n, int c) : name(n), calories(c), additive(nullptr) {}
        string getName() const { return name; }
        int getCalories() const { 
            int total = calories;
            if (additive) total += additive->getCalories();
            return total;
        }
        void setAdditive(Ingredient* a) { additive = a; }
        Ingredient* getAdditive() const { return additive; }

};

ostream& operator<<(ostream& os, const Ingredient& i) {
    string additives = "";
    if (i.getAdditive()) additives += i.getAdditive()->getName();
    os << "This ingredient is: " << i.getName() << ", it contains " << additives <<". it has a total of " << i.getCalories() << " calories.";
    return os;
}
ostream& operator<<(ostream& os, const Ingredient* i) {
    string additives = "";
    if (i->getAdditive()) additives += i->getAdditive()->getName();
    os << "This ingredient is: " << i->getName() << ", it contains " << additives <<". it has a total of " << i->getCalories() << " calories.";
    return os;
}