#include "Map.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <iterator> 
#include <map>
using namespace std;

// Map Elements Class Methods
Map::MapElem::MapElem():MapElem(0,0,'x', false, new Pyro("Pyro sp."),"xxx"){}; //default

Map::MapElem:: MapElem(int x, int y, char symbol, bool exist, Engimon* engi, string type){
    this->x = x;
    this->y = y;
    this->symbol = symbol;
    this->engimonExist = exist;
    this->engimon = engi->clone();
    this->type = type;
};        

// Getters and Setters 
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


// Map Class Methods 
Map::Map(){
    this->length = 0;
    this->width = 0;
    this->total_engimon = 0;
};

// Constructor
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
            // // Fixing bug in isEngimonExist Method;
            // if( i == 0 && j == 0){
            //     mapelem[i][j].set_engimon_exist(true);
            // } else { 
            //     mapelem[i][j].set_engimon_exist(false);
            // }
            
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

// Checking if a position is valid for a pokemon based on the world boundaries and current symbol on the map
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

bool Map::isPlayerPosition(int x, int y) const{
    return (this->player_pos[0]==x) && (this->player_pos[1]==y);
};


void Map::printMap(){
    this->updateMap();
    for(int i = 0; i<width; i++){
        cout <<"                                ";
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
    if(total_engimon <= max_engimon){
        // Check if there is an engimon in the cell
        if(this->mapelem[x][y].isEngimonExist()){
            throw(EngimonExist());
        } 
        // Check if the cell is an valid cell for the species. 
        else if(!isValidEngimonPosition(x, y, species, false)){
            if(species=="Pyro" || species=="Geo" || species=="Electro" || species=="Overload" || species=="PyroCrystallize" || species=="ElectroCrystallize" ){
                throw(InvalidEngimonPositionSea());
            } else if(species=="Hydro" || species=="Cryo" || species=="Frozen"){
                throw(InvalidEngimonPositionGrassland());
            }
        } 
        // Add it to the cell 
        else { 
            Engimon* newEngimon = EngimonFinder(species).front()->clone();
            this->mapelem[x][y].set_engimon_exist(true);
            this->mapelem[x][y].set_engimon(newEngimon);
            this->mapelem[x][y].set_symbol(newEngimon->getEngimonSymbol());
            this->total_engimon++; 
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
    }
    return false;
};

// User Related Methods 
void Map::move(char c){
    if(isAnyActiveEngimon() && isValidEngimonPosition(player_pos[0], player_pos[1], get_active_engimon_species(), true) ){
        if(c == 'w'){
            if(isValidPosition(player_pos[0]-1, player_pos[1], true) && mapelem[player_pos[0]-1][player_pos[1]].isEngimonExist()){
                throw(InvalidPlayerMove());
            }else if(!isValidPosition(player_pos[0]-1, player_pos[1], true)){
                throw(InvalidMoveException());
            }else{
                set_player_pos(this->player_pos[0]-1, this->player_pos[1]);
                set_active_engimon_pos(this->player_pos[0]+1, this->player_pos[1]);
            }
        }else if(c == 'a'){
            if(isValidPosition(player_pos[0], player_pos[1]-1, true) && mapelem[player_pos[0]][player_pos[1]-1].isEngimonExist()){
                throw(InvalidPlayerMove());
            }else if(!isValidPosition(player_pos[0], player_pos[1]-1, true)){
                throw(InvalidMoveException());
            }else{
                set_player_pos(this->player_pos[0], this->player_pos[1]-1);
                set_active_engimon_pos(this->player_pos[0], this->player_pos[1]+1);
            }
        }else if(c == 's'){
            if(isValidPosition(player_pos[0]+1, player_pos[1], true) && mapelem[player_pos[0]+1][player_pos[1]].isEngimonExist()){
                throw(InvalidPlayerMove());
            }else if(!isValidPosition(player_pos[0]+1, player_pos[1], true)){
                throw(InvalidMoveException());
            }else{
                set_player_pos(this->player_pos[0]+1, this->player_pos[1]);
                set_active_engimon_pos(this->player_pos[0]-1, this->player_pos[1]);
            }
        }else if(c == 'd'){
             if(isValidPosition(player_pos[0], player_pos[1]+1, true) && mapelem[player_pos[0]][player_pos[1]+1].isEngimonExist()){
                throw(InvalidPlayerMove());
            }else if(!isValidPosition(player_pos[0], player_pos[1]+1, true)){
                throw(InvalidMoveException());
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

Engimon* Map::getNearbyEnemyEngimon(int* X, int* Y){
    if(isValidPosition(this->player_pos[0]-1, this->player_pos[1], true)){
        if (this->mapelem[this->player_pos[0]-1][this->player_pos[1]].isEngimonExist()){
            *X = this->player_pos[0]-1; *Y =this->player_pos[1];
            return this->mapelem[this->player_pos[0]-1][this->player_pos[1]].get_engimon();
        }
    } 
    if(isValidPosition(this->player_pos[0], this->player_pos[1]-1, true)){
        if (this->mapelem[this->player_pos[0]][this->player_pos[1]-1].isEngimonExist()){
            *X = this->player_pos[0]; *Y =this->player_pos[1]-1;
            return this->mapelem[this->player_pos[0]][this->player_pos[1]-1].get_engimon();
        }
    } 
    if(isValidPosition(this->player_pos[0]+1, this->player_pos[1], true)){
        if (this->mapelem[this->player_pos[0]+1][this->player_pos[1]].isEngimonExist()){
            *X = this->player_pos[0]+1; *Y =this->player_pos[1];
            return this->mapelem[this->player_pos[0]+1][this->player_pos[1]].get_engimon();
        }
    } 
    if(isValidPosition(this->player_pos[0], this->player_pos[1]+1, true)){
        if (this->mapelem[this->player_pos[0]][this->player_pos[1]+1].isEngimonExist()){
            *X = this->player_pos[0]; *Y =this->player_pos[1]+1;
            return this->mapelem[this->player_pos[0]][this->player_pos[1]+1].get_engimon();
        }
    }
    throw InvalidBattleException();
}

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
            } else if(this->isPlayerPosition(i-1, j)){
                throw(InvalidEngimonMoveToPlayer());
            }
        }else if(number==2){
            if(isValidPosition(i, j-1, false)){
                this->moveEngimon(i, j, i, j-1, this->mapelem[i][j].get_engimon()->getSpecies());
            }else if(this->isPlayerPosition(i, j-1)){
                throw(InvalidEngimonMoveToPlayer());
            }
        }else if(number==3){
            if(isValidPosition(i+1, j, false)){
                this->moveEngimon(i, j, i+1, j, this->mapelem[i][j].get_engimon()->getSpecies());
            }else if(this->isPlayerPosition(i+1, j)){
                throw(InvalidEngimonMoveToPlayer());
            }
        } else if(number==4){
            if(isValidPosition(i, j+1, false)){
                this->moveEngimon(i, j, i, j+1, this->mapelem[i][j].get_engimon()->getSpecies());
            }else if(this->isPlayerPosition(i, j+1)){
                throw(InvalidEngimonMoveToPlayer());
            }
        } else{
                    //do nothing
        }
    }      

};

// Move this up later 
int Map::get_total_engimon() const{ return this->total_engimon; };
int Map::get_max_engimon() const{ return this->max_engimon; };

void Map::spawnRandomEngimon(){
    // Works Consistently to spawn pokemon up to at least 120 species 
    // No Level Handling Yet 
    vector<string> Pokemons{
        "Pyro", 
        "Pyro", 
        "Pyro", 
        "Hydro",
        "Hydro",
        "Hydro", 
        "Vaporize", 
        "Overload", 
        "PyroCrystallize", 
        "Melt", 
        "Electro",
        "Electro", 
        "Electro", 
        "ElectroCharged", 
        "HydroCrystallize",
        "Frozen", 
        "Geo",
        "Geo",
        "Geo",
        "ElectroCrystallize", 
        "Superconductor",
        "Cryo",
        "Cryo",
        "Cryo", 
        "CryoCrystallize"
    };

    // The Random Number Generator need a seed invocation outside this function
    int randomNumber = rand() % Pokemons.size();
    Engimon* newEngimon = EngimonFinderWithException(Pokemons[randomNumber]);
    string species = newEngimon->getSpecies();

    // This Logic only Works if the map is the current map
    // Water area Boundaries 
    const int waterStartX = 10;
    const int waterEndX = 19;
    const int waterStartY = 0;
    const int waterEndY = 5;
    int x;
    int y;
    if(species=="Hydro" || species=="Cryo" || species=="Frozen"){
        x = (rand() % (this->length - waterStartX)) + waterStartX;
        y = rand() % (this->width - waterEndY + 1);
    } else {
        y = rand() % (this->width);
        if(y <= waterEndY){
            x = rand() % (this->length - waterStartX);
        } else { 
            x = rand() % (this->length);
        } 
    }   
    int i = 0;
    while ((this->mapelem[y][x].get_symbol()!='-') && (this->mapelem[y][x].get_symbol()!='o')) {
        // Only Generate a random number in the engimon species area. 
        if(species=="Hydro" || species=="Cryo" || species=="Frozen"){
            x = (rand() % (this->length - waterStartX - 1)) + waterStartX;
            y = rand() % (this->width - waterEndY);
        } else {
            y = rand() % (this->width - 1);
            if(y <= waterEndY){
                x = rand() % (this->length - waterStartX - 1);
            } else { 
                x = rand() % (this->length - 1);
            } 
        }    
        // if ( i == 20){
        //     break;
        // }
        // i++;
    }
    this->addEngimon(y, x, Pokemons[randomNumber]);
}