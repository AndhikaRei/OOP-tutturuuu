#include "Engimon.hpp"

using namespace std;
/*--- CLASS PARENT ---*/
Parent::Parent()
{
    this->isParent = false;
    this->name = new string[2];
    this->species = new string[2];
}
Parent::Parent(string _papaName, string _papaSpecies, string _mamaName, string _mamaSpecies)
{
    this->isParent = true;
    this->name = new string[2];
    this->species = new string[2];
    this->name[0] = _papaName;
    this->name[1] = _mamaName;
    this->species[0] = _papaSpecies;
    this->species[1] = _mamaSpecies;
}
Parent::~Parent()
{
    delete[] name;
    delete[] species;
}
void Parent::showParent()
{
    if (this->isParent)
    {
        cout << "Parent 1              :";
        cout << this->name[0] << " - " << this->species[0] << '\n';
        cout << "Parent 2              :";
        cout << this->name[1] << " - " << this->species[1] << '\n';
    }
    else
    {
        cout << "Parent                : -\n";
    }
}

/*--- CLASS ENGIMON ---*/
Engimon::Engimon(string _name, string _species, int _elmt1, int _elmt2)
{
    this->name = _name;
    this->species = _species;

    this->parent = Parent();

    this->elements = new int[2];
    this->elements[0] = _elmt1;
    this->elements[1] = _elmt2;

    this->skill = new string[4];

    this->level = 0;
    this->exp = 0;
    this->cumul_exp = 0;

    showEngimon();
}
Engimon::Engimon(string _name, string _species, const Parent &_parent, int _elmt1, int _elmt2)
{
    this->name = _name;
    this->species = _species;

    this->parent = _parent;

    this->elements = new int[2];
    this->elements[0] = _elmt1;
    this->elements[1] = _elmt2;

    this->skill = new string[4];

    this->level = 0;
    this->exp = 0;
    this->cumul_exp = 0;

    showEngimon();
}
Engimon::~Engimon()
{
    delete[] elements;
    delete[] skill;
}
string Engimon::getName() const
{
    return this->name;
}
string Engimon::getSpecies() const
{
    return this->species;
}
void Engimon::levelUp()
{
    this->exp %= 100;
    this->level += exp / 100;
}
void Engimon::showEngimon()
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Name                  : " << name << '\n';
    cout << "Species               : " << species << '\n';
    cout << "Element(s)            : [" << elements[0] << "]";
    if (elements[1] != NONE)
    {
        cout << "[" << elements[1] << "]";
    }
    cout << endl;
    this->parent.showParent();
    cout << "Level                 : " << level << '\n';
    cout << "Experience            : " << exp << '\n';
    cout << "Cumulative Experience : " << cumul_exp << endl;
}

/*--- CLASS SPECIES ---*/
Pyro::Pyro(string _name) : Engimon(_name, "Pyro", Fire)
{
}
Pyro::Pyro(string _name, const Parent &_parent) : Engimon(_name, "Pyro", _parent, Fire)
{
}

Hydro::Hydro(string _name) : Engimon(_name, "Hydro", Water)
{
}
Hydro::Hydro(string _name, const Parent &_parent) : Engimon(_name, "Hydro", _parent, Water)
{
}

Electro::Electro(string _name) : Engimon(_name, "Electro", Electric)
{
}
Electro::Electro(string _name, const Parent &_parent) : Engimon(_name, "Electro", _parent, Electric)
{
}

Geo::Geo(string _name) : Engimon(_name, "Geo", Ground)
{
}
Geo::Geo(string _name, const Parent &_parent) : Engimon(_name, "Geo", _parent, Ground)
{
}

Cryo::Cryo(string _name) : Engimon(_name, "Cryo", Ice)
{
}
Cryo::Cryo(string _name, const Parent &_parent) : Engimon(_name, "Cryo", _parent, Ice)
{
}

Vaporize::Vaporize(string _name) : Engimon(_name, "Vaporize", Fire, Water)
{
}
Vaporize::Vaporize(string _name, const Parent &_parent) : Engimon(_name, "Vaporize", _parent, Fire, Water)
{
}

Overload::Overload(string _name) : Engimon(_name, "Overload", Fire, Electric)
{
}
Overload::Overload(string _name, const Parent &_parent) : Engimon(_name, "Overload", _parent, Fire, Electric)
{
}

PyroCrystallize::PyroCrystallize(string _name) : Engimon(_name, "PyroCrystallize", Fire, Ground)
{
}
PyroCrystallize::PyroCrystallize(string _name, const Parent &_parent) : Engimon(_name, "PyroCrystallize", _parent, Fire, Ground)
{
}

Melt::Melt(string _name) : Engimon(_name, "Melt", Fire, Ice)
{
}
Melt::Melt(string _name, const Parent &_parent) : Engimon(_name, "Melt", _parent, Fire, Ice)
{
}

ElectroCharged::ElectroCharged(string _name) : Engimon(_name, "ElectroCharged", Water, Electric)
{
}
ElectroCharged::ElectroCharged(string _name, const Parent &_parent) : Engimon(_name, "ElectroCharged", _parent, Water, Electric)
{
}

HydroCrystallize::HydroCrystallize(string _name) : Engimon(_name, "HydroCrystallize", Water, Ground)
{
}
HydroCrystallize::HydroCrystallize(string _name, const Parent &_parent) : Engimon(_name, "HydroCrystallize", _parent, Water, Ground)
{
}

Frozen::Frozen(string _name) : Engimon(_name, "Frozen", Water, Ice)
{
}
Frozen::Frozen(string _name, const Parent &_parent) : Engimon(_name, "Grozen", _parent, Water, Ice)
{
}

ElectroCrystallize::ElectroCrystallize(string _name) : Engimon(_name, "ElectroCrystallize", Electric, Ground)
{
}
ElectroCrystallize::ElectroCrystallize(string _name, const Parent &_parent) : Engimon(_name, "ElectroCrystallize", _parent, Electric, Ground)
{
}

Superconductor::Superconductor(string _name) : Engimon(_name, "Superconductor", Electric, Ice)
{
}
Superconductor::Superconductor(string _name, const Parent &_parent) : Engimon(_name, "Superconductor", _parent, Electric, Ice)
{
}

CryoCrystallize::CryoCrystallize(string _name) : Engimon(_name, "CryoCrystallize", Ground, Ice)
{
}
CryoCrystallize::CryoCrystallize(string _name, const Parent &_parent) : Engimon(_name, "CryoCrystallize", _parent, Ground, Ice)
{
}