#include "Kitchen.hpp"
#include <sstream>

Ingredient* Kitchen::prepareIngredient(Ingredient* item) {
    string preparation; // Each perparation is a single word
    
    // Gets preparations until user completes item by entering 'x'
    while (preparation != "x") {
        cout << "\nPreparing ingredient: " << item << endl;
        cout << "How would you like to prepare it? (Chopped, Diced, Boiled, etc.) Type 'x' to finsih prep." << endl;
        cin >> preparation;
        if (preparation != "x") {
            item->addPreparation(preparation);
        }
    }
    // Returns final ingredient
    return item;
}

Ingredient* Kitchen::prepareSandwich(Sandwich* item) {
    char input; // Stores action input
    string message = ""; // Stores message from previous action

    // Continues until user finishes preparation by entering 'x'
    while (input != 'x') {
        cout << "  ------     Sandwich Station     ------" << endl;
        cout << "  --------------------------------------" << endl;
        cout << "  Preparing sandwich: " << item << endl;
        cout << "\n  What do you want to do to the sandwich?" << endl;
        cout << "  (a) Add Ingredient  (r) Remove Ingredient" << endl;
        cout << "  (f) Flip Sandwich  (x) Finish Sandwich" << endl;
        cout << message << endl;

        cin >> input;
        
        // Entering 'a' adds ingredient
        if (input == 'a') {
            // Gets item from inventory with taking mode as true to prevent cloning.
            Ingredient* addition = inventoryMenu(true);
            // If item exists add it to the top of Sandwich
            if (!addition) {
                message = "No valid item was chosen.";
            } else {
                item->addIngredient(addition);
                message = addition->getName() + " was added to the top of the " + item->getName();
            }

        // Entering 'r' removes the top ingredient.
        } else if (input == 'r') {
            // Removes and stores top ingredient.
            Ingredient* removed = item->removeIngredient();
            // If successfully removed continue the process.
            if (removed) {
                cout << "\n\nRemoved the following item:" << endl;
                cout << removed << endl;
                cout << "Would you like to keep this item or delete it?" << endl;
                char choice = '\0';

                // Item can either be kept or deleted.
                while (choice != 'k' && choice != 'd') {
                    cout << "  (k) Keep  (d) Delete" << endl;
                    cin >> choice;
                }

                // Deletes item immediately if chosen.
                if (choice == 'd') {
                    cout << removed->getName() + " deleted." << endl;
                    delete removed;
                } else {
                    // Try to add item to inventory
                    while (!addItem(removed)) {
                        cout << "No room in inventory." << endl;
                        cout << "Review inventory and try again?" << endl;
                        cout << "  (r) Review Inventory  (d) Delete Item" << endl;
                        cin >> choice;

                        // If addition fails, continue until an inventory slot has been freed up
                        // or until the user agrees to delete the item instead
                        if (choice == 'r') {
                            inventoryMenu();
                        } else if (choice == 'd') {
                            cout << "Deleted " + removed->getName();
                            delete removed;
                            break;
                        }
                    }
                }

            // If nothing is removed either because the sandwich was empty, or deletion was cancelled.
            } else {
                message = "Nothing to remove.";
            }

        // Flips sandwich, reversing the order the ingredients are viewed.
        } else if (input == 'f') {
            item->flip();
        
        // No message if invalid input.
        } else {
            message = "";
        }

    }

    // Final preparations for the sandwich (same as ingredients)
    string preparation;
    while (preparation != "x") {
        cout << "  ------     Sandwich Station     ------" << endl;
        cout << "  --------------------------------------" << endl;
        cout << "\n  Preparing sandwich: " << item << endl;
        cout << "  How would you like to prepare it? (Sliced, Toasted, etc.) Type 'x' to finsih prep." << endl;
        cin >> preparation;
        if (preparation != "x") {
            item->addPreparation(preparation);
        }
    }
    return item;
}

