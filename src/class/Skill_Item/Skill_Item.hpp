#ifndef _SKILL_ITEM_HPP_
#define _SKILL_ITEM_HPP_

#include <string>
#include <vector>
#include <iostream>
#include "../Skill/Skill.hpp"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ostream;


class Skill_Item
{
private:
    Skill skill_contained;
    int amount;

    // void delAmount(); // Should be private
public:
    /** 4 SEKAWAN **/
    /* CTOR Default */
    Skill_Item();
    /* CTOR User-Defined */
    Skill_Item(const Skill& skill); // default amount = 1;
    Skill_Item(const Skill& skill, int amount);

    /* CCTOR */
    Skill_Item(const Skill_Item& other);
    /* DTOR */
    // ~Skill_Item();
    /* Operator= */
    Skill_Item& operator=(const Skill_Item& other);

    /** SERVICE **/
    /* learn sebuah skill kepada engimon */
    Skill learn(Elements ele);
    Skill learn(Elements ele, int n);
    Skill learn(int nEle, Elements* listEle);
    Skill learn(vector<Elements> listEle);
    Skill learn(vector<Elements> listEle, int n);
    /* menambah jumlah amount skill_item */
    void addAmount();
    void addAmount(int n);
    
    /* Mengembalikan amount item */
    int getAmount() const;

    // Printer
    void showItem();
    friend ostream& operator<<(ostream& os, Skill_Item& skill_item);

};



#endif