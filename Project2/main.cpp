#include <iostream>
#include <deque>
#include "Ingredient.hpp"
using namespace std;

// Idea - sandwich maker where ingredients can be added to the top and/or bottom using deque
// Sanwich could be flipped to change which side is being edited.
int main() {
    // Sandwich will be represented as a deque of ingredients, allowing additions to both ends.
    deque<Ingredient*> sandwich;
    // Inventory will be able to hold up to 10 ingredients which can be used in any amount.
    Ingredient* inventory[10] = {nullptr};
}