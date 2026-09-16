#include "Tool.hpp"

Tool::Tool(string name, char type) {
    this->name = name;
    this->type = type;
    this->age = 0;
    this->position = -1;
}

ostream& operator<<(ostream& os, const Tool& t) {
    os << "This is a " << t.name << ". It is " << t.age << " weeks old";
    return os;
}