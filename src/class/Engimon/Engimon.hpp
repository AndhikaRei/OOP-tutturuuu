/* List problematematika
 * - method belum lengkap
 * - skill belum pasti
*/

#ifndef ENGIMON_HPP
#define ENGIMON_HPP

#include <iostream>
#include <string>
// #include "../Skill/Skill.hpp"
#include "../Elements/Elements.hpp"

#define NONE -1

using namespace std;

/*--- CLASS PARENT ---*/
class Parent
{
public:
    /* 4 Sekawan, Getter, Setter */
    Parent();
    Parent(string _papaName, string _papaSpecies, string _mamaName, string _mamaSpecies);
    ~Parent();

    /* Methods */
    void showParent();

private:
    string *name;
    string *species;
    bool isParent;
};

/*--- CLASS ENGIMON ---*/
class Engimon
{
protected:
    string name;    // nama engimon
    string species; // spesies engimon
    Parent parent;  // class ortu (papa dan mama)
    int *elements;  // int[2] elements
    string *skill;  // Skill[4] skill (under construction)
    int level;      // level
    int exp;        // exp
    int cumul_exp;  // exp kumulatif

public:
    /* 4 Sekawan, Getter, Setter */
    Engimon(string _name, string _species, int _elmt1, int _elmt2 = NONE);                        // ctor tanpa parent
    Engimon(string _name, string _species, const Parent &_parent, int _elmt1, int _elmt2 = NONE); // ctor dengan parent
    ~Engimon();

    string getName() const;    // get name
    string getSpecies() const; // get species

    /* Methods */
    void levelUp(); // level up engimon
    // I.S. exp div 100 >= 1
    // F.S. exp %= 100, level += exp div 100

    void showEngimon(); // show info engimon
    // I.S. any
    // F.S. menampilkan info engimon ke layar
};

/*--- CLASS SPECIES ---*/
/*--- Fire ---*/
class Pyro : public Engimon
{
public:
    Pyro(string _name);
    Pyro(string _name, const Parent &_parent);
};

/*--- Water ---*/
class Hydro : public Engimon
{
public:
    Hydro(string _name);
    Hydro(string _name, const Parent &_parent);
};

/*--- Electric ---*/
class Electro : public Engimon
{
public:
    Electro(string _name);
    Electro(string _name, const Parent &_parent);
};

/*--- Ground ---*/
class Geo : public Engimon
{
public:
    Geo(string _name);
    Geo(string _name, const Parent &_parent);
};

/*--- Ice ---*/
class Cryo : public Engimon
{
public:
    Cryo(string _name);
    Cryo(string _name, const Parent &_parent);
};

/*--- Fire/Water ---*/
class Vaporize : public Engimon
{
public:
    Vaporize(string _name);
    Vaporize(string _name, const Parent &_parent);
};

/*--- Fire/Electric ---*/
class Overload : public Engimon
{
public:
    Overload(string _name);
    Overload(string _name, const Parent &_parent);
};

/*--- Fire/Ground ---*/
class PyroCrystallize : public Engimon
{
public:
    PyroCrystallize(string _name);
    PyroCrystallize(string _name, const Parent &_parent);
};

/*--- Fire/Ice ---*/
class Melt : public Engimon
{
public:
    Melt(string _name);
    Melt(string _name, const Parent &_parent);
};

/*--- Water/Electric ---*/
class ElectroCharged : public Engimon
{
public:
    ElectroCharged(string _name);
    ElectroCharged(string _name, const Parent &_parent);
};

/*--- Water/Ground ---*/
class HydroCrystallize : public Engimon
{
public:
    HydroCrystallize(string _name);
    HydroCrystallize(string _name, const Parent &_parent);
};

/*--- Water/Ice ---*/
class Frozen : public Engimon
{
public:
    Frozen(string _name);
    Frozen(string _name, const Parent &_parent);
};

/*--- Electric/Ground ---*/
class ElectroCrystallize : public Engimon
{
public:
    ElectroCrystallize(string _name);
    ElectroCrystallize(string _name, const Parent &_parent);
};

/*--- Electric/Ice ---*/
class Superconductor : public Engimon
{
public:
    Superconductor(string _name);
    Superconductor(string _name, const Parent &_parent);
};

/*--- Ground/Ice ---*/
class CryoCrystallize : public Engimon
{
public:
    CryoCrystallize(string _name);
    CryoCrystallize(string _name, const Parent &_parent);
};

#endif