Ingredient* Kitchen::prepareDish(Dish* item) {
    char input; // Stores action input
    string message = ""; // Stores message from previous action.

    // Continues until user finishes preparation by entering 'x'
    while (input != 'x') {
        cout << "  ------       Dish Station       ------" << endl;
        cout << "  --------------------------------------" << endl;
        cout << "  Preparing dish: " << item << endl;
        cout << "\n  What do you want to do to the dish?" << endl;
        cout << "  (a) Add Ingredient  (r) Remove Ingredient" << endl;
        cout << "  (x) Finish Dish" << endl;
        cout << message << endl;

        cin >> input;

        // Entering 'a' adds ingredient
        if (input == 'a') {
            // Gets item from inventory with taking mode as true to prevent cloning
            Ingredient* addition = inventoryMenu(true);
            // If the item exists, append it to the dish ingredient list
            if (!addition) {
                message = "No valid item was chosen.";
            } else {
                item->addIngredient(addition);
                message = addition->getName() + " was added to the " + item->getName();
            }

        // Entering 'r' removes an item from the dish
        } else if (input == 'r') {
            char choice = '\0'; // Stores further choice options
            Ingredient* removed = nullptr; // Stores removed item
            // List of ingredients in dish to remove from
            list<Ingredient*>& ingredients = item->getIngredients(); 

            // Iterates through the list of ingredients until the user either
            // decides to remove one, or cancelles the action
            while (choice != 'd') {
                for (const auto i : ingredients) {
                    cout << "Current item: \n" << i << endl;
                    cout << "Would you like to remove this item?" << endl;
                    cout << "  (r) Remove  (n) Next Item  (c) Cancel Removal" << endl;
                    cin >> choice;
                    
                    // If chosen, remove item and store it
                    if (choice == 'r') {
                        removed = item->removeIngredient(i);
                        break;
                    } else if (choice == 'c') {
                        break;
                    }
                }

                // If item was removed, or action was canelled, stop iterating
                if (removed || choice == 'c') {
                        break;
                    }
            }
            
            // If successfully removed continue the process. 
            if (removed) {
                cout << "\n\nRemoved the following item:" << endl;
                cout << removed << endl;
                cout << "Would you like to keep this item or delete it?" << endl;

                // Item can either be kept or deleted.
                while (choice != 'k' && choice != 'd') {
                    cout << "  (k) Keep  (d) Delete" << endl;
                    cin >> choice;
                }

                // Deletes item immediately if chosen.
                if (choice == 'd') {
                    cout << removed->getName() + " deleted." << endl;
                    message = "Removed " + removed->getName() + " and deleted it.";
                    delete removed;
                } else {
                    // Try to add item to inventory
                    while (!addItem(removed)) {
                        message = "Removed " + removed->getName() + " and kept it.";
                        cout << "No room in inventory." << endl;
                        cout << "Review inventory and try again?" << endl;
                        cout << "  (r) Review Inventory  (d) Delete Item" << endl;
                        cin >> choice;

                        // If addition fails, continue until an inventory slot has been freed up
                        // or until the user agrees to delete the item instead
                        if (choice == 'r') {
                            inventoryMenu();
                        } else if (choice == 'd') {
                            cout << "Deleted " + removed->getName();
                            message = "Removed " + removed->getName() + " and deleted it.";
                            delete removed;
                            break;
                        }
                    }
                }

            // If nothing is removed either because the sandwich was empty, or deletion was cancelled.
            } else {
                message = "Nothing to remove.";
            }

        // No message if invalid input.
        } else {
            message = "";
        }

    }

    // Final preparations for the dish (same as ingredients)
    string preparation;
    while (preparation != "x") {
        cout << "  ------       Dish Station       ------" << endl;
        cout << "  --------------------------------------" << endl;
        cout << "\n  Preparing sandwich: " << item << endl;
        cout << "  How would you like to prepare it? (Sliced, Toasted, etc.) Type 'x' to finsih prep." << endl;
        cin >> preparation;
        if (preparation != "x") {
            item->addPreparation(preparation);
        }
    }
    return item;
}

bool Kitchen::addItem(Ingredient* item) {
    // Interates through inventory until it reaches an empty slot.
    for (int i = 0; i < size; ++i) {
        if (inventory[i] == nullptr) {
            inventory[i] = item;
            return true;
        }
    }
    return false;
}

Ingredient* Kitchen::getItem(int index) {
    // If index is in bounds, return its item.
    if (index >= 0 && index < this->size && inventory[index] != nullptr) {
        return inventory[index];
    } else {
        cout << "Invalid item number." << endl;
    }
    return nullptr;
}

