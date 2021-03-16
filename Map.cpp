#include "Map.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

Map::MapElem::MapElem():MapElem(0,0,'x',"space","xxx"){};

Map::MapElem::MapElem(int x, int y, char sym, string type, string poke){
    this->x = x;
    this->y = y;
    this->symbol = sym;
    this->type = type;
    this->pokemon = poke;
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
void Map::MapElem::set_pokemon(string poke){
    this->pokemon = poke;
};
string Map::MapElem::get_pokemon() const{
    return this->pokemon;
};

Map::Map(){
    this->length = 0;
    this->width = 0;
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
        
void Map::printMap(){
    for(int i = 0; i<width; i++){
       for(int j= 0; j<length ; j++){
           cout<<this->mapelem[i][j].get_symbol();
       }
       cout<<endl;
    }
};

void Map::move(char c){
    try{
        if(c == 'w'){
            set_player_pos(this->player_pos[0]-1, this->player_pos[1]);
        }else if(c == 'a'){
            set_player_pos(this->player_pos[0], this->player_pos[1]-1);
        }else if(c == 's'){
            set_player_pos(this->player_pos[0]+1, this->player_pos[1]);
        }else if(c == 'd'){
            set_player_pos(this->player_pos[0], this->player_pos[1]+1);
        }
        this->printMap();
    } catch(int i){
        cout<<"Anda tidak bisa bergerak keluar map"<<endl;
    }
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
        throw(-1);
    }
};

int* Map::get_player_pos() const{
    return this->player_pos;
};