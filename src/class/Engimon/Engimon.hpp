/* List problematematika
 * - kejelasan spesies, jadi atribut atau gausah
 * - method belum lengkap
 * - skill belum pasti
 * - elements belum pasti
*/

#ifndef ENGIMON_HPP
#define ENGIMON_HPP

#include <iostream>
#include <string>
// #include "../Skill/Skill.hpp"
// #include "../Elements/Elements.hpp"

#define NONE "none"

using namespace std;

class Engimon
{
public:
    // ctor dtor
    Engimon(string _name, string _parent, string _spesies, string _elmt1, string _elmt2 = NONE);
    ~Engimon();

    // level up engimon
    // I.S. exp div 100 >= 1
    // F.S. exp %= 100, level += exp div 100
    void levelUp();

    // show info engimon
    void showInfo();
    // virtual void showInfo() = 0;

protected:
    string name;      // nama engimon
    string parent;    // nama ortu
    string species;   // butuh ga ya?
    string *elements; // char[2] element
    string *skill;    // Skill[4] skill
    int level;        // level
    int exp;          // exp
    int cumul_exp;    // exp kumulatif
};

/* Spesies dari elemen genshin dan reaksinya */
/*--- Fire ---*/
class Pyro : public Engimon
{
public:
    Pyro(string name, string _parent = "-");
};

/*--- Water ---*/
class Hydro : public Engimon
{
public:
    Hydro(string name, string _parent = "-");
};

/*--- Electric ---*/
class Electro : public Engimon
{
public:
    Electro(string name, string _parent = "-");
};

/*--- Ground ---*/
class Geo : public Engimon
{
public:
    Geo(string name, string _parent = "-");
};

/*--- Ice ---*/
class Cryo : public Engimon
{
public:
    Cryo(string name, string _parent = "-");
};

/*--- Fire/Water ---*/
class Vaporize : public Engimon
{
public:
    Vaporize(string name, string _parent = "-");
};

/*--- Fire/Electric ---*/
class Overload : public Engimon
{
public:
    Overload(string name, string _parent = "-");
};

/*--- Fire/Ground ---*/
class PyroCrystallize : public Engimon
{
public:
    PyroCrystallize(string name, string _parent = "-");
};

/*--- Fire/Ice ---*/
class Melt : public Engimon
{
public:
    Melt(string name, string _parent = "-");
};

/*--- Water/Electric ---*/
class ElectroCharged : public Engimon
{
public:
    ElectroCharged(string name, string _parent = "-");
};

/*--- Water/Ground ---*/
class HydroCrystallize : public Engimon
{
public:
    HydroCrystallize(string name, string _parent = "-");
};

/*--- Water/Ice ---*/
class Frozen : public Engimon
{
public:
    Frozen(string name, string _parent = "-");
};

/*--- Electric/Ground ---*/
class ElectroCrystallize : public Engimon
{
public:
    ElectroCrystallize(string name, string _parent = "-");
};

/*--- Electric/Ice ---*/
class Superconductor : public Engimon
{
public:
    Superconductor(string name, string _parent = "-");
};

/*--- Ground/Ice ---*/
class CryoCrystallize : public Engimon
{
public:
    CryoCrystallize(string name, string _parent = "-");
};

#endif