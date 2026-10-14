#pragma once
#include <iostream>
#include "Ingredient.hpp"

class Kitchen {
    private:
        string name = "Kitchen"; // Name of kitchen
        Ingredient** inventory; // Array of Ingredient pointers
        int size; // Size limit of kitchen
        int pageSize; // Page size of kitchen
    public:
        // Inventory will be able to hold (up to 24 by default) previously made 
        // ingredients, dishes, or sandwiches which can be used when cooking.
        Kitchen(int size = 24, int pageSize = 8) {
            this->size = size;
            this->pageSize = pageSize;
            inventory = new Ingredient*[size];
            for (int i = 0; i < size; ++i) {
                inventory[i] = nullptr;
            }
        }
        ~Kitchen() {
            for (int i = 0; i < size; ++i) {
                delete inventory[i];
            }
            delete[] inventory;
        }

        // Prepares an ingredient and returns it
        Ingredient* prepareIngredient(Ingredient* item);
        // Prepares a sandwich and returns it
        Ingredient* prepareSandwich(Sandwich* item);
        // Prepares a dish and returns it
        Ingredient* prepareDish(Dish* item);
        // Returns name of the kitchen
        string getName() const { return name; }
        // Sets name of the kitchen
        void setName(const string& newName) { name = newName; }
        // Adds an item to the first available inventory slot
        bool addItem(Ingredient* item);
        // Gets an item from inventory at specific index
        Ingredient* getItem(int index);
        // Enters kitchen's inventory menu
        Ingredient* inventoryMenu(bool taking = false);
        // Enters kitchen's main menu
        void mainMenu();
};