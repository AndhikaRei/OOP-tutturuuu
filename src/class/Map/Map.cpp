#include "Map.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <iterator> 
#include <map>
using namespace std;

Map::MapElem::MapElem():MapElem(0,0,'x', false, new Pyro("Pyro sp."),"xxx"){}; //default

Map::MapElem:: MapElem(int x, int y, char symbol, bool exist, Engimon* engi, string type){
    this->x = x;
    this->y = y;
    this->symbol = symbol;
    this->engimonExist = exist;
    this->engimon = engi->clone();
    this->type = type;
};        

void Map::MapElem::set_x(int x){
    this->x = x;
};
int Map::MapElem::get_x() const{
    return this->x;
};
void Map::MapElem::set_y(int y){
    this->y = y;
};
int Map::MapElem::get_y() const{
    return this->y;
};
void Map::MapElem::set_symbol(char sym){
    this->symbol = sym;
};
char Map::MapElem::get_symbol() const{
    return this->symbol;
};
void Map::MapElem::set_type(string type){
    this->type = type;
};
string Map::MapElem::get_type() const{
    return this->type;
};
void Map::MapElem::set_engimon(Engimon* engimon){
    this->engimon = engimon->clone();
};
Engimon* Map::MapElem::get_engimon() const{
    return this->engimon->clone();
};
void Map::MapElem::set_engimon_exist(bool status){
    this->engimonExist = status;
};
bool Map::MapElem::isEngimonExist() const{
    return this->engimonExist;
};

Map::Map(){
    this->length = 0;
    this->width = 0;
    this->total_engimon = 0;
};

Map::Map(int m, int n, string txt){
    int i, j;
    this->length = m;
    this->width = n;
    this->mapelem = new MapElem*[width];
    for(i = 0; i<width; i++){
        mapelem[i] = new MapElem[length];
    }
    char ch;
    ifstream infile(txt);
    i = 0;
    j = 0;
    while(infile.get(ch)){
        if(ch != '\n'){
            mapelem[i][j].set_x(i);
            mapelem[i][j].set_y(j);
            mapelem[i][j].set_symbol(ch);
            if(i<6 && j>9){
                mapelem[i][j].set_type("sea");
            } else{
                mapelem[i][j].set_type("grassland");
            }
            j++;
        } else{
            i++;
            j = 0;
        }
    }
    this->player_pos = new int[2];
    this->player_pos[0] = 0;
    this->player_pos[1] = 1;
    this->active_engimon_pos = new int[2];
    this->active_engimon_pos[0] = 0;
    this->active_engimon_pos[1] = 0;
    this->active_engimon_species = "Pyro";
    this->mapelem[player_pos[0]][player_pos[1]].set_symbol('P');
    this->total_engimon = 0;
};

Map::Map(const Map&){

};

Map::~Map(){
    for(int i = 0; i<width; i++){
        delete[] mapelem[i];
    }
    delete[] mapelem;
    delete[] player_pos;
};

bool Map::isValidPosition(int x, int y, bool isActive){
    if(isActive){
        return ((x<this->width && x>=0 && y >=0 && y<this->length));
    } else{
        return ((x<this->width && x>=0 && y >=0 && y<this->length) && (this->mapelem[x][y].get_symbol()=='-' || this->mapelem[x][y].get_symbol()=='o'));
    }
    
};

bool Map::isAnyActiveEngimon() const{
    return this->active_engimon_species != "undefined";
};

void Map::printMap(){
    this->updateMap();
    for(int i = 0; i<width; i++){
       for(int j= 0; j<length ; j++){
           cout<<this->mapelem[i][j].get_symbol();
       }
       cout<<endl;
    }
};

void Map::updateMap(){
    for(int i = 0; i<width; i++){
        for(int j= 0; j<length ; j++){
            if(this->mapelem[i][j].isEngimonExist() && !(this->player_pos[0] == i && this->player_pos[1] ==j)){
                this->mapelem[i][j].set_symbol(this->mapelem[i][j].get_engimon()->getEngimonSymbol());
            }
        }
    }
    if(this->isAnyActiveEngimon()){
        this->mapelem[active_engimon_pos[0]][active_engimon_pos[1]].set_symbol('X');
    }
    this->mapelem[player_pos[0]][player_pos[1]].set_symbol('P');
};

