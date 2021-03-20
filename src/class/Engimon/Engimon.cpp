#include "Engimon.hpp"

using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

/*--- CLASS PARENT ---*/
Parent::Parent() { this->isParent = false; }
Parent::Parent(string _papaName, string _papaSpecies, string _mamaName, string _mamaSpecies)
{
    this->isParent = true;
    this->name.push_back(_papaName);
    this->name.push_back(_mamaName);
    this->species.push_back(_papaSpecies);
    this->species.push_back(_mamaSpecies);
}
Parent::Parent(const Parent &_parent)
{
    if (_parent.isParent)
    {
        this->isParent = true;
        this->name.push_back(_parent.name.at(0));
        this->name.push_back(_parent.name.at(1));
        this->species.push_back(_parent.species.at(0));
        this->species.push_back(_parent.species.at(1));
    }
    else
    {
        this->isParent = false;
    }
}
void Parent::showParent()
{
    if (this->isParent)
    {
        cout << this->name[0] << " - " << this->species[0] << ", ";
        cout << this->name[1] << " - " << this->species[1];
    }
    else
    {
        cout << "-";
    }
}

/*--- CLASS ENGIMON ---*/
Engimon::Engimon(string _name, string _species, Elements _elmt1, Elements _elmt2)
{
    this->name = _name;
    this->species = _species;

    this->parent = Parent();

    this->elements.push_back(_elmt1);
    if (_elmt2 != NONE)
    {
        this->elements.push_back(_elmt2);
    }

    this->level = 0;
    this->exp = 0;
    this->cumul_exp = 0;
}
Engimon::Engimon(string _name, string _species, const Parent &_parent, Elements _elmt1, Elements _elmt2)
{
    this->name = _name;
    this->species = _species;

    this->parent = _parent;

    this->elements.push_back(_elmt1);
    if (_elmt2 != NONE)
    {
        this->elements.push_back(_elmt2);
    }

    this->level = 0;
    this->exp = 0;
    this->cumul_exp = 0;
}
// Engimon& Engimon::operator=(const Engimon& _engi)
// {
// }
string Engimon::getName() const { return this->name; }
string Engimon::getSpecies() const { return this->species; }
Parent Engimon::getParent() const { return this->parent; }
vector<Elements> Engimon::getElements() const { return this->elements; }
vector<Skill> Engimon::getSkill() const { return this->skill; }
int Engimon::getLevel() const { return this->level; }
int Engimon::getExp() const { return this->exp; }
int Engimon::getCumulExp() const { return this->cumul_exp; }
void Engimon::rename(string _name) { this->name = _name; }
void Engimon::setParent(const Parent &_parent) { this->parent = _parent; }
bool Engimon::isOneElement() const { return this->elements.size() == 1; }
bool Engimon::isElement(Elements _ele) { return this->elements[0] == _ele ? true : isOneElement() ? false
                                                                                                  : this->elements[1] == _ele; }
