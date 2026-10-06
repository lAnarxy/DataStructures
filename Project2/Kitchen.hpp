#pragma once
#include <iostream>
#include "Ingredient.hpp"

class Kitchen {
    private:
        // Inventory will be able to hold up to 16 previously made 
        // ingredients, dishes, or sandwiches which can be used in any amount.
        Ingredient** inventory;
        char* inventoryID; // Tracks what object each element is
        int size;
        int pageSize;
    public:
        Kitchen(int size = 24, int pageSize = 8) {
            this->size = size;
            this->pageSize = pageSize;
            inventory = new Ingredient*[size];
            inventoryID = new char[size];
            for (int i = 0; i < size; ++i) {
                inventory[i] = nullptr;
                inventoryID[i] = '\0';
            }
        }
        ~Kitchen() {
            for (int i = 0; i < size; ++i) {
                delete inventory[i];
            }
            delete[] inventory;
            delete[] inventoryID;
        }

        void addItem(Ingredient* item);
        void pickItem();
        void inventoryMenu();
};