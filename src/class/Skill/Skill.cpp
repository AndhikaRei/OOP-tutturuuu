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
void Skill::showSkill() {
    cout << "-- " << name << " --" << endl;
    cout << desc << endl;
    cout << "BasePower    : " << basePower << endl;
    cout << "MasteryLevel : " << masteryLevel << endl;
    cout << "Elements     : ";
    for (int i = 0; i < listElements.size(); i++) {
        cout << elementName(listElements[i]);
        if (i < listElements.size() - 1) {
            cout << "/";
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
            cout << "/";
        }
    }
    os << endl;
    return os;        
}


// Getter (Not necesarry, just in case)
string Skill::getName() const {
    return name;
}
string Skill::getDesc() const {
    return desc;
}
int Skill::getBasePower() const {
    return basePower;
}
int Skill::getMasteryLevel() const {
    return masteryLevel;
}


vector<Skill> databaseSkill;

void databaseSkillInitialization() {
    // General skill
    databaseSkill.clear();
    vector<Elements> allElement({Fire, Water, Electric, Ground, Ice});
    
    Skill s1("Punch", "Pukulan Maut!",10,allElement);
    Skill s2("Kick", "Sikat Miring!",10,allElement);
    Skill s3("ONE-PUNCH", "Hiyaa jurus si botak", 20, allElement);


    // 1 Element Skill
    vector<Elements> pyro({Fire}); 
    vector<Elements> hydro({Water});
    vector<Elements> electro({Electric});
    vector<Elements> geo({Ground});
    vector<Elements> cyro({Ice});

    Skill s4("Fire Breath", "Hah Naga!", 20, pyro);
    Skill s5("Doom Eternal", "Gelut sama setan", 30, pyro);
    Skill s6("Gush", "Ciuhh!", 20, hydro);
    Skill s7("Ravage", "Tentakel + Anime", 30, hydro);
    Skill s8("Ball Lighting", "Lookin for me?", 20, electro);
    Skill s9("Static Storm", "I'm ecstatic!",30 ,electro);
    Skill s10("Fissure", "Feel the earth shake!", 20, geo);
    Skill s11("Echo Slam", "1 Million Dollar Slam", 30, geo);
    Skill s12("Ice Path", "Beku broh", 20, hydro);
    Skill s13("Ice Ice Baby", "Seriously?", 30, hydro);

    
    // 2 Element Skill
    vector<Elements> vaporize({Fire,Water});
    vector<Elements> overload({Fire,Electric});
    vector<Elements> crystalizePyro({Fire,Ground});
    vector<Elements> melt({Fire,Ice});
    vector<Elements> electroCharged({Water,Electric});
    vector<Elements> crystalizeHydro({Water, Ground});
    vector<Elements> frozen({Water,Ice});
    vector<Elements> crystalizeElectro({Electric, Ground});
    vector<Elements> superConductor({Electric,Ice});
    vector<Elements> crystalizeCryo({Ice, Ground});

    // 3 Element Skill 

    Skill listSkill[] = {s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11};
    databaseSkill.insert(databaseSkill.begin(),listSkill,listSkill + sizeof(listSkill)/sizeof(listSkill[0]));


}


