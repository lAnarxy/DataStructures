#include "Plant.hpp"

Plant::Plant(string name, string type, int plant_date) {
    this->name = name;
    this->type = type;
    this->plant_date = plant_date;
    this->age = 0;
    this->position = -1;
    this->water = plant_date;
    this->maintenance = plant_date;
}

void Plant::updateAge(int time) {
    age = time - plant_date;
}

ostream& operator<<(ostream& os, const Plant& p) {
    os << "This is a " << p.name << ". It is " << p.age << " hours old";
    return os;
}

ostream& operator<<(ostream& os, const Plant* p) {
    os << "This is a " << p->name << ". It is " << p->age << " hours old";
    return os;
}