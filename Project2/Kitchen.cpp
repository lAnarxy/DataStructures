#include "Kitchen.hpp"
#include <sstream>

Ingredient* Kitchen::prepareIngredient(Ingredient* item) {
    string preparation;
    while (preparation != "x") {
        cout << "\nPreparing ingredient: " << item << endl;
        cout << "How would you like to prepare it? (Chopped, Diced, Boiled, etc.) Type 'x' to finsih prep." << endl;
        cin >> preparation;
        if (preparation != "x") {
            item->addPreparation(preparation);
        }
    }
    return item;
}

Ingredient* Kitchen::prepareSandwich(Sandwich* item) {
    char input;
    string message = "";
    while (input != 'x') {
        cout << "  ------     Sandwich Station     ------" << endl;
        cout << "  --------------------------------------" << endl;
        cout << "  Preparing sandwich: " << item << endl;
        cout << "\n  What do you want to do to the sandwich?" << endl;
        cout << "  (a) Add Ingredient  (r) Remove Ingredient" << endl;
        cout << "  (f) Flip Sandwich  (x) Finish Sandwich" << endl;
        cout << message << endl;

        cin >> input;
        if (input == 'a') {
            Ingredient* addition = inventoryMenu(true);
            if (!addition) {
                message = "No valid item was chosen.";
            } else {
                item->addIngredient(addition);
                message = addition->getName() + " was added to the top of the " + item->getName();
            }
        } else if (input == 'r') {
            Ingredient* removed = item->removeIngredient();
            if (removed) {
                cout << "\n\nRemoved the following item:" << endl;
                cout << removed << endl;
                cout << "Would you like to keep this item or delete it?" << endl;
                char choice = '\0';
                while (choice != 'k' && choice != 'd') {
                    cout << "  (k) Keep  (d) Delete" << endl;
                    cin >> choice;
                }

                if (choice == 'd') {
                    cout << removed->getName() + " deleted." << endl;
                    delete removed;
                } else {
                    while (!addItem(removed)) {
                        cout << "No room in inventory." << endl;
                        cout << "Review inventory and try again?" << endl;
                        cout << "  (r) Review Inventory  (d) Delete Item" << endl;
                        cin >> choice;

                        if (choice == 'r') {
                            inventoryMenu();
                        } else if (choice == 'd') {
                            cout << "Deleted " + removed->getName();
                            delete removed;
                            break;
                        }
                    }
                }
            } else {
                message = "Nothing to remove.";
            }
        } else if (input == 'f') {
            item->flip();
        } else {
            message = "";
        }

    }
    // Final preparations for the sandwich
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
    char input;
    string message = "";
    while (input != 'x') {
        cout << "  ------       Dish Station       ------" << endl;
        cout << "  --------------------------------------" << endl;
        cout << "  Preparing dish: " << item << endl;
        cout << "\n  What do you want to do to the dish?" << endl;
        cout << "  (a) Add Ingredient  (r) Remove Ingredient" << endl;
        cout << "  (x) Finish Dish" << endl;
        cout << message << endl;

        cin >> input;
        if (input == 'a') {
            Ingredient* addition = inventoryMenu(true);
            if (!addition) {
                message = "No valid item was chosen.";
            } else {
                item->addIngredient(addition);
                message = addition->getName() + " was added to the " + item->getName();
            }
        } else if (input == 'r') {
            int index = 0;
            char choice = '\0';

            list<Ingredient*>& ingredients = item->getIngredients();
            Ingredient* removed = nullptr;
            while (choice != 'd') {
                for (const auto i : ingredients) {
                    cout << "Current item: \n" << i << endl;
                    cout << "Would you like to remove this item?" << endl;
                    cout << "  (r) Remove  (n) Next Item  (c) Cancel Removal" << endl;
                    cin >> choice;
                    
                    if (choice == 'r') {
                        removed = item->removeIngredient(i);
                        break;
                    } else if (choice == 'c') {
                        break;
                    }
                }
                if (removed) {
                        break;
                    }
            }
             
            if (removed) {
                cout << "\n\nRemoved the following item:" << endl;
                cout << removed << endl;
                cout << "Would you like to keep this item or delete it?" << endl;

                while (choice != 'k' && choice != 'd') {
                    cout << "  (k) Keep  (d) Delete" << endl;
                    cin >> choice;
                }

                if (choice == 'd') {
                    cout << removed->getName() + " deleted." << endl;
                    message = "Removed " + removed->getName() + " and deleted it.";
                    delete removed;
                } else {
                    while (!addItem(removed)) {
                        message = "Removed " + removed->getName() + " and kept it.";
                        cout << "No room in inventory." << endl;
                        cout << "Review inventory and try again?" << endl;
                        cout << "  (r) Review Inventory  (d) Delete Item" << endl;
                        cin >> choice;

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
            } else {
                message = "Nothing to remove.";
            }
        } else {
            message = "";
        }

    }
    // Final preparations for the sandwich
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
    for (int i = 0; i < size; ++i) {
        if (inventory[i] == nullptr) {
            inventory[i] = item;
            return true;
        }
    }
    return false;
}

Ingredient* Kitchen::getItem(int index) {
    if (index >= 0 && index < this->size && inventory[index] != nullptr) {
        return inventory[index];
    } else {
        cout << "Invalid item number." << endl;
    }
    return nullptr;
}

Ingredient* Kitchen::inventoryMenu(bool taking) {
    char choice = '\0';
    int page = 0;
    bool inspecting = false;
    string inspectString = "Enter the item number to inspect: ";
    string chooseString = "Enter the item number to choose: ";
    string deleteString = "Enter the item number to delete: ";
    string message = "";
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
            int itemNumber;
            cin >> itemNumber;
            if (itemNumber >= 1 && itemNumber <= size && inventory[itemNumber - 1] != nullptr) {
                Ingredient* chosen = inventory[itemNumber - 1];
                if (taking) {
                    inventory[itemNumber - 1] = nullptr;
                }
                return chosen;
            } else {
                message = "Invalid item number.";
                continue;
            }
        } else if (message == inspectString) {
            int itemNumber;
            cin >> itemNumber;
            if (itemNumber >= 1 && itemNumber <= size && inventory[itemNumber - 1] != nullptr) {
                stringstream ss;
                ss << inventory[itemNumber - 1];
                message = ss.str();;
                continue;
            } else {
                message = "Invalid item number.";
            }
        } else if (message == deleteString) {
            int itemNumber;
            cin >> itemNumber;
            if (itemNumber >= 1 && itemNumber <= size && inventory[itemNumber - 1] != nullptr) {
                message = "Deleted " + inventory[itemNumber - 1]->getName();
                delete inventory[itemNumber - 1];
                inventory[itemNumber - 1] = nullptr;
                continue;
            } else {
                message = "Invalid item number.";
            }
        }

        // Gets user choice and reset message
        cin >> choice;
        message = "";
        if (choice == 'n') {
            if ((page + 1) * pageSize >= size) {
                message = "You are on the last page.";
            } else {
                ++page;
            }
        } else if (choice == 'p') {
            if (page == 0) {
                message = "You are on the first page.";
            } else {
                --page;
            }
        } else if (choice == 'i') {
            message = inspectString;
        } else if (choice == 'c') {
            message = chooseString;
        } else if (choice == 'd') {
            message = deleteString;
        } else {
            message = "";
        }
    } while (choice != 'x');
    return nullptr;
}

