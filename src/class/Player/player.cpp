#include "player.hpp"
#include "../Engimon/Engimon.hpp"
#include "../Skill_Item/Skill_Item.hpp"
#include <iostream> 
#include <vector> 
#include <string>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

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
    for(int i = 0;i<this->items.size();i++){
        this->items[i]->showItem();
    }
}

vector<Engimon *> player::getEngimons(){
    return this->engimons;
}
Engimon* player::getEngimon(int i){
    return this->engimons[i];
}
void player::printEngimon(){// nunggu implementasi yg lain
    cout << "this is all your engimons : \n";
    
    for(int i = 0; i< this->engimons.size();i++){
        this->engimons[i]->showEngimon();
    }
}

Engimon* player::getActiveEngimon(){
    if(ActiveEngimon == NULL){
        throw "Belum ada Active Engimon";
    }
    return this->ActiveEngimon; 
}
void player::changeActiveEngimon(int i){
    this->ActiveEngimon = this->engimons[i];
}

void player::printProfile(){
    cout << "Name : " << this->name << endl;
    printEngimon();
    printInventory();
}
int player::getCount(){
    return this->engimons.size() + this->items.size();
}


void player::printInventory(){
	cout << "this is all your Inventory : \n";
    for(int i = 0; i< this->items.size();i++){
        this->items[i]->showItem();
    }
}
//modify data
//
void player::addEngimon(Engimon* engimon){//belum diimplementasiin
   if(this->getCount() >= 100){
       throw "Inventory Penuh";
   }
   Engimon *temp = engimon->clone();
   this->engimons.push_back(engimon);
}
void player::addItem(Skill_Item *item){ //belum diimplementasiin
    if(this->getCount() >= 100){
        throw "Inventory Penuh";
    }
    int found = 0;
    int i = 0;
    while(!found && i < this->items.size()){
        if(this->items[i]->getSkill().getName() == item->getSkill().getName()){
            this->items[i]->addAmount();
            found = true;
            break;
        }
        i++;
    }
    if(!found){
        this->items.push_back(item);
    }
    
}