void Engimon::addExp(int _exp)
{
    this->exp += _exp;
    this->cumul_exp += _exp;
    if (exp >= 100)
    {
        levelUp();
    }
}
void Engimon::addSkill(Skill sk)
{
    if (!skillLevelUp(sk))
    {
        if (this->skill.size() < 4)
        {
            this->skill.push_back(sk);
        }
        else
        {
            throw InvalidFullSkill();
        }
    }
}
void Engimon::addSkill(Skill_Item &_skit)
{
    Skill temp = _skit.learn(this->elements);
    if (!skillLevelUp(temp))
    {
        if (this->skill.size() < 4)
        {
            this->skill.push_back(temp);
        }
        else
        {
            throw InvalidFullSkill();
        }
    }
}
void Engimon::addSkill(Skill_Item &_skit, int _amount)
{
    Skill temp = _skit.learn(this->elements);
    if (!skillLevelUp(temp, _amount))
    {
        if (this->skill.size() < 4)
        {
            this->skill.push_back(temp);
        }
        else
        {
            throw InvalidFullSkill();
        }
    }
}
void Engimon::levelUp()
{
    cout << "Selamat, engimon kamu naik level!" << endl;
    this->level += exp / 100;
    this->exp %= 100;
}
void Engimon::showEngimon() const
{
    cout << "| " << name << " | ";
    cout << species << " | ";
    cout << "[" << elementName(elements[0]) << "]";
    if (!isOneElement())
    {
        cout << "[" << elementName(elements[1]) << "]";
    }
    cout << " | ";
    this->getParent().showParent();
    cout << " | ";
    cout << level << " | ";
    cout << exp << " | ";
    cout << cumul_exp << " | " << endl;
}
void Engimon::interact() const
{
    cout << this->name << ": " << this->slogan << endl;
}
bool Engimon::skillLevelUp(Skill sk)
{
    vector<Skill>::iterator it = std::find(skill.begin(), skill.end(), sk);
    if (it != skill.end())
    {
        it->levelUp();
        return true;
    }
    return false;
}
bool Engimon::skillLevelUp(Skill sk, int lv)
{
    vector<Skill>::iterator it = std::find(skill.begin(), skill.end(), sk);
    if (it != skill.end())
    {
        it->levelUp(lv);
        return true;
    }
    return false;
}
char Engimon::getEngimonSymbol()
{
    if (this->species == "Pyro")
    {
        return this->level > 10 ? 'A' : 'a';
    }
    else if (this->species == "Hydro")
    {
        return this->level > 10 ? 'B' : 'b';
    }
    else if (this->species == "Electro")
    {
        return this->level > 10 ? 'C' : 'c';
    }
    else if (this->species == "Geo")
    {
        return this->level > 10 ? 'D' : 'd';
    }
    else if (this->species == "Cryo")
    {
        return this->level > 10 ? 'E' : 'e';
    }
    else if (this->species == "Vaporize")
    {
        return this->level > 10 ? 'F' : 'f';
    }
    else if (this->species == "Overload")
    {
        return this->level > 10 ? 'G' : 'g';
    }
    else if (this->species == "PyroCrystallize")
    {
        return this->level > 10 ? 'H' : 'h';
    }
    else if (this->species == "Melt")
    {
        return this->level > 10 ? 'I' : 'i';
    }
    else if (this->species == "ElectroCharged")
    {
        return this->level > 10 ? 'J' : 'j';
    }
    else if (this->species == "HydroCrystallize")
    {
        return this->level > 10 ? 'K' : 'k';
    }
    else if (this->species == "Frozen")
    {
        return this->level > 10 ? 'L' : 'l';
    }
    else if (this->species == "ElectroCrystallize")
    {
        return this->level > 10 ? 'M' : 'm';
    }
    else if (this->species == "Superconductor")
    {
        return this->level > 10 ? 'N' : 'n';
    }
    else
    {
        //this->species=="CryoCrystallize"
        return this->level > 10 ? 'Q' : 'q';
    }
};

/*--- CLASS SPECIES ---*/
Pyro::Pyro(string _name) : Engimon(_name, "Pyro", Fire)
{
    this->slogan = "Se no!~";
    this->skill.push_back(Skill("Explosion!", "Megumin approved.", 20, Fire));
}
Pyro::Pyro(string _name, const Parent &_parent) : Engimon(_name, "Pyro", _parent, Fire)
{
    this->slogan = "Se no!~";
    this->skill.push_back(Skill("Explosion!", "Megumin approved.", 20, Fire));
}
Engimon *Pyro::clone()
{
    return new Pyro(*this);
}

Hydro::Hydro(string _name) : Engimon(_name, "Hydro", Water)
{
    this->slogan = "Demo sonnan ja dame~";
    this->skill.push_back(Skill("Purification!", "Aqua approved.", 20, Water));
}
Hydro::Hydro(string _name, const Parent &_parent) : Engimon(_name, "Hydro", _parent, Water)
{
    this->slogan = "Demo sonnan ja dame~";
    this->skill.push_back(Skill("Purification!", "Aqua approved.", 20, Water));
}
Engimon *Hydro::clone()
{
    return new Hydro(*this);
}

