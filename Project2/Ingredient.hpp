#pragma once
#include <iostream>
#include <list>
#include <deque>
#include <string>
using namespace std;

// Prototypes for stream overloads
class Ingredient;
class Dish;
class Sandwich;

// Stream overload prototypes for printing Ingredient, Dish, and Sandwich objects.
ostream& operator<<(ostream& os, const Ingredient& i);
ostream& operator<<(ostream& os, const Ingredient* i);  
ostream& operator<<(ostream& os, const Dish& d);
ostream& operator<<(ostream& os, const Dish* d);
ostream& operator<<(ostream& os, const Sandwich& s);
ostream& operator<<(ostream& os, const Sandwich* s);


// The Ingredient class is the base block of other classes, and cannot contain other ingredients itself.
class Ingredient {
    private:
        string name;
        list<string> preparations; // How the ingredient is prepared. i.e., chopped, diced, boiled, etc.
    
    protected:
        int calories;
    
    public:
        Ingredient(const string& n, int c) : name(n), calories(c), preparations() {}
        // Returns name of the ingredient
        string getName() const { return name; }
        // Returns calories for the ingredient
        int getCalories() const { return calories; }
        // Returns the list of preparations for the ingredient
        list<string>& getPreparations() { return preparations; }
        // Adds a preparation method to the ingredient
        void addPreparation(const string& prep) { preparations.push_back(prep); }
        // Print function used for polymorphic << overload compatibility
        virtual void print(ostream& os) const {
            os << "This ingredient is: " << getName() << ". it has " << getCalories() << " calories.";
        }
        virtual ~Ingredient() {}
};

// The Dish class inherits from Ingredient and represents a collection of ingredients.  
class Dish : public Ingredient {
    private:
        list<Ingredient*> ingredients; // The list of ingredients in the dish.
    public:
        Dish(const string& n) : Ingredient(n, 0), ingredients() {}
        // Adds ingredient and its calories to dish
        void addIngredient(Ingredient* i) { 
            ingredients.push_back(i);
            calories += i->getCalories();
        }
        // Returns the list of ingredients in the dish
        list<Ingredient*>& getIngredients() { return ingredients; }
        // Print function used for polymorphic << overload compatibility
        void print(ostream& os) const {
            os << "This dish is: " << getName() << ". it has a total of " << getCalories() << " calories.\nIt contains the following: ";
            for (const Ingredient* ingredient : ingredients) {
                os << "\n  - " << ingredient;
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
        // Adds ingredient and its calories to the 'top' of sandwich. Top side depends on flipped state.
        void addIngredient(Ingredient* i) { 
            if (flipped) {
                ingredients.push_back(i); // Add to the back if flipped
            } else {
                ingredients.push_front(i); // Add to the front if not flipped
            }
            calories += i->getCalories();
        }
        // Flips the sandwich, changing which side is considered the 'top'
        void flip() { flipped = !flipped; }
        // Returns whether the sandwich is flipped or not
        bool isFlipped() const { return flipped; }
        // Returns the deque of ingredients in the sandwich
        const deque<Ingredient*>& getIngredients() const { return ingredients; }
        // Print function used for polymorphic << overload compatibility
        void print(ostream& os) const {
            os << "This sandwich is: " << getName() << ". it has a total of " << getCalories() << " calories.\nIt contains the following: ";
            if (flipped) {
                // Print ingredients in reverse order if the sandwich is flipped
                for (auto it = ingredients.rbegin(); it != ingredients.rend(); ++it) {
                    os << "\n  - " << *it;
                }
            } else {
                // Print ingredients in normal order if the sandwich is not flipped
                for (const Ingredient* ingredient : ingredients) {
                    os << "\n  - " << ingredient;
                }
            }
        }
};


// Ingredient Printing
inline ostream& operator<<(ostream& os, const Ingredient& i) {
    i.print(os);
    return os;
}
inline ostream& operator<<(ostream& os, const Ingredient* i) {
    i->print(os);
    return os;
}

// Dish Printing
inline ostream& operator<<(ostream& os, const Dish& d) {
    d.print(os);
    return os;
}
inline ostream& operator<<(ostream& os, const Dish* d) {
    d->print(os);
    return os;
}

// Sandwich Printing
inline ostream& operator<<(ostream& os, const Sandwich& s) {
    s.print(os);
    return os;
}
inline ostream& operator<<(ostream& os, const Sandwich* s) {
    s->print(os);
    return os;
}