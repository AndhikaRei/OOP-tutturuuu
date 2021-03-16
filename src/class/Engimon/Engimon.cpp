#include "Engimon.hpp"

using namespace std;

// Class Engimon
Engimon::Engimon(string _name, string _parent, string _species, string _elmt1, string _elmt2)
{
    this->name = _name;
    this->parent = _parent;
    this->species = _species;
    this->elements = new string[2];
    this->elements[0] = _elmt1;
    this->elements[1] = _elmt2;
    this->skill = new string[4];
    this->level = 0;
    this->exp = 0;
    this->cumul_exp = 0;
    showInfo();
}
Engimon::~Engimon()
{
    delete[] elements;
    delete[] skill;
}
void Engimon::levelUp()
{
    this->exp %= 100;
    this->level += exp / 100;
}
void Engimon::showInfo()
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Name                  : " << name << '\n';
    cout << "Parent Name           : " << parent << '\n';
    cout << "Species               : " << species << '\n';
    cout << "Element(s)            : [" << elements[0] << "]";
    if (elements[1] != NONE)
    {
        cout << "[" << elements[1] << "]";
    }
    cout << endl;
    cout << "Level                 : " << level << '\n';
    cout << "Experience            : " << exp << '\n';
    cout << "Cumulative Experience : " << cumul_exp << endl;
}

Pyro::Pyro(string _name, string _parent) : Engimon(_name, _parent, "Pyro", "Fire")
{
}

Hydro::Hydro(string _name, string _parent) : Engimon(_name, _parent, "Hydro", "Water")
{
}

Electro::Electro(string _name, string _parent) : Engimon(_name, _parent, "Electro", "Electric")
{
}

Geo::Geo(string _name, string _parent) : Engimon(_name, _parent, "Geo", "Ground")
{
}

Cryo::Cryo(string _name, string _parent) : Engimon(_name, _parent, "Cryo", "Ice")
{
}

Vaporize::Vaporize(string _name, string _parent) : Engimon(_name, _parent, "Vaporize", "Fire", "Water")
{
}

Overload::Overload(string _name, string _parent) : Engimon(_name, _parent, "Overload", "Fire", "Electric")
{
}

PyroCrystallize::PyroCrystallize(string _name, string _parent) : Engimon(_name, _parent, "PyroCrystallize", "Fire", "Ground")
{
}

Melt::Melt(string _name, string _parent) : Engimon(_name, _parent, "Melt", "Fire", "Ice")
{
}

ElectroCharged::ElectroCharged(string _name, string _parent) : Engimon(_name, _parent, "ElectroCharged", "Water", "Electric")
{
}
HydroCrystallize::HydroCrystallize(string _name, string _parent) : Engimon(_name, _parent, "HydroCrystallize", "Water", "Ground")
{
}

Frozen::Frozen(string _name, string _parent) : Engimon(_name, _parent, "Frozen", "Water", "Ice")
{
}

ElectroCrystallize::ElectroCrystallize(string _name, string _parent) : Engimon(_name, _parent, "ElectroCrystallize", "Electric", "Ground")
{
}

Superconductor::Superconductor(string _name, string _parent) : Engimon(_name, _parent, "Superconductor", "Electric", "Ice")
{
}

CryoCrystallize::CryoCrystallize(string _name, string _parent) : Engimon(_name, _parent, "CryoCrystallize", "Ground", "Ice")
{
}