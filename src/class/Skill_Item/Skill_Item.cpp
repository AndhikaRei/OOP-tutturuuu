#include "Skill_Item.hpp"

/** 4 SEKAWAN **/
/* CTOR Default */
Skill_Item::Skill_Item(): 
    skill_contained() 
{
    amount = 0;
}

/* CTOR User-Defined */
Skill_Item::Skill_Item(const Skill& skill): 
    skill_contained(skill) 
{
    this->amount = 1;
}

Skill_Item::Skill_Item(const Skill& skill, int amount): 
    skill_contained(skill) 
{
    this->amount = amount;
}

/* CCTOR */
Skill_Item::Skill_Item(const Skill_Item& other)
{
    this->skill_contained = other.skill_contained;
    this->amount = other.amount;
}

/* DTOR */
// ~Skill_Item();

/* Operator= */
Skill_Item& Skill_Item::operator=(const Skill_Item& other) 
{
    this->skill_contained = other.skill_contained;
    this->amount = other.amount;
    return *this;
}

/** SERVICE **/
/* learn sebuah skill kepada engimon */
Skill Skill_Item::getSkill(){
    // Mengembalikan skill yang tersedia dalam skill item
    return this->skill_contained;
}
Skill Skill_Item::learn(Elements ele) {
    // Mempelajari skill item
    if (skill_contained.isElementCompatible(ele)) {
        if (amount > 0) {
            amount--;
            return skill_contained;
        } else {
            throw InvalidNotEnoughItemAmount();
        }
    } else {    // Kasus elemen tidak sesuai
        throw InvalidElementNotCompatible();
    }    
}

// Skill Skill_Item::learn(Elements ele, int n) {
//     if (skill_contained.isElementCompatible(ele)) {
//         if (amount - n >= 0) {
//             amount -= n;
//             return skill_contained;
//         } else {
//             throw InvalidNotEnoughItemAmount();
//         }
//     } else {    // Kasus elemen tidak sesuai
//         throw InvalidElementNotCompatible();
//     }
// }

Skill Skill_Item::learn(int nEle, Elements* listEle) {
    // Mempelajari skill item
    if (skill_contained.isElementCompatible(nEle,listEle)) {
        if (amount > 0) {
            amount--;
            return skill_contained;
        } else {
            throw InvalidNotEnoughItemAmount();
        }
    } else {    // Kasus elemen tidak sesuai
        throw InvalidElementNotCompatible();
    } 
}

Skill Skill_Item::learn(vector<Elements> listEle) {
    // Mempelajari skill item
    if (skill_contained.isElementCompatible(listEle)) {
        if (amount > 0) {
            amount--;
            return skill_contained;
        } else {
            throw InvalidNotEnoughItemAmount();
        }
    } else {    // Kasus elemen tidak sesuai
        throw InvalidElementNotCompatible();
    } 
}

// Skill Skill_Item::learn(vector<Elements> listEle, int n) {
//     if (skill_contained.isElementCompatible(listEle)) {
//         if (amount - n >= 0) {
//             amount -= n;
//             return skill_contained;
//         } else {
//             throw InvalidElementNotCompatible();
//         }
//     } else {    // Kasus elemen tidak sesuai
//         throw InvalidElementNotCompatible();
//     } 
// }

/* menambah jumlah amount skill_item */
void Skill_Item::addAmount() {
    // Menambah jumlah skill item
    amount++;
}

void Skill_Item::addAmount(int n) {
    // Menambah jumlah skill item
    amount += n;
}

/* Mengembalikan amount item */
int Skill_Item::getAmount() const {
    // Menambah jumlah skill item
    return amount;
}

// Printer
void Skill_Item::showItem() {
    skill_contained.showSkill();
    cout << "Amounts      : " << amount << endl;
}
void Skill_Item::showSimpleItem() {
    skill_contained.showSimpleSkill();
    cout << "Amounts  : " << amount << endl;
}

ostream& operator<<(ostream& os, Skill_Item& skill_item) {
    os << skill_item.skill_contained;
    os << "Amounts      : " << skill_item.amount;
    return os;
}
