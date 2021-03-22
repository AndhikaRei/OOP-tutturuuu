#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <random> // A better random number generator
#include "../Exception/Exception.hpp"
#include "../Engimon/Engimon.hpp"
#include "../Elements/Elements.hpp"

using namespace std;

/*--- CLASS MAP ---*/
class Map{
    private :
        /*--- CLASS MapElem ---*/
        class MapElem{
            private :
                int x; /* Koordinat Absis Tiles */
                int y; /* Koordinat Ordinat Tiles */
                char symbol; /* Simbol Tiles Pada Peta yang Merepresentasikan Tipe Tiles / Engimon / Active Engimon/ Player */
                bool engimonExist; /* Boolean Status Untuk Keberadaan Engimon Liar Pada Tiles */
                Engimon* engimon; /* Pointer to Engimon yang berada pada Tiles*/
                string type; /* Tipe Tiles, grassland atau sea*/
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

                // Engimon Managers 
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
        const int max_engimon = 20;
    public :
        Map();
        Map(int, int, string);
        Map(const Map&);
        ~Map();
        bool isValidPosition(int, int, bool);
        bool isAnyActiveEngimon() const;
        bool isPlayerPosition(int, int) const;

        // getter;
        int get_total_engimon() const;
        int get_max_engimon() const;

        // Map Manipulation Functions 
        void printMap();
        void updateMap();

        // Engimon Handlers
        void randomMoveAllEngimon();
        map<string, vector<int>> getEngimonPosition();
        void addEngimon(int, int, string);
        void removeEngimon(int, int);
        void moveEngimon(int, int, int, int, string);
        bool isValidEngimonPosition(int, int, string, bool);
       

        // Player Handlers 
        void move(char);
        void set_player_pos(int, int);
        int* get_player_pos() const;
        void set_active_engimon_pos(int, int);
        int* get_active_engimon_pos()const;
        void set_active_engimon_species(string);
        string get_active_engimon_species()const;
        void spawnRandomEngimon();

        Engimon* getNearbyEnemyEngimon(int* X, int* Y);

        
};



#endif
