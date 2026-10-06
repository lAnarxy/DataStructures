#include <iostream>
#include <deque>
#include "Ingredient.hpp"
#include "Kitchen.hpp"
using namespace std;
void inventoryMenu(Ingredient* inventory[16], char inventoryID[16]);

// Idea - sandwich maker where ingredients can be added to the top and/or bottom using deque
// Sandwich could be flipped to change which side is being edited.
int main() {
    Kitchen* kitchen = new Kitchen(24, 8);

    cout << "  ------       Welcome to the Kitchen Simulator!       ------" << endl;
    cout << "For ease of use we recommend increasing the size of the terminal!" << endl;
    Sandwich* sandwich = new Sandwich("Test Sandwich");
    sandwich->addIngredient(new Ingredient("Lettuce", 2));
    sandwich->addIngredient(new Ingredient("Tomato", 3));
    sandwich->addIngredient(new Ingredient("Bread", 5));
    cout << sandwich << endl;
    sandwich->flip(); // Flip the sandwich to change which side is being edited.
    sandwich->addIngredient(new Ingredient("Bread", 5));
    kitchen->addItem(sandwich);
    cout << sandwich << endl;
    
    kitchen->inventoryMenu();
    // Clean up dynamically allocated memory
    delete kitchen;
    delete sandwich;
}