void Map::randomMoveAllEngimon(){
    map<string, vector<int>> EngimonPos = this->getEngimonPosition();
    srand (time(NULL));
    for (map<string, vector<int>>::iterator it=EngimonPos.begin(); it!=EngimonPos.end(); ++it){
        int number =rand() % 5;
        int i = it->second[0];
        int j = it->second[1];
        if(number==1){
            if(isValidPosition(i-1, j, false)){
                this->moveEngimon(i, j, i-1, j, this->mapelem[i][j].get_engimon()->getSpecies());
            }
        }else if(number==2){
            if(isValidPosition(i, j-1, false)){
                this->moveEngimon(i, j, i, j-1, this->mapelem[i][j].get_engimon()->getSpecies());
            }
        }else if(number==3){
            if(isValidPosition(i+1, j, false)){
                this->moveEngimon(i, j, i+1, j, this->mapelem[i][j].get_engimon()->getSpecies());
            }
        } else if(number==4){
            if(isValidPosition(i, j+1, false)){
                this->moveEngimon(i, j, i, j+1, this->mapelem[i][j].get_engimon()->getSpecies());
            }
        } else{
                    //do nothing
        }
    }      

};

map<string, vector<int>> Map::getEngimonPosition(){
    map<string, vector<int>> result;
    for(int i = 0; i<width; i++){
        for(int j= 0; j<length ; j++){    
            if(this->mapelem[i][j].isEngimonExist()){
                result.insert(pair<string, vector<int>>(this->mapelem[i][j].get_engimon()->getSpecies(), {i, j}));
            }
       }
    }
    return result;
};

void Map::addEngimon(int x, int y, string species){
    if(total_engimon < 11){
        if(!(this->mapelem[x][y].isEngimonExist()) && isValidEngimonPosition(x, y, species, false)){
            this->mapelem[x][y].set_engimon_exist(true);
            this->mapelem[x][y].set_engimon(EngimonFinder(species).front()->clone());
            this->total_engimon++; 
        } else{
            if(this->mapelem[x][y].isEngimonExist()){
                throw(EngimonExist());
            } else{
                if(species=="Pyro" || species=="Geo" || species=="Electro" || species=="Overload" || species=="PyroCrystallize" || species=="ElectroCrystallize" ){
                    throw(InvalidEngimonPositionSea());
                } else if(species=="Hydro" || species=="Cryo" || species=="Frozen"){
                    throw(InvalidEngimonPositionGrassland());
                }
            }
        }
    } else{
        throw(MaximumEngimonReached());
    }

};

void Map::removeEngimon(int x, int y){
    if(this->mapelem[x][y].isEngimonExist()){
        this->mapelem[x][y].set_engimon_exist(false);
        this->mapelem[x][y].set_symbol(this->mapelem[x][y].get_type()=="grassland"?'-': 'o');
        this->total_engimon--; 
    }else{
        throw(NoEngimonFound());
    }
};

void Map::moveEngimon(int x1, int y1, int x2, int y2, string species){
    if(this->isValidEngimonPosition(x2, y2, species, false)){
            removeEngimon(x1, y1);
            addEngimon(x2, y2, species);
    }else{
        // throw(InvalidEngimonMove());
    }
};

bool Map::isValidEngimonPosition(int x, int y, string species, bool isActive){
    if(!this->mapelem[x][y].isEngimonExist() && isValidPosition(x, y, isActive)){
        if(species=="Pyro" || species=="Geo" || species=="Electro" || species=="Overload" || species=="PyroCrystallize" || species=="ElectroCrystallize" ){
            return(this->mapelem[x][y].get_type() == "grassland");
        } else if(species=="Hydro" || species=="Cryo" || species=="Frozen"){
            return(this->mapelem[x][y].get_type() == "sea");
        } else{
            return true;
        }
    }else{
        return false;
    }
};
void Map::move(char c){
    if(isAnyActiveEngimon() && isValidEngimonPosition(player_pos[0], player_pos[1], get_active_engimon_species(), true) ){
        if(c == 'w'){
            if(mapelem[player_pos[0]-1][player_pos[1]].isEngimonExist()){
                throw(InvalidPlayerMove());
            }else{
                set_player_pos(this->player_pos[0]-1, this->player_pos[1]);
                set_active_engimon_pos(this->player_pos[0]+1, this->player_pos[1]);
            }
        }else if(c == 'a' ){
            if(mapelem[player_pos[0]][player_pos[1]-1].isEngimonExist()){
                throw(InvalidPlayerMove());
            }else{
                set_player_pos(this->player_pos[0], this->player_pos[1]-1);
                set_active_engimon_pos(this->player_pos[0], this->player_pos[1]+1);
            }
        }else if(c == 's'){
            if(mapelem[player_pos[0]+1][player_pos[1]].isEngimonExist()){
                throw(InvalidPlayerMove());
            }else{
                set_player_pos(this->player_pos[0]+1, this->player_pos[1]);
                set_active_engimon_pos(this->player_pos[0]-1, this->player_pos[1]);
            }
        }else if(c == 'd'){
             if(mapelem[player_pos[0]][player_pos[1]+1].isEngimonExist()){
                throw(InvalidPlayerMove());
            }else{
                set_player_pos(this->player_pos[0], this->player_pos[1]+1);
                set_active_engimon_pos(this->player_pos[0], this->player_pos[1]-1);
            }
        }
    } else if(isAnyActiveEngimon()){
        string species = this->get_active_engimon_species();
        if(species=="Pyro" || species=="Geo" || species=="Electro" || species=="Overload" || species=="PyroCrystallize" || species=="ElectroCrystallize" ){
            throw(InvalidEngimonPositionSea());
        } else if(species=="Hydro" || species=="Cryo" || species=="Frozen"){
            throw(InvalidEngimonPositionGrassland());
        }
    }else{
        if(c == 'w'){
            set_player_pos(this->player_pos[0]-1, this->player_pos[1]);
        }else if(c == 'a'){
            set_player_pos(this->player_pos[0], this->player_pos[1]-1);
        }else if(c == 's'){
            set_player_pos(this->player_pos[0]+1, this->player_pos[1]);
        }else if(c == 'd'){
            set_player_pos(this->player_pos[0], this->player_pos[1]+1);
        }
    }
    if(this->mapelem[this->player_pos[0]][this->player_pos[1]].isEngimonExist()){
        this->mapelem[this->player_pos[0]][this->player_pos[1]].get_engimon()->interact();
    }
    this->randomMoveAllEngimon();
    this->printMap();
};

