#include "Skill.hpp"

// Default CTOR
Skill::Skill() {
    name = "";
    desc = "";
    basePower = 0;
    masteryLevel = 1;
}
// User-Defined CTOR
Skill::Skill(string name, string desc, int basePower, int nElements, Elements* listElements) {
    this->name = name;
    this->desc = desc;
    this->basePower = basePower;
    this->masteryLevel = 1;
    this->listElements.clear();
    for (int i = 0; i < nElements; i++) {
        this->listElements.push_back(listElements[i]);
    }
}

Skill::Skill(string name, string desc, int basePower, vector<Elements> listElements) {
    this->name = name;
    this->desc = desc;
    this->basePower = basePower;
    this->masteryLevel = 1;
    this->listElements = listElements;
}

// CCTOR
Skill::Skill(const Skill& other) {
    this->name = other.name;
    this->desc = other.desc;
    this->basePower = other.basePower;
    this->masteryLevel = other.masteryLevel;
    this->listElements = other.listElements;
}
// DTOR
// ~Skill();
// Operator=
Skill& Skill::operator=(const Skill& other) {
    this->name = other.name;
    this->desc = other.desc;
    this->basePower = other.basePower;
    this->masteryLevel = other.masteryLevel;
    this->listElements = other.listElements;

    return *this;
}

// Service
void Skill::levelUp() {
    masteryLevel += 1;
}
void Skill::levelUp(int up) {
    masteryLevel += up;
}

int Skill::totalDamage() {
    return masteryLevel*basePower;
}

bool Skill::isElementCompatible(Elements ele) {
    return (std::find(listElements.begin(), listElements.end(), ele) != listElements.end());
}

bool Skill::isElementCompatible(int nElements, Elements* listEle) {
    bool found = false;
    int i;

    i = 0;
    while (!found && i < nElements) {
        if (std::find(listElements.begin(), listElements.end(), listEle[i]) != listElements.end())
        {
            found = true;
        }
        i++;
    }
    return found;
}

bool Skill::isElementCompatible(vector<Elements> listEle) {
    bool found = false;
    int i;

    i = 0;

    while (!found && i < listEle.size()) {
        if (std::find(listElements.begin(), listElements.end(), listEle[i]) != listElements.end())
        {
            found = true;
        }
        i++;
    }
    return found;
}


// Printer
void Skill::printAll() {
    cout << "-- " << name << " --" << endl;
    cout << desc << endl;
    cout << "BasePower    : " << basePower << endl;
    cout << "MasteryLevel : " << masteryLevel << endl;
    cout << "Elements     : ";
    for (int i = 0; i < listElements.size(); i++) {
        cout << elementName(listElements[i]);
        if (i < listElements.size() - 1) {
            cout << ", ";
        }
        
    }
    cout << endl; 
}

ostream& operator<<(ostream& os, const Skill& skill) {

    os << "-- " << skill.name << " --" << endl;
    os << skill.desc << endl;
    os << "BasePower    : " << skill.basePower << endl;
    os << "MasteryLevel : " << skill.masteryLevel << endl;
    os << "Elements     : ";
    for (int i = 0; i < skill.listElements.size(); i++) {
        os << elementName(skill.listElements[i]);
        if (i < skill.listElements.size() - 1) {
            cout << ", ";
        }
    }
    os << endl;
    return os;        
}


// Getter (Not necesarry, just in case)
string Skill::getName() {
    return name;
}
string Skill::getDesc() {
    return desc;
}
int Skill::getBasePower() {
    return basePower;
}
int Skill::getMasteryLevel() {
    return masteryLevel;
}