Ingredient* Kitchen::inventoryMenu(bool taking) {
    char choice = '\0'; // Stores action input
    int page = 0; // Tracks current inventory page
    bool inspecting = false; // Checks extra steps for inspection
    string message = ""; // Message from previous action

    // Action messages for easier comparissons
    string inspectString = "Enter the item number to inspect: ";
    string chooseString = "Enter the item number to choose: ";
    string deleteString = "Enter the item number to delete: ";

    do {
        cout << "\n" << endl;
        // If an inspection was requested, print it above inventory menu
        if (inspecting) {
            cout << message << endl;
            message = "Inspection printed above.";
            inspecting = false;
        }

        // Inventory menu header
        cout << "  ------      Inventory Menu      ------" << endl;
        cout << "  --------------------------------------" << endl;

        // Prints the current page of the inventory
        for (int i = page * pageSize; i < (page + 1) * pageSize && i < size; ++i) {
            cout << "    " << i + 1 << (i + 1 < 10? " : " : ": ") << (inventory[i] ? inventory[i]->getName() : "Empty") << endl;
        }
        cout << "  --------------------------------------" << endl;
        cout << "  " << (page > 0 ? "(p) Previous Page" : "                 ") << "  " << ((page + 1) * pageSize < size ? "(n) Next Page" : "             ") << "  " << "(x) Exit" << endl;
        cout << "  (i) Inspect Item  (c) Choose Item (d) Delete Item" << endl;

        // Message determined by previous choice
        cout << message << endl;

        // If previous choice requires extra input, prompt the user for it before next action
        if (message == chooseString) {
            int itemNumber; // User picks which item to choose
            cin >> itemNumber;
            // If choice is within the list, and isnt null, choose that item
            if (itemNumber >= 1 && itemNumber <= size && inventory[itemNumber - 1] != nullptr) {
                Ingredient* chosen = inventory[itemNumber - 1];

                // Remove pointer from inventory if menu was called to take an item out
                if (taking) {
                    inventory[itemNumber - 1] = nullptr;
                }

                return chosen;

            // Fails if item outside of list bounds or item was null
            } else {
                message = "Invalid item number.";
                continue;
            }
        } else if (message == inspectString) {
            int itemNumber; // User picks which item to inspect
            cin >> itemNumber;
            // If choice is within the list, and isnt null, inspect that item
            if (itemNumber >= 1 && itemNumber <= size && inventory[itemNumber - 1] != nullptr) {
                // Stores inspection data into a string
                stringstream ss;
                ss << inventory[itemNumber - 1];
                message = ss.str();;
                continue;

            // Fails if item outside of list bounds or item was null
            } else {
                message = "Invalid item number.";
            }
        } else if (message == deleteString) {
            int itemNumber; // User picks which item to delete
            cin >> itemNumber;
            // If choice is within the list, and isnt null, delete that item
            if (itemNumber >= 1 && itemNumber <= size && inventory[itemNumber - 1] != nullptr) {
                // Saves deleted items name and deallocates pointer before removal from inventory
                message = "Deleted " + inventory[itemNumber - 1]->getName();
                delete inventory[itemNumber - 1];
                inventory[itemNumber - 1] = nullptr;
                continue;
            
            // Fails if item outside of list bounds or item was null 
            } else {
                message = "Invalid item number.";
            }
        }

        // Gets user choice and reset message
        cin >> choice;
        message = "";

        // Goes to next page of inventory
        if (choice == 'n') {
            if ((page + 1) * pageSize >= size) {
                message = "You are on the last page.";
            } else {
                ++page;
            }

        // Goes to previous page of inventory
        } else if (choice == 'p') {
            if (page == 0) {
                message = "You are on the first page.";
            } else {
                --page;
            }

        // Inspects an item
        } else if (choice == 'i') {
            message = inspectString;

        // Chooses an item
        } else if (choice == 'c') {
            message = chooseString;

        // Deletes an item
        } else if (choice == 'd') {
            message = deleteString;

        // Otherwise no message
        } else {
            message = "";
        }

    // User exits menu by entering 'x'
    } while (choice != 'x');
    return nullptr;
}

