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

Player::Player(){
    this->name = "";
    //vector<Engimon *> engimons;
    //vector<Skill_Item *> items;
}

Player::Player(string name_){
    this->name = name_; // masi salah
    //strcpy(this->name,name_);
}

Player::Player(const Player& other){
    this->name = other.name;
    for(int i = 0;i < other.items.size(); ++i){
        this->items[i] = other.items[i]; //gtw dah dibikin atau belum di items
    }
    for(int i = 0;i < other.engimons.size(); ++i){
        this->engimons[i] = other.engimons[i]; //gtw dah dibikin atau belum di items
    }
}
Player::~Player(){
    
}

Player& Player::operator=(const Player& other){
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
vector<Skill_Item *> Player::getItems(){
    return this->items;
}
Skill_Item* Player::getItem(int i){
    return this->items[i];
}
void Player::printItems(){ // nunggu implementasi yg lain
    for(int i = 0;i<this->items.size();i++){
        this->items[i]->showItem();
    }
}

vector<Engimon *> Player::getEngimons(){
    return this->engimons;
}
Engimon* Player::getEngimon(int i){
    return this->engimons[i];
}
void Player::printEngimon(){// nunggu implementasi yg lain
    cout << "this is all your engimons : \n";
    
    for(int i = 0; i< this->engimons.size();i++){
        this->engimons[i]->showEngimon();
    }
}

Engimon* Player::getActiveEngimon(){
    if(ActiveEngimon == NULL){
        throw "Belum ada Active Engimon";
    }
    return this->ActiveEngimon; 
}
void Player::changeActiveEngimon(int i){
    this->ActiveEngimon = this->engimons[i];
}

void Player::printProfile(){
    cout << "Name : " << this->name << endl;
    printEngimon();
    printInventory();
}
int Player::getCount(){
    return this->engimons.size() + this->items.size();
}


void Player::printInventory(){
	cout << "this is all your Inventory : \n";
    for(int i = 0; i< this->items.size();i++){
        this->items[i]->showItem();
    }
}
//modify data
//
void Player::addEngimon(Engimon* engimon){//belum diimplementasiin
   if(this->getCount() >= 100){
       throw "Inventory Penuh";
   }
   Engimon *temp = engimon->clone();
   this->engimons.push_back(engimon);
}
void Player::addItem(Skill_Item *item){ //belum diimplementasiin
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
