#pragma once
#include <iostream>
#include "Ingredient.hpp"

class Kitchen {
    private:
        // Inventory will be able to hold (up to 24 by default) previously made 
        // ingredients, dishes, or sandwiches which can be used cooking.
        string name = "Kitchen";
        Ingredient** inventory;
        int size;
        int pageSize;
    public:
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

        Ingredient* prepareIngredient(Ingredient* item);
        Ingredient* prepareSandwich(Sandwich* item);
        Ingredient* prepareDish(Dish* item);
        string getName() const { return name; }
        void setName(const string& newName) { name = newName; }
        bool addItem(Ingredient* item);
        Ingredient* getItem(int index);
        Ingredient* inventoryMenu(bool taking = false);
        void mainMenu();
};