Electro::Electro(string _name) : Engimon(_name, "Electro", Electric)
{
    this->slogan = "Mou sonnan ja hora~";
    this->skill.push_back(Skill("Thunderstorm", "Lightning goes brrr.", 20, Electric));
}
Electro::Electro(string _name, const Parent &_parent) : Engimon(_name, "Electro", _parent, Electric)
{
    this->slogan = "Mou sonnan ja hora~";
    this->skill.push_back(Skill("Thunderstorm", "Lightning goes brrr.", 20, Electric));
}
Engimon *Electro::clone()
{
    return new Electro(*this);
}

Geo::Geo(string _name) : Engimon(_name, "Geo", Ground)
{
    this->slogan = "Kokoro wa shinka suru yo~";
    this->skill.push_back(Skill("Tanah tinggi!", "Ez cover.", 20, Ground));
}
Geo::Geo(string _name, const Parent &_parent) : Engimon(_name, "Geo", _parent, Ground)
{
    this->slogan = "Kokoro wa shinka suru yo~";
    this->skill.push_back(Skill("Tanah tinggi!", "Ez cover.", 20, Ground));
}
Engimon *Geo::clone()
{
    return new Geo(*this);
}

Cryo::Cryo(string _name) : Engimon(_name, "Cryo", Ice)
{
    this->slogan = "Motto motto~";
    this->skill.push_back(Skill("Freeze!", "I'll never use my dad's power.", 20, Ice));
}
Cryo::Cryo(string _name, const Parent &_parent) : Engimon(_name, "Cryo", _parent, Ice)
{
    this->slogan = "Motto motto~";
    this->skill.push_back(Skill("Freeze!", "I'll never use my dad's power.", 20, Ice));
}
Engimon *Cryo::clone()
{
    return new Cryo(*this);
}

Vaporize::Vaporize(string _name) : Engimon(_name, "Vaporize", Fire, Water)
{
    this->slogan = "Fuwa fuwari, fuwa fuwaru~";
    this->skill.push_back(Skill("Indomie rebus", "Masak aer.", 20, Fire, Water));
}
Vaporize::Vaporize(string _name, const Parent &_parent) : Engimon(_name, "Vaporize", _parent, Fire, Water)
{
    this->slogan = "Fuwa fuwari, fuwa fuwaru~";
    this->skill.push_back(Skill("Indomie rebus", "Masak aer.", 20, Fire, Water));
}
Engimon *Vaporize::clone()
{
    return new Vaporize(*this);
}

Overload::Overload(string _name) : Engimon(_name, "Overload", Fire, Electric)
{
    this->slogan = "Anata ga namae wo yobu~";
    this->skill.push_back(Skill("Korsleting", "Api berpadu dengan Listrik", 20, Fire, Electric));
}
Overload::Overload(string _name, const Parent &_parent) : Engimon(_name, "Overload", _parent, Fire, Electric)
{
    this->slogan = "Anata ga namae wo yobu~";
    this->skill.push_back(Skill("Korsleting", "Api berpadu dengan Listrik", 20, Fire, Electric));
}
Engimon *Overload::clone()
{
    return new Overload(*this);
}

PyroCrystallize::PyroCrystallize(string _name) : Engimon(_name, "PyroCrystallize", Fire, Ground)
{
    this->slogan = "Sore dake de chuu e ukabu~";
    this->skill.push_back(Skill("Golem Api!", "Ez tank.", 20, Fire, Ground));
}
PyroCrystallize::PyroCrystallize(string _name, const Parent &_parent) : Engimon(_name, "PyroCrystallize", _parent, Fire, Ground)
{
    this->slogan = "Sore dake de chuu e ukabu~";
    this->skill.push_back(Skill("Golem Api!", "Ez tank.", 20, Fire, Ground));
}
Engimon *PyroCrystallize::clone()
{
    return new PyroCrystallize(*this);
}

