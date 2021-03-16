/* List problematematika
 * 1. skill belom ada
 * 2. kejelasan spesies, jadi atribut atau gausa
 * 3. method belum lengkap
*/

#ifndef ENGIMON_HPP
#define ENGIMON_HPP

#include <iostream>
#include <string>
// #include "Skill.h" ?

using namespace std;

class Engimon
{
public:
    // ctor dtor
    Engimon(string _name, string _parent, string _spesies, string _elmt1, string _elmt2 = NULL);
    ~Engimon();

    // level up engimon
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

/* Spesies dummy */
class Dummy : public Engimon
{
public:
    Dummy(string name, string _parent = "void");
};

/* Spesies dari elemen genshin dan reaksinya */
/*--- Fire ---*/
class Pyro : public Engimon
{
};

/*--- Water ---*/
class Hydro : public Engimon
{
};

/*--- Electric ---*/
class Electro : public Engimon
{
};

/*--- Ground ---*/
class Geo : public Engimon
{
};

/*--- Ice ---*/
class Cryo : public Engimon
{
};

/*--- Fire/Water ---*/
class Vaporize : public Engimon
{
};

/*--- Fire/Electric ---*/
class Overload : public Engimon
{
};

/*--- Fire/Ground ---*/
class PyroCrystallize : public Engimon
{
};

/*--- Fire/Ice ---*/
class Melt : public Engimon
{
};

/*--- Water/Electric ---*/
class ElectroCharged : public Engimon
{
};

/*--- Water/Ground ---*/
class HydroCrystallize : public Engimon
{
};

/*--- Water/Ice ---*/
class Frozen : public Engimon
{
};

/*--- Electric/Ground ---*/
class ElectroCrystallize : public Engimon
{
};

/*--- Electric/Ice ---*/
class Superconductor : public Engimon
{
};

/*--- Ground/Ice ---*/
class CryoCrystallize : public Engimon
{
};

#endif