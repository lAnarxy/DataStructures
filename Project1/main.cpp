#include <iostream>
#include <limits>
#include "LinkedList.hpp"
#include "Plant.hpp"
// #include "Tool.hpp"
using namespace std;

void getCommand(char &command, int numGardens, int variant);
Plant* createPlant(int time);

int main() {
    cout << "Welcome to the Digital Garden!" << endl;
    int numGardens;
    cout << "How many gardens would you like to make? (1-6, 3 recommended)" << endl;
    cin >> numGardens;
    while (!(numGardens > 0 && numGardens < 7) || cin.fail()) {
        cout << "Invalid Input. Please enter a number between 1 and 6 (3 recommended)" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> numGardens;
    }
    cout << "Preparing " << numGardens << " gardens..." << endl;
    
    // Linked list of gardens, each garden is a linked list of plants
    LinkedList<LinkedList<Plant*>*>* gardens = new LinkedList<LinkedList<Plant*>*>();
    for (int i = 0; i < numGardens; i++) {
        LinkedList<Plant*>* garden = new LinkedList<Plant*>;
        gardens->insert_back(garden);
    }

    Node<LinkedList<Plant*>*>* gardenPos = gardens->getNode();
    Node<LinkedList<Plant*>*>* initialPos = gardenPos;
    char command;
    int time = 0;
    bool started = false;
    getCommand(command, numGardens, 0);
    while(command != 'x') {
        Node<Plant*>* plantPos;
        
        // Movement between gardens.
        if (command == 'g') {
            if (started) {
                gardenPos = gardenPos->next;
            } else {
                started = true;
            }
            cout<<"You have arrived at the next garden!"<<endl;
            cout<<"This garden has " << gardenPos->data->getSize() << " plants in it." <<endl;
            plantPos = gardenPos->data->getNode();

        // Inspect current pot
        } else if (command == 'i') {
            if (plantPos == nullptr) {
                cout<<"The pot is empty. You decide to plant something new!"<<endl;
                Plant* newPlant = createPlant(time);
                gardenPos->data->insert_back(newPlant);
                plantPos = gardenPos->data->getNode();
            } else {
                plantPos->data->updateAge(time);
                cout<<"There is a pot with a plant in it.\n"<< plantPos->data <<endl;
            }

        // Move to next pot
        } else if (command == 'm') {
            if (gardenPos->data->getSize() < 2) {
                cout<<"There is only one pot."<<endl;
            } else {
                plantPos = plantPos->next;
            }

        // Add a new pot
        } else if (command == 'p') {
            cout<<"You walk to the front of the garden. You place down another pot and decide to plant something new!"<<endl;
            Plant* newPlant = createPlant(time);
            gardenPos->data->insert_front(newPlant);
            plantPos = gardenPos->data->getNode();

        // Remove current pot
        } else if (command == 'r') {
            if (gardenPos->data->getSize() == 0) {
                cout<<"There are no plants to remove."<<endl;
            } else {
                int index = 0;
                Node<Plant*>* deleteCheck = gardenPos->data->getNode();
                while (plantPos != deleteCheck) {
                    deleteCheck = deleteCheck -> next;
                    index++;
                }
                cout<<"You removed the plant."<<endl;
                gardenPos->data->remove(index);
                plantPos = gardenPos->data->getNode();
            }
        }

        getCommand(command, numGardens, 1);
        cout<<"\n\n"<<endl;
        time++;
    }
    
    delete gardens;
    return 0;
}

// Function used to gat command input from user
void getCommand(char &command, int numGardens, int variant) {
    if (variant == 0) {
        cout<<"There are " << numGardens << " round gardens in front of you in a circle.\nType 'g' to go to the first garden\nType 'x' to leave the garden" << endl;
    }
    if (variant == 1) {
        cout<<"You are standing at a garden. There is a pot in front of you.\nType 'g' to go to the next garden\nType 'i' to inspect the pot in front of you.\nType 'p' to plant a new pot.\nType 'm' to move to the next pot.\nType 'r' to remove the plant in front of you.\nType 'x' to leave the garden"<<endl;
    }
    cin >> command;
    while (cin.fail()) {
        cout << "Invalid Input. Please enter a valid command" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> command;
    }
    return;
    
}

// Prompts user to create a new plant at given time.
Plant* createPlant(int time) {
    string name;
    cout<<"What is the name of this plant? "<<endl;
    cin >> name;
    while (cin.fail()) {
        cout << "Invalid Input. Please enter a valid string" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> name;
    }
    string type;
    cout<<"What type of plant is it? (Tree, Flower, Tuber, etc) "<<endl;
    cin >> type;
    while (cin.fail()) {
        cout << "Invalid Input. Please enter a valid string" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> type;
    }

    return new Plant(name, type, time);
}