Melt::Melt(string _name) : Engimon(_name, "Melt", Fire, Ice)
{
    this->slogan = "Fuwafuwaru fuwafuwari~";
    this->skill.push_back(Skill("Half-Cold Half-Hot", "Todoroki not approve.", 20, Fire, Ice));
}
Melt::Melt(string _name, const Parent &_parent) : Engimon(_name, "Melt", _parent, Fire, Ice)
{
    this->slogan = "Fuwafuwaru fuwafuwari~";
    this->skill.push_back(Skill("Half-Cold Half-Hot", "Todoroki not approve.", 20, Fire, Ice));
}
Engimon *Melt::clone()
{
    return new Melt(*this);
}

ElectroCharged::ElectroCharged(string _name) : Engimon(_name, "ElectroCharged", Water, Electric)
{
    this->slogan = "Anata ga waratte iru~";
    this->skill.push_back(Skill("Charged Water!", "Hati-hati kesetrum.", 20, Water, Electric));
}
ElectroCharged::ElectroCharged(string _name, const Parent &_parent) : Engimon(_name, "ElectroCharged", _parent, Water, Electric)
{
    this->slogan = "Anata ga waratte iru~";
    this->skill.push_back(Skill("Charged Water!", "Hati-hati kesetrum.", 20, Water, Electric));
}
Engimon *ElectroCharged::clone()
{
    return new ElectroCharged(*this);
}

HydroCrystallize::HydroCrystallize(string _name) : Engimon(_name, "HydroCrystallize", Water, Ground)
{
    this->slogan = "Sore dake de egao ni naru~";
    this->skill.push_back(Skill("Golem Air!", "Ez tank 2.", 20, Water, Ground));
}
HydroCrystallize::HydroCrystallize(string _name, const Parent &_parent) : Engimon(_name, "HydroCrystallize", _parent, Water, Ground)
{
    this->slogan = "Sore dake de egao ni naru~";
    this->skill.push_back(Skill("Golem Air!", "Ez tank 2.", 20, Water, Ground));
}
Engimon *HydroCrystallize::clone()
{
    return new HydroCrystallize(*this);
}

Frozen::Frozen(string _name) : Engimon(_name, "Frozen", Water, Ice)
{
    this->slogan = "Kami-sama arigatou~";
    this->skill.push_back(Skill("Let it go~", "Elsa approved.", 20, Water, Ice));
}
Frozen::Frozen(string _name, const Parent &_parent) : Engimon(_name, "Grozen", _parent, Water, Ice)
{
    this->slogan = "Kami-sama arigatou~";
    this->skill.push_back(Skill("Let it go~", "Elsa approved.", 20, Water, Ice));
}
Engimon *Frozen::clone()
{
    return new Frozen(*this);
}

ElectroCrystallize::ElectroCrystallize(string _name) : Engimon(_name, "ElectroCrystallize", Electric, Ground)
{
    this->slogan = "Unmei no itazura demo~";
    this->skill.push_back(Skill("Golem Petir!", "Ez tank 3.", 20, Electric, Ground));
}
ElectroCrystallize::ElectroCrystallize(string _name, const Parent &_parent) : Engimon(_name, "ElectroCrystallize", _parent, Electric, Ground)
{
    this->slogan = "Unmei no itazura demo~";
    this->skill.push_back(Skill("Golem Petir!", "Ez tank 3.", 20, Electric, Ground));
}
Engimon *ElectroCrystallize::clone()
{
    return new ElectroCrystallize(*this);
}

Superconductor::Superconductor(string _name) : Engimon(_name, "Superconductor", Electric, Ice)
{
    this->slogan = "Meguriaeta koto ga~";
    this->skill.push_back(Skill("Species-self-explanatory.", "Masa listrik bisa berpadu dengan es?", 20, Electric, Ice));
}
Superconductor::Superconductor(string _name, const Parent &_parent) : Engimon(_name, "Superconductor", _parent, Electric, Ice)
{
    this->slogan = "Meguriaeta koto ga~";
    this->skill.push_back(Skill("Species-self-explanatory.", "Masa listrik bisa berpadu dengan es?", 20, Electric, Ice));
}
Engimon *Superconductor::clone()
{
    return new Superconductor(*this);
}