void Kitchen::mainMenu() {
    char choice = '\0'; // Stores action input
    int createStep = 0; // Tracks steps in creating new item
    char newType = '\0'; // Stores type for new items
    string message = ""; // Stores message from previous action
    string newName = ""; // Stores name for new items
    Ingredient* currentItem = nullptr; // Stores held item


    do {
        cout << "\n" << endl;
        cout << "  ------      Main Menu      ------" << endl;
        cout << "  ---------------------------------" << endl;
        cout << "  Working at the " << name << endl;
        cout << "  Current held item: " << (currentItem ? currentItem->getName() : "None") << endl;
        cout << "  (i) View Inventory" << endl;
        cout << "  (n) Create New Item" << endl;
        cout << "  (c) Cook Held Item" << endl;
        cout << "  (p) Put Away Held Item" << endl;
        cout << "  (x) Exit" << endl;

        // Prints message based on previous action
        cout << message << endl;

        // Additional chain of inputs when creating a new item.
        // Step 1 gets the type of item
        if (createStep == 1) {
            createStep++;
            cin >> newType;
            string type;
            if (newType == 's') {
                type = "sandwich";
            } else if (newType == 'd') {
                type = "dish";
            } else {
                newType = 'i';
                type = "ingredient";
            }
            // Message for next step
            message = "What is the name of the " + type + ":";
            continue;

        // Step 2 gets the name of the item
        } else if (createStep == 2) {
            createStep++;
            cin.ignore();
            getline(cin, newName);

            // Skips calorie prompt if it isnt an ingredient.
            if (newType != 'i') {
                continue;
            }
            message = "How many calories are in the " + newName + ":";
            continue;

        // Step 3 gets calorie count and starts item preparation
        } else if (createStep == 3) {
            createStep = 0;
            int newCalories;
            Ingredient* newIngredient;

            // Only ingredients need calorie count, otherwise skip to preparation
            if (newType == 'i') {
                cin >> newCalories;
                newIngredient = prepareIngredient(new Ingredient(newName, newCalories));
            } else if (newType == 's') {
                newIngredient = prepareSandwich(new Sandwich(newName));
            } else if (newType == 'd') {
                newIngredient = prepareDish(new Dish(newName));
            }

            message = newName + " was created.";
            currentItem = newIngredient;
            continue;
        }

        // Gets user choice for the main menu
        cin >> choice;

        // Enters inventory menu
        if (choice == 'i') {
            message = "";
            // Picks item and removes from inventory
            Ingredient* picked = inventoryMenu(true);
            if (picked) {
                currentItem = picked;
            }

        // Creates new item in hand
        } else if (choice == 'n') {
            if (currentItem) {
                message = "Already holding an item.";
            } else {
                createStep = 1;
                message = "What is the type of the item?\n  (i) Ingredient  (s) Sandwich  (d) Dish";
            }

        // Starts cooking held item
        } else if (choice == 'c') {
            if (currentItem) {
                // Gets item type
                char type = currentItem->getType();
                // Different preparation steps for each item
                if (type == 'I') {
                    prepareIngredient(currentItem);
                } else if (type == 'D') {
                    Dish* dishItem = dynamic_cast<Dish*>(currentItem);
                    prepareDish(dishItem);
                } else if (type == 'S') {
                    Sandwich* sandwichItem = dynamic_cast<Sandwich*>(currentItem);
                    prepareSandwich(sandwichItem);
                }
            } else {
                message = "Not holding an item.";
            }

        // Puts an item back in inventory
        } else if (choice == 'p') {
            if (currentItem) {
                // Try to add item to inventory
                if (addItem(currentItem)) {
                    message = currentItem->getName() + " was put back in inventory.";
                    currentItem = nullptr;
                } else {
                    bool kept = false;
                    // Until addition succeeds ask for further input
                    while (!addItem(currentItem)) {
                        cout << "No room in inventory." << endl;
                        cout << "Review inventory and try again?" << endl;
                        cout << "  (r) Review Inventory  (d) Delete Item" << endl;
                        cout << "  (c) Cancel Action" << endl;
                        cin >> choice;

                        // If addition fails, continue until an inventory slot has been freed up
                        // or until the user agrees to cancel action or delete the item instead
                        if (choice == 'r') {
                            inventoryMenu();
                        } else if (choice == 'd') {
                            message =  "Deleted " + currentItem->getName();
                            delete currentItem;
                            break;
                        } else if (choice = 'c') {
                            message = currentItem->getName() + " was not put away.";
                            kept = true;
                            break;
                        }
                    }
                    if (!kept) {
                        currentItem = nullptr;
                        message = currentItem->getName() + " was put back in inventory.";
                    }
                }
            
            // Fails if no item is in hand to put away
            } else {
                message = "Not holding an item.";
            }

        // No message if invalid action
        } else {
            message = "";
        }

    // User exits main menu by entering 'x'
    } while (choice != 'x');
}