#ifndef ENGIMON_HPP
#define ENGIMON_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include "../Skill/Skill.hpp"
#include "../Elements/Elements.hpp"
#include "../Skill_Item/Skill_Item.hpp"
#include "../Exception/Exception.hpp"

using std::cout;
using std::endl;
using std::map;
using std::multimap;
using std::string;
using std::vector;

/*--- CLASS PARENT ---*/
class Parent
{
private:
    vector<string> name;    // nama papa[0] mama[1]
    vector<string> species; // spesies papa [0] mama [1]
    bool isParent;          // return true jika engimon punya parent

public:
    /* 4 Sekawan, Getter, Setter */
    Parent();
    Parent(string _papaName, string _papaSpecies, string _mamaName, string _mamaSpecies);
    Parent(const Parent&);
    // dtor tak perlu   

    /* Methods */
    void showParent();
};

/*--- CLASS ENGIMON ---*/
class Engimon
{
protected:
    string name;               // nama engimon
    string species;            // spesies engimon
    Parent parent;             // class ortu (papa dan mama)
    vector<Elements> elements; // int[2] elements
    vector<Skill> skill;       // Skill[4] skill
    int level;                 // level
    int exp;                   // exp
    int cumul_exp;             // exp kumulatif
    string slogan;             // slogan engimon, 1 dulu, more slogan belakangan

public:
    /* 4 Sekawan, Getter, Setter */
    Engimon(string _name, string _species, Elements _elmt1, Elements _elmt2 = NONE);                        // ctor tanpa parent
    Engimon(string _name, string _species, const Parent &_parent, Elements _elmt1, Elements _elmt2 = NONE); // ctor dengan parent
    virtual Engimon *clone() = 0;                                                                           // cctor
    // dtor tak perlu

    string getName() const;               // get name
    string getSpecies() const;            // get species
    Parent getParent() const;             // get parent
    vector<Elements> getElements() const; // get elements
    vector<Skill> getSkill() const;       // get skill
    int getLevel() const;                 // get level
    int getExp() const;                   // get exp
    int getCumulExp() const;              // get cumul_exp
    void setName(string name);

    void rename(string _name);             // set name
    void setParent(const Parent &_parent); // set parent

    /* Methods */
    bool isOneElement() const;
    // return true jika engimon hanya 1 elemen

    bool isElement(Elements _ele);
    // return true jika element compatible

    void addExp(int _exp); // menambahkan exp
    // I.S. any
    // F.S. exp += _exp

    void addSkill(Skill);
    void addSkill(Skill_Item &);
    // void addSkill(Skill_Item &, int);
    // I.S. any
    // F.S. add skill to Engimon

    void levelUp(); // level up engimon
    // I.S. exp >= 100
    // F.S. exp %= 100, level += exp div 100

    void showEngimon() const; // show info engimon secara pendek
    // I.S. any
    // F.S. menampilkan info engimon ke layar

    void showEngimonComplete() const; // show info engimon secara lengkap
    // I.S. any
    // F.S. menampilkan info engimon ke layar

    void showEngimonEngidex() const; // show info engimon secara umum (tanpa exp)
    // I.S. any
    // F.S. menampilkan info engimon ke layar

    void interact() const;
    // I.S. any
    // F.S. menampilkan hasil interact engimon ke layar

    bool skillLevelUp(Skill sk);
    bool skillLevelUp(Skill sk, int lv);
    // return true jika berhasil level up skill

    char getEngimonSymbol();
    // return symbol based on species

    /* Service Breeding */
    friend Engimon &breeding(Engimon &parent_a, Engimon &parent_b);
};

/*--- CLASS SPECIES ---*/
/*--- Fire ---*/
class Pyro : public Engimon
{
public:
    Pyro(string _name);
    Pyro(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- Water ---*/
class Hydro : public Engimon
{
public:
    Hydro(string _name);
    Hydro(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- Electric ---*/
class Electro : public Engimon
{
public:
    Electro(string _name);
    Electro(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- Ground ---*/
class Geo : public Engimon
{
public:
    Geo(string _name);
    Geo(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- Ice ---*/
class Cryo : public Engimon
{
public:
    Cryo(string _name);
    Cryo(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- Fire/Water ---*/
class Vaporize : public Engimon
{
public:
    Vaporize(string _name);
    Vaporize(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- Fire/Electric ---*/
class Overload : public Engimon
{
public:
    Overload(string _name);
    Overload(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- Fire/Ground ---*/
class PyroCrystallize : public Engimon
{
public:
    PyroCrystallize(string _name);
    PyroCrystallize(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- Fire/Ice ---*/
class Melt : public Engimon
{
public:
    Melt(string _name);
    Melt(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- Water/Electric ---*/
class ElectroCharged : public Engimon
{
public:
    ElectroCharged(string _name);
    ElectroCharged(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- Water/Ground ---*/
class HydroCrystallize : public Engimon
{
public:
    HydroCrystallize(string _name);
    HydroCrystallize(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- Water/Ice ---*/
class Frozen : public Engimon
{
public:
    Frozen(string _name);
    Frozen(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- Electric/Ground ---*/
class ElectroCrystallize : public Engimon
{
public:
    ElectroCrystallize(string _name);
    ElectroCrystallize(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- Electric/Ice ---*/
class Superconductor : public Engimon
{
public:
    Superconductor(string _name);
    Superconductor(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- Ground/Ice ---*/
class CryoCrystallize : public Engimon
{
public:
    CryoCrystallize(string _name);
    CryoCrystallize(string _name, const Parent &_parent);
    Engimon *clone();
};

/*--- MISC ---*/
extern map<string, Engimon *> Engidex;

void initEngidex();
void printEngidex();
string generalParentSpecies(string element);
Engimon* EngimonFinderWithException(string _species);
vector<Engimon *> EngimonFinder(string _species);
vector<Engimon *> EngimonFinder(Elements _e1, Elements _e2 = NONE);

#endif