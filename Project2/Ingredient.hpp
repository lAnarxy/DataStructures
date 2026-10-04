#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;

class Ingredient {
    private:
        string name;
        int calories;
        list<Ingredient*>* additives;
    
    public:
        Ingredient(const string& n, int c) : name(n), calories(c), additives(new list<Ingredient*>) {}
        ~Ingredient() { delete additives; }
        string getName() const { return name; }
        int getCalories() const { 
            int total = calories;
            for (auto& a : *additives) total += a->getCalories();
            return total;
        }
        void setAdditive(Ingredient* a) { additives->push_back(a); }
        list<Ingredient*>* getAdditives() const { return additives; }

};

ostream& operator<<(ostream& os, const Ingredient& i) {
    string additives = "";
    for (auto& a : *i.getAdditives()) additives += a->getName();
    os << "This ingredient is: " << i.getName() << ", it contains " << additives <<". it has a total of " << i.getCalories() << " calories.";
    return os;
}
ostream& operator<<(ostream& os, const Ingredient* i) {
    string additives = "";
    for (auto& a : *i->getAdditives()) additives += a->getName();
    os << "This ingredient is: " << i->getName() << ", it contains " << additives <<". it has a total of " << i->getCalories() << " calories.";
    return os;
}