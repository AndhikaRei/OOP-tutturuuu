#ifndef _SKILL_HPP_
#define _SKILL_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "../Elements/Elements.hpp"
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ostream;


class Skill
{
private:
    string name;        // Nama skill
    string desc;        // Deskripsi suatu skill
    int basePower;      // Base Power
    int masteryLevel;   // Masteri Level

    vector<Elements> listElements;     // Elemen yang bisa mempelajari (jenis elemen skill) (Pake vector aja?)
    // int nElements;              // Jumlah elemen yang dimiliki
    // Kapan masteryLevel naik?
public:
    /** 4 SEKAWAN **/
    // Default CTOR
    Skill();
    // User-Defined CTOR
    Skill(string name, string desc, int basePower, Elements Elements1, Elements Elements2=NONE,Elements Elements3=NONE,Elements Elements4=NONE,Elements Elements5=NONE);
    Skill(string name, string desc, int basePower, int nElements, Elements* listElements);
    Skill(string name, string desc, int basePower, vector<Elements> listElements);
    // CCTOR
    Skill(const Skill& other);
    // DTOR
    // ~Skill();
    // Operator=
    Skill& operator=(const Skill& other);

    // Operator==
    bool operator==(const Skill& other);

    /** SERVICE **/
    /* Menaikan mastery level */
    void levelUp();
    void levelUp(int up);
    /* Menghitung total damage yang dihasilkan skill */
    int totalDamage();
    
    /* Mengecek apakah suatu element sesuai dengan skill */
    bool isElementCompatible(Elements ele);
    bool isElementCompatible(int nElements, Elements* listElements);
    bool isElementCompatible(vector<Elements> listEle);

    /* Printer */
    void showSkill();
    void showSimpleSkill();
    
    friend ostream& operator<<(ostream& os, const Skill& skill);

    /* Getter */
    string getName() const;
    string getDesc() const;
    int getBasePower() const;
    int getMasteryLevel() const;
    vector<Elements> getListElements() const;
    
};


extern vector<Skill> databaseSkill;

void databaseSkillInitialization();





#endif