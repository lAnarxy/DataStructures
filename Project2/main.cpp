#include <iostream>
#include <deque>
#include "Ingredient.hpp"
using namespace std;

// Idea - sandwich maker where ingredients can be added to the top and/or bottom using deque
// Sandwich could be flipped to change which side is being edited.
int main() {
    // Inventory will be able to hold up to 16 previously made ingredients, dishes, or sandwiches which can be used in any amount.
    Ingredient* inventory[16] = {nullptr};
    Sandwich* sandwich = new Sandwich("Test Sandwich");
    sandwich->addIngredient(new Ingredient("Lettuce", 2));
    sandwich->addIngredient(new Ingredient("Tomato", 3));
    sandwich->addIngredient(new Ingredient("Bread", 5));
    cout << sandwich << endl;
    sandwich->flip(); // Flip the sandwich to change which side is being edited.
    sandwich->addIngredient(new Ingredient("Bread", 5));
    inventory[0] = sandwich;
    cout << *inventory[0] << endl;
    inventory[0]->print();
    
    // Clean up dynamically allocated memory
    for (int i = 0; i < 16; ++i) {
        delete inventory[i];
    }
}