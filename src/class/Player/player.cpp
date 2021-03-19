#include "player.hpp"
#include "../Engimon/Engimon.hpp"
#include "../Skill_Item/Skill_Item.hpp"
#include <iostream> 
#include <vector> 
#include <string>

player::player(){
    this->name = "";
    //vector<Engimon *> engimons;
    //vector<Skill_Item *> items;
}

player::player(string name_){
    this->name = name_; // masi salah
    //strcpy(this->name,name_);
}

player::player(const player& other){
    this->name = other.name;
    for(int i = 0;i < other.items.size(); ++i){
        this->items[i] = other.items[i]; //gtw dah dibikin atau belum di items
    }
    for(int i = 0;i < other.engimons.size(); ++i){
        this->engimons[i] = other.engimons[i]; //gtw dah dibikin atau belum di items
    }
}

player& player::operator=(const player& other){
    //strcpy(this->name,other.name);
    this->name = other.name; // masi salah
    for(int i = 0;i < other.items.size(); ++i){
        this->items[i] = other.items[i]; //gtw dah dibikin atau belum di items
    }
    for(int i = 0;i < other.engimons.size(); ++i){
        this->engimons[i] = other.engimons[i]; //gtw dah dibikin atau belum di items
    }
    
    return *this;
}

//selector
vector<Skill_Item *> player::getItems(){
    return this->items;
}
Skill_Item* player::getItem(int i){
    return this->items[i];
}
void player::printItems(){ // nunggu implementasi yg lain
    
}

vector<Engimon *> player::getEngimons(){
    return this->engimons;
}
Engimon* player::getEngimon(int i){
    return this->engimons[i];
}
void player::printEngimon(){// nunggu implementasi yg lain

}

int player::getCount(){
    return this->engimons.size() + this->items.size();
}


void player::printInventory(){

}
//modify data
void player::addEngimon(Engimon engimon){//belum diimplementasiin
    if(this->getCount() >= 100){
        throw "Inventory Penuh";
    }
}
void player::addItem(Skill_Item item){ //belum diimplementasiin
    if(this->getCount() >= 100){
        throw "Inventory Penuh";
    }
}
