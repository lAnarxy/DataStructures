#include "Kitchen.hpp"


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

void Kitchen::pickItem() {
    int choice;
    cout << "Enter the item number to pick: ";
    cin >> choice;
    if (choice >= 0 && choice < this->size && inventory[choice] != nullptr) {
        cout << "You picked: " << inventory[choice]->getName() << endl;
    } else {
        cout << "Invalid item number." << endl;
    }
}

void Kitchen::inventoryMenu() {
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
        }
    } while (choice != 'x');
}