#include "Kitchen.hpp"
#include <sstream>

Ingredient* Kitchen::prepareIngredient(Ingredient* item) {
    cout << "Preparing ingredient: " << item << endl;
    string preparation;
    while (preparation != "x") {
        cout << "How would you like to prepare it? (Chopped, Diced, Boiled, etc.) Type 'x' to cancel." << endl;
        cin >> preparation;
        if (preparation != "x") {
            item->addPreparation(preparation);
        }
    }
    return item;
}

Ingredient* Kitchen::prepareSandwich(Ingredient* item) {
    // Implementation for preparing a sandwich goes here
    return item;
}

Ingredient* Kitchen::prepareDish(Ingredient* item) {
    // Implementation for preparing a dish goes here
    return item;
}

void Kitchen::addItem(Ingredient* item) {
    for (int i = 0; i < size; ++i) {
        if (inventory[i] == nullptr) {
            inventory[i] = item;
            inventoryID[i] = 'I'; // 'I' for Ingredient
            return;
        }
    }
    cout << "Inventory is full." << endl;
}

Ingredient* Kitchen::getItem(int index) {
    if (index >= 0 && index < this->size && inventory[index] != nullptr) {
        return inventory[index];
    } else {
        cout << "Invalid item number." << endl;
    }
    return nullptr;
}

Ingredient* Kitchen::inventoryMenu() {
    char choice = '\0';
    int page = 0;
    string message = "";
    do {
        cout << "  ------      Inventory Menu      ------" << endl;
        cout << "  --------------------------------------" << endl;
        for (int i = page * pageSize; i < (page + 1) * pageSize && i < size; ++i) {
            cout << "    " << i + 1 << (i + 1 < 10? " : " : ": ") << (inventory[i] ? inventory[i]->getName() : "Empty") << endl;
        }
        cout << "  --------------------------------------" << endl;
        cout << "  " << (page > 0 ? "(p) Previous Page" : "                 ") << "  " << ((page + 1) * pageSize < size ? "(n) Next Page" : "             ") << "  " << "(x) Exit" << endl;
        cout << "  (i) Inspect Item  (c) Choose Item" << endl;
        cout << message << endl;
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
            int itemNumber;
            cout << "Enter the item number to inspect: " << endl;
            cin >> itemNumber;
            if (itemNumber >= 1 && itemNumber <= size && inventory[itemNumber - 1] != nullptr) {
                stringstream ss;
                ss << inventory[itemNumber - 1];
                message = ss.str();
            } else {
                message = "Invalid item number.";
            }
        } else if (choice == 'c') {
            int itemNumber;
            cout << "Enter the item number to choose: " << endl;
            cin >> itemNumber;
            if (itemNumber >= 1 && itemNumber <= size && inventory[itemNumber - 1] != nullptr) {
                return inventory[itemNumber - 1];
            } else {
                message = "Invalid item number.";
            }
        }
    } while (choice != 'x');
    return nullptr;
}

void Kitchen::mainMenu() {
    char choice = '\0';
    Ingredient* currentItem = nullptr;
    string message = "";
    do {
        cout << "  ------      Main Menu      ------" << endl;
        cout << "  ---------------------------------" << endl;
        cout << "  Working at the " << name << endl;
        cout << "  Current held item: " << (currentItem ? currentItem->getName() : "None") << endl;
        cout << "  (i) View Inventory" << endl;
        cout << "  (c) Cook held item" << endl;
        cout << "  (x) Exit" << endl;
        cout << message << endl;
        cin >> choice;
        if (choice == 'i') {
            Ingredient* picked = inventoryMenu();
            if (picked) {
                currentItem = picked;
            }
        } else if (choice == 'c') {
            if (currentItem) {
                char type = currentItem->getType();
                if (type == 'I') {
                    prepareIngredient(currentItem);
                } else if (type == 'D') {
                    prepareDish(currentItem);
                } else if (type == 'S') {
                    prepareSandwich(currentItem);
                }
            } else {
                message = "Not holding an item.";
            }
        }
    } while (choice != 'x');
}