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
    // 4 Sekawan
    // Default CTOR
    Skill();
    // User-Defined CTOR
    Skill(string name, string desc, int basePower, int nElements, Elements* listElements);
    // Skill(string name, string desc, int basePower, Elements el1, Elements el2);
    // Skill(string name, string desc, int basePower, Elements el1, Elements el2, Elements el3);
    // Skill(string name, string desc, int basePower, Elements el1, Elements el2, Elements el3, Elements el4);
    // Skill(string name, string desc, int basePower, Elements el1, Elements el2, Elements el3, Elements el4, Elements el5);
    Skill(string name, string desc, int basePower, vector<Elements> listElements);
    // CCTOR
    Skill(const Skill& other);
    // DTOR
    // ~Skill();
    // Operator=
    Skill& operator=(const Skill& other);

    // Service
    void levelUp();
    void levelUp(int up);
    int totalDamage();
    bool isElementCompatible(Elements ele);
    bool isElementCompatible(int nElements, Elements* listElements);
    bool isElementCompatible(vector<Elements> listEle);

    // Printer
    void printAll();
    friend ostream& operator<<(ostream& os, const Skill& skill);

    // Getter
    string getName();
    string getDesc();
    int getBasePower();
    int getMasteryLevel();
    vector<Elements> getListElements();
    
};






#endif