CryoCrystallize::CryoCrystallize(string _name) : Engimon(_name, "CryoCrystallize", Ground, Ice)
{
    this->slogan = "Shiawase na no~";
    this->skill.push_back(Skill("Golem Es!", "Ez tank 4.", 20, Ground, Ice));
}
CryoCrystallize::CryoCrystallize(string _name, const Parent &_parent) : Engimon(_name, "CryoCrystallize", _parent, Ground, Ice)
{
    this->slogan = "Shiawase na no~";
    this->skill.push_back(Skill("Golem Es!", "Ez tank 4.", 20, Ground, Ice));
}
Engimon *CryoCrystallize::clone()
{
    return new CryoCrystallize(*this);
}

/*--- MISC ---*/
map<string, Engimon *> Engidex;

void initEngidex()
{
    Engidex.clear();
    Engimon *e1 = new Pyro("Pyro sp.");
    Engimon *e2 = new Hydro("Hydro sp.");
    Engimon *e3 = new Electro("Electro sp.");
    Engimon *e4 = new Geo("Geo sp.");
    Engimon *e5 = new Cryo("Cryo sp.");
    Engimon *e6 = new Vaporize("Vaporize sp.");
    Engimon *e7 = new Overload("Overload sp.");
    Engimon *e8 = new PyroCrystallize("PyroCrystallize sp.");
    Engimon *e9 = new Melt("Melt sp.");
    Engimon *e10 = new ElectroCharged("ElectroCharged sp.");
    Engimon *e11 = new HydroCrystallize("HydroCrystallize sp.");
    Engimon *e12 = new Frozen("Frozen sp.");
    Engimon *e13 = new ElectroCrystallize("ElectroCrystallize sp.");
    Engimon *e14 = new Superconductor("Superconductor sp.");
    Engimon *e15 = new CryoCrystallize("CryoCrystallize sp.");

    Engidex.insert(pair<string, Engimon *>("Pyro", e1));
    Engidex.insert(pair<string, Engimon *>("Hydro", e2));
    Engidex.insert(pair<string, Engimon *>("Electro", e3));
    Engidex.insert(pair<string, Engimon *>("Geo", e4));
    Engidex.insert(pair<string, Engimon *>("Cryo", e5));
    Engidex.insert(pair<string, Engimon *>("Vaporize", e6));
    Engidex.insert(pair<string, Engimon *>("Overload", e7));
    Engidex.insert(pair<string, Engimon *>("PyroCrystallize", e8));
    Engidex.insert(pair<string, Engimon *>("Melt", e1));
    Engidex.insert(pair<string, Engimon *>("ElectroCharged", e10));
    Engidex.insert(pair<string, Engimon *>("HydroCrystallize", e11));
    Engidex.insert(pair<string, Engimon *>("Frozen", e12));
    Engidex.insert(pair<string, Engimon *>("ElectroCrystallize", e13));
    Engidex.insert(pair<string, Engimon *>("Superconductor", e14));
    Engidex.insert(pair<string, Engimon *>("CryoCrystallize", e15));
}

vector<Engimon *> EngimonFinder(string _species)
{
    vector<Engimon *> temp;
    temp.push_back(Engidex[_species]);
    return temp;
}
vector<Engimon *> EngimonFinder(Elements _e1, Elements _e2)
{
    vector<Engimon *> temp;
    map<string, Engimon *>::iterator it;
    for (it = Engidex.begin(); it != Engidex.end(); it++)
    {
        if (_e2 == NONE)
        {
            if (it->second->isElement(_e1))
            {
                temp.push_back(it->second);
            }
        }
        else
        {
            if (it->second->isElement(_e1) || it->second->isElement(_e2))
            {
                temp.push_back(it->second);
            }
        }
    }
    return temp;
}