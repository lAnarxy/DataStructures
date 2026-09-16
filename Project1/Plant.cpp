#include "Plant.hpp"

Plant::Plant(string name, char type) {
    this->name = name;
    this->type = type;
    this->age = 0;
    this->position = -1;
}

ostream& operator<<(ostream& os, const Plant& p) {
    os << "This is a " << p.name << ". It is " << p.age << " weeks old";
    return os;
}