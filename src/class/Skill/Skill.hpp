#ifndef _SKILL_HPP_
#define _SKILL_HPP_

#include <string>
#include <iostream>

using namespace std;

class Skill
{
private:
    string name;        // Nama skill
    string desc;        // Deskripsi suatu skill
    int basePower;      // Base Power
    int masteryLevel;   // Masteri Level

    Elements* elements;      // Elemen yang bisa mempelajari (char/int)
    int nElements;      // Jumlah elemen skill
    
    // Kapan masteryLevel naik?
public:
    // 4 Sekawan
    // Default CTOR
    Skill();
    // User-Defined CTOR
    Skill(string name, int basePower, int nElements, int* elements);
    ~Skill();
};

Skill::Skill(/* args */)
{
}

Skill::~Skill()
{
}






#endif