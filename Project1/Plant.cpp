#include "Plant.hpp"

Plant::Plant(string name, char type, int plant_date) {
    this->name = name;
    this->type = type;
    this->plant_date = plant_date;
    this->position = -1;
    this->water = plant_date;
    this->maintenance = plant_date;
}

ostream& operator<<(ostream& os, const Plant& p) {
    os << "This is a " << p.name << ". It is " << p.plant_date << " weeks old";
    return os;
}

ostream& operator<<(ostream& os, const Plant* p) {
    os << "This is a " << p->name << ". It is " << p->plant_date << " weeks old";
    return os;
}