#include "Engimon.hpp"

using namespace std;

// user-defined ctor
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
}

// dtor
Engimon::~Engimon()
{
    delete[] elements;
    delete[] skill;
}

// level up engimon
void Engimon::levelUp()
{
}

// lihat info engimon
void Engimon::showInfo()
{
    cout << "Name                  : " << name << '\n';
    cout << "Parent Name           : " << parent << '\n';
    cout << "Species               : " << species << '\n';
    cout << "Element(s)            : [" << elements[0] << "] [" << elements[1] << "]\n";
    cout << "Level                 : " << level << '\n';
    cout << "Experience            : " << exp << '\n';
    cout << "Cumulative Experience : " << cumul_exp << endl;
}

Dummy::Dummy(string _name, string _parent) : Engimon(_name, _parent, "Dummy", "Dark", "Light")
{
}
