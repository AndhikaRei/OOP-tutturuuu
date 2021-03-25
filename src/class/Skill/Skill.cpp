#include "Skill.hpp"

// Default CTOR
Skill::Skill() {
    name = "";
    desc = "";
    basePower = 0;
    masteryLevel = 1;
}
// User-Defined CTOR
Skill::Skill(string name, string desc, int basePower, Elements Elements1, Elements Elements2,Elements Elements3,Elements Elements4,Elements Elements5) {
    this->name = name;
    this->desc = desc;
    this->basePower = basePower;
    this->masteryLevel = 1;
    this->listElements.clear();
    this->listElements.push_back(Elements1);
    if (Elements2 != NONE) this->listElements.push_back(Elements2);
    if (Elements3 != NONE) this->listElements.push_back(Elements3);
    if (Elements4 != NONE) this->listElements.push_back(Elements4);
    if (Elements5 != NONE) this->listElements.push_back(Elements5);
}

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

 // Operator==
bool Skill::operator==(const Skill& other) {
        return this->name == other.name;
}

// Service
void Skill::levelUp() {
    // Menaikan level Skill
    masteryLevel += 1;
    // cout << "Skill Level Up " << masteryLevel << endl;
}
void Skill::levelUp(int up) {
    // Menaikan level Skill sebanyak up
    masteryLevel += up;
}

int Skill::totalDamage() {
    // Menghitung total damage dari suatu skill
    return masteryLevel*basePower;
}

bool Skill::isElementCompatible(Elements ele) {
    // Mengcek apakah suatu elemen compatible dengan skill
    return (std::find(listElements.begin(), listElements.end(), ele) != listElements.end());
}

bool Skill::isElementCompatible(int nElements, Elements* listEle) {
    // Mengcek apakah suatu elemen compatible dengan skill
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
    // Mengcek apakah suatu elemen compatible dengan skill
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

void Skill::showSimpleSkill() {
    cout << "SkillName/BasePower : " << name << "/" << basePower << endl;
    cout << "Elements : ";
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
    Skill s4("Fire Breath", "Hah Naga!", 20, Fire);
    Skill s5("Doom Eternal", "Gelut sama setan", 30, Fire);
    Skill s6("Gush", "Ciuhh!", 20, Water);
    Skill s7("Ravage", "Tentakel + Anime", 30, Water);
    Skill s8("Ball Lighting", "Lookin for me?", 20, Electric);
    Skill s9("Static Storm", "I'm ecstatic!",30 ,Electric);
    Skill s10("Fissure", "Feel the earth shake!", 20, Ground);
    Skill s11("Echo Slam", "1 Million Dollar Slam", 30, Ground);
    Skill s12("Ice Path", "Beku broh", 20, Ice);
    Skill s13("Ice Ice Baby", "Seriously?", 30, Ice);

    // 2 Element Skill
    Skill s14("Rupture", "Bocor Bocor", 30, Fire, Water);
    Skill s15("Flamming Lasso", "Kena lo", 30, Fire, Electric);
    Skill s16("Life Break", "Loncat Indah", 30, Fire, Ground);
    Skill s17("Hand of God", "Tangan Madonna", 30, Fire, Ice);
    Skill s18("Chronosphere", "Zawarudo", 30, Water, Electric);
    Skill s19("Feast", "Laperrr",30,Water,Ground);
    Skill s20("Flux", "Ababil", 30, Water, Ice);
    Skill s21("Mana Void", "Duarr", 30, Electric, Ground);
    Skill s22("Heartstopper Aura", "Nyicil Darah", 30, Electric, Ice);
    Skill s23("Dark Ascension", "Stalker in The Night", 30, Ground, Ice);

    // 5 Element Skill
    Skill s69("DOOM","JURUS DAJAL",666,Fire,Water,Electric,Ground,Ice);

    Skill listSkill[] = {s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s69};
    databaseSkill.insert(databaseSkill.begin(),listSkill,listSkill + sizeof(listSkill)/sizeof(listSkill[0]));


}


