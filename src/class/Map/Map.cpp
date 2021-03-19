#include "Map.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
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
    this->player_pos[1] = 0;
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

bool Map::isValidPosition(int x, int y){
    return (x<this->width && x>=0 && y >=0 && y<this->length);
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
};

void Map::randomMoveAllEngimon(){
    srand (time(NULL));
    for(int i = 0; i<width; i++){
        for(int j= 0; j<length ; j++){
            if(this->mapelem[i][j].isEngimonExist()){
                int number =rand() % 5;
                try{
                    if(number==1){
                        this->moveEngimon(i, j, i-1, j, this->mapelem[i][j].get_engimon()->getSpecies());
                    }else if(number==2){
                        this->moveEngimon(i, j, i, j-1, this->mapelem[i][j].get_engimon()->getSpecies());
                    }else if(number==3){
                        this->moveEngimon(i, j, i+1, j, this->mapelem[i][j].get_engimon()->getSpecies());
                    } else if(number==4){
                        this->moveEngimon(i, j, i, j+1, this->mapelem[i][j].get_engimon()->getSpecies());
                    } else{
                        //do nothing
                    }
                }catch(WriteException &e){
                    cout <<e.what() << endl;
                }
            }
        }
    }
    
};

void Map::addEngimon(int x, int y, string species){
    if(total_engimon < 11){
        if(!(this->mapelem[x][y].isEngimonExist()) && isValidEngimonPosition(x, y, species)){
            this->mapelem[x][y].set_engimon_exist(true);
            this->mapelem[x][y].set_engimon(EngimonFinder(species).front()->clone());
            this->total_engimon++; 
        } else{
            if(this->mapelem[x][y].isEngimonExist()){
                throw(EngimonExist());
            } else{
                throw(InvalidEngimonPosition());
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
    if(this->isValidEngimonPosition(x2, y2, species)){
        try{
            removeEngimon(x1, y1);
            addEngimon(x2, y2, species);
        } catch(WriteException &e){
            cout <<e.what() << endl;
        }
    }else{
        throw(InvalidEngimonMove());
    }
};

bool Map::isValidEngimonPosition(int x, int y, string species){
    if(!this->mapelem[x][y].isEngimonExist() && isValidPosition(x, y)){
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
    //try{
        if(c == 'w'){
            set_player_pos(this->player_pos[0]-1, this->player_pos[1]);
        }else if(c == 'a'){
            set_player_pos(this->player_pos[0], this->player_pos[1]-1);
        }else if(c == 's'){
            set_player_pos(this->player_pos[0]+1, this->player_pos[1]);
        }else if(c == 'd'){
            set_player_pos(this->player_pos[0], this->player_pos[1]+1);
        }
        if(this->mapelem[this->player_pos[0]][this->player_pos[1]].isEngimonExist()){
            this->mapelem[this->player_pos[0]][this->player_pos[1]].get_engimon()->interact();
        }
        this->randomMoveAllEngimon();
        this->printMap();

    /*} catch(int i){
        cout<<"Anda tidak bisa bergerak keluar map"<<endl;
    }*/
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

// bool isPositionValid()