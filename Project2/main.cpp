#include <iostream>
#include <deque>
#include "Ingredient.hpp"
#include "Kitchen.hpp"
using namespace std;


// Idea - sandwich maker where ingredients can be added to the top and/or bottom using deque
// Sandwich could be flipped to change which side is being edited.
int main() {
    Kitchen* kitchen;
    Ingredient* currentItem = nullptr;

    // Setup the kitchen with user input
    cout << "  ------       Welcome to the Kitchen Simulator!       ------" << endl;
    cout << "For ease of use we recommend increasing the size of the terminal!\n\n" << endl;
    cout << "Lets create your first kitchen!" << endl;
    string name;
    cout << "Enter the name of your kitchen: " << endl;
    getline(cin, name);
    int size, pageSize;
     // Ignore the newline character left in the buffer after reading the name
    cout << "Enter the size of your kitchen 10-50 (24 is recommended): " << endl;
    cin >> size;
    // Clamps size to limit
    if (size < 10) { size = 10; }
    else if (size > 50) { size = 50; }
    cout << "Enter the page size for the inventory menu 4-16 (8 is recommended): " << endl;
    cin >> pageSize;
    // Clamps pageSize to limit
    if (pageSize < 4) { pageSize = 4; }
    else if (pageSize > 16) { pageSize = 16; }
    kitchen = new Kitchen(size, pageSize);
    kitchen->setName(name);

    Sandwich* sandwich = new Sandwich("Test Sandwich");
    sandwich->addIngredient(new Ingredient("Lettuce", 2));
    sandwich->addIngredient(new Ingredient("Tomato", 3));
    sandwich->addIngredient(new Ingredient("Bread", 5));
    sandwich->flip(); // Flip the sandwich to change which side is being edited.
    sandwich->addIngredient(new Ingredient("Bread", 5));
    cout << sandwich << endl;

    kitchen->addItem(sandwich);
    cout << kitchen->getItem(0)->getType() << endl;

    
    kitchen->inventoryMenu();
    // Clean up dynamically allocated memory
    delete kitchen;
    delete sandwich;
}

