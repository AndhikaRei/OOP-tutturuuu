//class player
//file player.hpp
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream> 
#include <vector> 
#include <string>
//#include "../Exception/Exception.hpp"
//#include "../Item/Item.hpp"
#include "../Engimon/Engimon.hpp"
using namespace std; 

class player {
    public:
        string name;
        int exp;
        vector<Engimon *> engimons;
        //vector<item *> items;

};

#endif