void Kitchen::mainMenu() {
    char choice = '\0';
    int createStep = 0;
    char newType = '\0';
    string newName = "";
    Ingredient* currentItem = nullptr;
    string message = "";
    do {
        cout << "\n" << endl;
        cout << "  ------      Main Menu      ------" << endl;
        cout << "  ---------------------------------" << endl;
        cout << "  Working at the " << name << endl;
        cout << "  Current held item: " << (currentItem ? currentItem->getName() : "None") << endl;
        cout << "  (i) View Inventory" << endl;
        cout << "  (n) Create New Item" << endl;
        cout << "  (c) Cook Held Item" << endl;
        cout << "  (p) Put Down Held Item" << endl;
        cout << "  (x) Exit" << endl;

        // Prints message based on previous action
        cout << message << endl;

        // Additional chain of inputs when creating a new item.
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
            message = "What is the name of the " + type + ":";
            continue;
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
        } else if (createStep == 3) {
            createStep = 0;
            int newCalories;
            Ingredient* newIngredient;
            if (newType == 'i') {
                cin >> newCalories;
                newIngredient = prepareIngredient(new Ingredient(newName, newCalories));
            } else if (newType == 's') {
                newIngredient = prepareSandwich(new Sandwich(newName));
            } else if (newType == 'd') {
                newIngredient = prepareDish(new Dish(newName));
            }

            if (addItem(newIngredient)) {
                message = newName + " was successfully added to inventory.";
                continue;
            } else {
                message = "Could not add item. Inventory is full";
                delete newIngredient;
                continue;
            }
        }

        // Gets user choice for the main menu
        cin >> choice;
        if (choice == 'i') {
            message = "";
            Ingredient* picked = inventoryMenu();
            if (picked) {
                currentItem = picked;
            }
        } else if (choice == 'n') {
            if (currentItem) {
                message = "Already holding an item.";
            } else {
                createStep = 1;
                message = "What is the type of the item?\n  (i) Ingredient  (s) Sandwich  (d) Dish";
            }
        } else if (choice == 'c') {
            if (currentItem) {
                char type = currentItem->getType();
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
        } else if (choice == 'p') {
            if (currentItem) {
                message = currentItem->getName() + " was put down.";
                currentItem = nullptr;
            } else {
                message = "Not holding an item.";
            }
        } else {
            message = "";
        }
    } while (choice != 'x');
}