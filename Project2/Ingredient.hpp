#pragma once
#include <iostream>
#include <list>
#include <deque>
#include <string>
using namespace std;

// The Ingredient class is the base block of other classes, and cannot contain other ingredients itself.
class Ingredient {
    private:
        string name;
        list<string> preparations; // How the ingredient is prepared. i.e., chopped, diced, boiled, etc.
    
    protected:
        int calories;
    
    public:
        Ingredient(const string& n, int c) : name(n), calories(c), preparations() {}
        string getName() const { return name; }
        int getCalories() const { return calories; }
        list<string>& getPreparations() { return preparations; }
        void addPreparation(const string& prep) { preparations.push_back(prep); }
        virtual void print() {
            cout << "This ingredient is: " << getName() << ". it has " << getCalories() << " calories.";
        }
        virtual ~Ingredient() {}
};

// The Dish class inherits from Ingredient and represents a collection of ingredients.  
class Dish : public Ingredient {
    private:
        list<Ingredient*> ingredients; // The list of ingredients in the dish.
    public:
        Dish(const string& n) : Ingredient(n, 0), ingredients() {}
        void addIngredient(Ingredient* i) { 
            ingredients.push_back(i);
            calories += i->getCalories();
        }
        list<Ingredient*>& getIngredients() { return ingredients; }
        void print() {
            cout << "This dish is: " << getName() << ". it has a total of " << getCalories() << " calories.\nIt contains the following: ";
            for (const Ingredient* ingredient : ingredients) {
                cout << "\n  - " << ingredient;
            }
        }
};

// The Sandwich class is similar to the Dish class, but it is represented as a deque of ingredients, allowing additions to both ends.
class Sandwich : public Ingredient {
private:
        deque<Ingredient*> ingredients; // The deque of ingredients in the sandwich.
        bool flipped = false; // Whether the sandwich is flipped or not.
    public:
        Sandwich(const string& n) : Ingredient(n, 0), ingredients() {}
        void addIngredient(Ingredient* i) { 
            if (flipped) {
                ingredients.push_back(i);
            } else {
                ingredients.push_front(i);
            }
            calories += i->getCalories();
        }
        void flip() { flipped = !flipped; }
        bool isFlipped() const { return flipped; }
        const deque<Ingredient*>& getIngredients() const { return ingredients; }
        void print() {
            cout << "This sandwich is: " << getName() << ". it has a total of " << getCalories() << " calories.\nIt contains the following: ";
            if (flipped) {
                for (auto it = ingredients.rbegin(); it != ingredients.rend(); ++it) {
                    cout << "\n  - " << *it;
                }
            } else {
                for (const Ingredient* ingredient : ingredients) {
                    cout << "\n  - " << ingredient;
                }
            }
        }
};


// Ingredient Printing
ostream& operator<<(ostream& os, const Ingredient& i) {
    os << "This ingredient is: " << i.getName() << ". it has " << i.getCalories() << " calories.";
    return os;
}
ostream& operator<<(ostream& os, const Ingredient* i) {
    os << "This ingredient is: " << i->getName() << ". it has " << i->getCalories() << " calories.";
    return os;
}

// Dish Printing
ostream& operator<<(ostream& os, const Dish& d) {
    os << "This dish is: " << d.getName() << ". it has a total of " << d.getCalories() << " calories.";
    return os;
}
ostream& operator<<(ostream& os, const Dish* d) {
    os << "This dish is: " << d->getName() << ". it has a total of " << d->getCalories() << " calories.";
    return os;
}

// Sandwich Printing
ostream& operator<<(ostream& os, const Sandwich& s) {
    os << "This sandwich is: " << s.getName() << ". it has a total of " << s.getCalories() << " calories.\nIt contains the following: ";
    if (s.isFlipped()) {
        for (auto it = s.getIngredients().rbegin(); it != s.getIngredients().rend(); ++it) {
            os << "\n  - " << *it;
        }
    } else {
        for (const Ingredient* ingredient : s.getIngredients()) {
            os << "\n  - " << ingredient;
        }
    }
    return os;
}
ostream& operator<<(ostream& os, const Sandwich* s) {
    os << "This sandwich is: " << s->getName() << ". it has a total of " << s->getCalories() << " calories.\nIt contains the following: ";
    if (s->isFlipped()) {
        for (auto it = s->getIngredients().rbegin(); it != s->getIngredients().rend(); ++it) {
            os << "\n  - " << *it;
        }
    } else {
        for (const Ingredient* ingredient : s->getIngredients()) {
            os << "\n  - " << ingredient;
        }
    }
    return os;
}