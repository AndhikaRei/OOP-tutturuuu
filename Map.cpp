#include "Map.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

Map::MapElem::MapElem():MapElem(0,0,'x',"xxx"){};

Map::MapElem::MapElem(int x, int y, char sym, string poke){
    this->x = x;
    this->y = y;
    this->symbol = sym;
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
void Map::MapElem::set_string(string poke){
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
            j++;
        } else{
            i++;
            j = 0;
        }
    }
};

Map::Map(const Map&){

};

Map::~Map(){
    for(int i = 0; i<width; i++){
        delete[] mapelem[i];
    }
    delete[] mapelem;
};
        
void Map::printMap(){
    for(int i = 0; i<width; i++){
       for(int j= 0; j<length ; j++){
           cout<<this->mapelem[i][j].get_symbol();
       }
       cout<<endl;
    }
};