void Map::set_player_pos(int x, int y){
    if(x>=0 && x<10 && y>=0 && y<20){
        if(this->mapelem[player_pos[0]][player_pos[1]].get_type() == "grassland"){
            this->mapelem[player_pos[0]][player_pos[1]].set_symbol('-');
        } else{
            this->mapelem[player_pos[0]][player_pos[1]].set_symbol('o');
        }
        this->player_pos[0] = x;
        this->player_pos[1] = y;
        this->mapelem[x][y].set_symbol('P');
    } else{
        throw InvalidMoveException();
    }
};

int* Map::get_player_pos() const{
    return this->player_pos;
};

void Map::set_active_engimon_pos(int x, int y){
    string species = this->active_engimon_species;
    if(isValidEngimonPosition(x, y, species, true)){
        if(this->mapelem[active_engimon_pos[0]][active_engimon_pos[1]].get_type() == "grassland"){
            this->mapelem[active_engimon_pos[0]][active_engimon_pos[1]].set_symbol('-');
        } else{
            this->mapelem[active_engimon_pos[0]][active_engimon_pos[1]].set_symbol('o');
        }
        this->active_engimon_pos[0] = x;
        this->active_engimon_pos[1] = y;
        this->mapelem[x][y].set_symbol('X');
    }else{
        if(species=="Pyro" || species=="Geo" || species=="Electro" || species=="Overload" || species=="PyroCrystallize" || species=="ElectroCrystallize" ){
            throw(InvalidEngimonPositionSea());
        } else if(species=="Hydro" || species=="Cryo" || species=="Frozen"){
            throw(InvalidEngimonPositionGrassland());
        }
    }
};

int* Map::get_active_engimon_pos()const{
    return this->active_engimon_pos;
};

void Map::set_active_engimon_species(string species){
    this->active_engimon_species = species;
};

string Map::get_active_engimon_species()const{
    return this->active_engimon_species;
};

Engimon* Map::getNearbyEnemyEngimon(){
    if(isValidPosition(this->player_pos[0]-1, this->player_pos[1], true)){
        if (this->mapelem[this->player_pos[0]-1][this->player_pos[1]].isEngimonExist())
            return this->mapelem[this->player_pos[0]-1][this->player_pos[1]].get_engimon();
    } 
    if(isValidPosition(this->player_pos[0], this->player_pos[1]-1, true)){
        if (this->mapelem[this->player_pos[0]][this->player_pos[1]-1].isEngimonExist())
            return this->mapelem[this->player_pos[0]][this->player_pos[1]-1].get_engimon();
    } 
    if(isValidPosition(this->player_pos[0]+1, this->player_pos[1], true)){
        if (this->mapelem[this->player_pos[0]+1][this->player_pos[1]].isEngimonExist())
            return this->mapelem[this->player_pos[0]+1][this->player_pos[1]].get_engimon();
    } 
    if(isValidPosition(this->player_pos[0], this->player_pos[1]+1, true)){
        if (this->mapelem[this->player_pos[0]][this->player_pos[1]+1].isEngimonExist())
            return this->mapelem[this->player_pos[0]][this->player_pos[1]+1].get_engimon();
    }
    throw InvalidBattleException();
}
