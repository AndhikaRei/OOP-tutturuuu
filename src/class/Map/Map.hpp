#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <fstream>
#include "../Exception/Exception.hpp"
#include "../Engimon/Engimon.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

class Map{
    private :
        class MapElem{
            private :
                int x;
                int y;
                char symbol;
                bool engimonExist;
                Engimon* engimon;
                string type; //grassland or sea
            public :
                MapElem();
                MapElem(int, int, char, bool, Engimon*, string);
                //cctor tidak perlu
                //assignment operator tidak perlu;
                //dtor tidak perlu;
                void set_x(int);
                int get_x() const;
                void set_y(int);
                int get_y() const;
                void set_symbol(char);
                char get_symbol() const;
                void set_type(string);
                string get_type() const;
                void set_engimon(Engimon*);
                Engimon* get_engimon() const;
                void set_engimon_exist(bool);
                bool isEngimonExist() const;
        };
        int length;
        int width;
        MapElem** mapelem;
        int* player_pos;
        int* active_engimon_pos;
        string active_engimon_species;
        int total_engimon;
    public :
        Map();
        Map(int, int, string);
        Map(const Map&);
        ~Map();
        bool isValidPosition(int, int, bool);
        bool isAnyActiveEngimon() const;

        void printMap();
        void updateMap();
        void randomMoveAllEngimon();
        map<string, vector<int>> getEngimonPosition();
        void addEngimon(int, int, string);
        void removeEngimon(int, int);
        void moveEngimon(int, int, int, int, string);
        bool isValidEngimonPosition(int, int, string, bool);
        void move(char);
        void set_player_pos(int, int);
        int* get_player_pos()const;
        void set_active_engimon_pos(int, int);
        int* get_active_engimon_pos()const;
        void set_active_engimon_species(string);
        string get_active_engimon_species()const;
        Engimon* getNearbyEnemyEngimon();
};



#endif
